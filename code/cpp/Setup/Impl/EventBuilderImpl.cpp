/*********************************************************************************************
 * Name      :  EventBuilderImpl.cpp
 *
 * Purpose   :  Create events and cleanup after use. Implementation class.
 *				 
 * Notes	 :	
 *
 * Info      :	http://www.corinet.org
 *
 * Copyright :	2006, King's College London
 *		
 * License   :  This program is free software; you can redistribute it and/or modify
 *				it under the terms of the GNU General Public License as published by
 *				the Free Software Foundation; either version 2 of the License, or
 *				(at your option) any later version.
 *
 *				This program is distributed in the hope that it will be useful,
 *				but WITHOUT ANY WARRANTY; without even the implied warranty of
 *				MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *				GNU General Public License in $CORINETROOT/licenses for more details.
 *
 **********************************************************************************************/

#include "EventBuilderImpl.h"
#include <Event/Impl/EventImpl.h>
#include <Event/Impl/ActionImpl.h>
#include <Event/Impl/ReportImpl.h>
#include <Event/Impl/ConditionImpl.h>
#include <Event/Impl/OperationImpl.h>
#include <Util/Factory.h>
#include <Setup/Makers.h>
#include <Setup/CommonBuilder.h>
#include <Setup/NetBuilder.h>
#include <Setup/TaskBuilder.h>
#include <Setup/ExecutionBuilder.h>

namespace CORINET {

CEventBuilderImpl::CEventBuilderImpl() : mOperations(),mConditions(),mReports(),mActions(),mEvents(),
										pCommonBuilder(0),pNetBuilder(0),pTaskBuilder(0),pExecutionBuilder(0)
{

}
	
CEventBuilderImpl::~CEventBuilderImpl()
{
	ReleaseAll();
}

void CEventBuilderImpl::SetCommonBuilder(CCommonBuilder* pcb)
{
	pCommonBuilder = pcb;
}
	
void CEventBuilderImpl::SetNetBuilder(CNetBuilder* pnb)
{
	pNetBuilder = pnb;
}
	
void CEventBuilderImpl::SetTaskBuilder(CTaskBuilder* ptb)
{
	pTaskBuilder = ptb;
}
	
void CEventBuilderImpl::SetExecutionBuilder(CExecutionBuilder* peb)
{
	pExecutionBuilder = peb;
}

CEvent* CEventBuilderImpl::Create(SEventMaker* pem)
{
	if (mEvents.find(pem) == mEvents.end()) {
		CEvent* pe = CFactoryManager<CEvent>::CreateInstance(pem->type);

		if (!pe)
			throw ECreation("event",pem->type);
		else
			mEvents.insert(LEvents::value_type(pem,pe));
		
		//add the conditions
		for(std::multimap<const std::string,SConditionMaker*>::const_iterator it=pem->condMakers.begin(),
			ite=pem->condMakers.end();it != ite;++it) {
			static_cast<CEventImpl*>(pe)->AddCondition(it->first,Create(it->second));
		}
		
		//add the actions
		for(size_t i=0,is=pem->actionMakers.size();i<is;++i) {
			static_cast<CEventImpl*>(pe)->AddAction(Create(pem->actionMakers[i]));
		}
	}
	return mEvents[pem];
}

CAction* CEventBuilderImpl::Create(SActionMaker* pam)
{
	if (mActions.find(pam) == mActions.end()) {
		CAction* pa = CFactoryManager<CAction>::CreateInstance(pam->type);

		if (!pa)
			throw ECreation("action",pam->type);
		else
			mActions.insert(LActions::value_type(pam,pa));
		
		//set the reporter (only has effect for record actions)
		if (pam->reportMaker) {
			static_cast<CActionImpl*>(pa)->SetReporter(Create(pam->reportMaker));
			static_cast<CActionImpl*>(pa)->SetPrecision(pam->precision);
		}
		else
			static_cast<CActionImpl*>(pa)->SetReporter(0);
		//add the operations (only for modify actions)
		for(size_t i1=0,ie1=pam->opMakers.size();i1<ie1;++i1) {
			static_cast<CActionImpl*>(pa)->AddOperation(Create(pam->opMakers[i1]));
		}
		//set the node and input indices (only has effect for modifyValues actions)
		static_cast<CActionImpl*>(pa)->SetIndices(pam->nodeIndices,pam->inputIndices);
		
		//add the targets
		if (pam->targets.size()) {
			const std::string& makertype = pam->targets[0]->makerType;
			if (makertype == "task" || makertype == "dataSource" || makertype == "insert") {
				for(size_t i=0,is=pam->targets.size();i<is;++i) {
					std::vector<void*>& tempobjects = pTaskBuilder->GetVoid(pam->targets[i]);
					for(size_t j=0,js=tempobjects.size();j<js;++j) {
						std::vector<CTask*> tempparents = pTaskBuilder->GetParents(tempobjects[j]);
						for(size_t k=0,ks=tempparents.size();k<ks;++k) {
							std::string idstr = "";
							std::string parentid = "";
							if (pam->paramNums) {
								static_cast<CActionImpl*>(pa)->AddTarget(tempparents[k],tempobjects[j],"","",(*(pam->paramNums))[i]);
							}
							else {
								if (makertype == "task") {
									idstr = static_cast<STaskMaker*>(pam->targets[i])->idStr;
									parentid = pTaskBuilder->GetTaskID(tempparents[k]);
								}
								static_cast<CActionImpl*>(pa)->AddTarget(tempparents[k],tempobjects[j],idstr,parentid);
							}
						}
					}
				}
			}
			else if (makertype == "network" || makertype == "block" || makertype == "integrationSite" ||
				makertype == "outputFunction" || makertype == "normalisation" || makertype == "initialisation") {
				for(size_t i=0,is=pam->targets.size();i<is;++i) {
					std::vector<void*>& tempobjects = pNetBuilder->GetVoid(pam->targets[i]);
					for(size_t j=0,js=tempobjects.size();j<js;++j) {
						std::vector<CNetwork*>& tempparents = pNetBuilder->GetParents(tempobjects[j]);
						for(size_t k=0,ks=tempparents.size();k<ks;++k) {
							std::string idstr = "";
							std::string parentid = "";
							if (pam->paramNums) {
								static_cast<CActionImpl*>(pa)->AddTarget(tempparents[k],tempobjects[j],"","",(*(pam->paramNums))[i]);
							}
							else {
								if (makertype == "network") {
									SNetworkMaker* netMaker = static_cast<SNetworkMaker*>(pam->targets[i]);
									idstr = netMaker->idStr;
									parentid = idstr;
								}
								else if (makertype == "block") {
									SBlockMaker* blockMaker = static_cast<SBlockMaker*>(pam->targets[i]);
									idstr = blockMaker->idStr;
									parentid = pNetBuilder->GetNetworkID(tempparents[k]);
								}
								else if (makertype == "integrationSite") {
									SIntegrationSiteMaker* siteMaker = static_cast<SIntegrationSiteMaker*>(pam->targets[i]);
									idstr = siteMaker->idStr;
									parentid = pNetBuilder->GetNetworkID(tempparents[k]);
								}
								static_cast<CActionImpl*>(pa)->AddTarget(tempparents[k],tempobjects[j],idstr,parentid);
							}
						}
					}
				}
			}
			else if (makertype == "attenuation" || makertype == "noiseFunction" || makertype == "randGen") {
				for(size_t i=0,is=pam->targets.size();i<is;++i) {
					std::vector<void*>& tempobjects = pCommonBuilder->GetVoid(pam->targets[i]);
					for(size_t j=0,js=tempobjects.size();j<js;++j) {
						std::vector<CTask*>& temptaskparents = pTaskBuilder->GetParents(tempobjects[j]);
						for(size_t k1=0,ks1=temptaskparents.size();k1<ks1;++k1) {
							if (pam->paramNums) {
								static_cast<CActionImpl*>(pa)->AddTarget(temptaskparents[k1],tempobjects[j],"","",(*(pam->paramNums))[i]);
							}
							else {
								static_cast<CActionImpl*>(pa)->AddTarget(temptaskparents[k1],tempobjects[j],"","");
							}
						} 
						std::vector<CNetwork*>& tempnetparents = pNetBuilder->GetParents(tempobjects[j]);
						for(size_t k2=0,ks2=tempnetparents.size();k2<ks2;++k2) {
							if (pam->paramNums) {
								static_cast<CActionImpl*>(pa)->AddTarget(tempnetparents[k2],tempobjects[j],"","",
									(*(pam->paramNums))[i]);
							}
							else {
								static_cast<CActionImpl*>(pa)->AddTarget(tempnetparents[k2],tempobjects[j],"","");
							}
						} 
					}
				}
			}
			else if (makertype == "executionElement") {
				for(size_t i=0,is=pam->targets.size();i<is;++i) {
					std::vector<void*>& tempobjects = pExecutionBuilder->GetVoid(pam->targets[i]);
					for(size_t j=0,js=tempobjects.size();j<js;++j) {
						if (pam->paramNums) {
							static_cast<CActionImpl*>(pa)->AddTarget(tempobjects[j],tempobjects[j],"","",(*(pam->paramNums))[i]);
						}
						else {
							static_cast<CActionImpl*>(pa)->AddTarget(tempobjects[j],tempobjects[j],"","");
						}
					}
				}
			}
		}
		
	}
	return mActions[pam];
}
	
CReport* CEventBuilderImpl::Create(SReportMaker* prm)
{
	if (mReports.find(prm) == mReports.end()) {
		CReport* pr = CFactoryManager<CReport>::CreateInstance(prm->type);

		if (!pr)
			throw ECreation("report",prm->type);
		else
			mReports.insert(LReports::value_type(prm,pr));

		//initialise
		static_cast<CReportImpl*>(pr)->SetSink(prm->sink);

		const std::vector<std::pair<std::string,std::string> >& topIDs = pExecutionBuilder->GetTopLevelIDs();
		for(size_t n=0,ns=topIDs.size();n<ns;++n) {
			static_cast<CReportImpl*>(pr)->MakeTopLevelNode(topIDs[n].first,topIDs[n].second);
		}
	}
	return mReports[prm];
}
	
FCondition* CEventBuilderImpl::Create(SConditionMaker* pcm)
{
	if (mConditions.find(pcm) == mConditions.end()) {
		FCondition* pc = CFactoryManager<FCondition>::CreateInstance(pcm->type);
		if (!pc)
			throw ECreation("condition",pcm->type);
		else
			mConditions.insert(LConditions::value_type(pcm,pc));

		//set the condition values
		static_cast<FConditionImpl*>(pc)->SetVals(pcm->conditionVals);
	}
	return mConditions[pcm];
}
	
FOperation* CEventBuilderImpl::Create(SOperationMaker* pom)
{
	if (mOperations.find(pom) == mOperations.end()) {
		FOperation* po = CFactoryManager<FOperation>::CreateInstance(pom->type);
		if (!po)
			throw ECreation("operation",pom->type);
		else
			mOperations.insert(LOperations::value_type(pom,po));

		//set the values
		static_cast<FOperationImpl*>(po)->SetVals(pom->modifyVals);	
	}
	return mOperations[pom];
}

CEvent* CEventBuilderImpl::Get(SEventMaker* em)
{
	if (mEvents.find(em) != mEvents.end()) 
		return mEvents[em];
	else
		return 0;
}

CReport* CEventBuilderImpl::Get(SReportMaker* rm)
{
	if (mReports.find(rm) != mReports.end()) 
		return mReports[rm];
	else
		return 0;
}
	
void CEventBuilderImpl::ReleaseAll()
{
	for(LOperations::iterator it1=mOperations.begin(),ite1=mOperations.end();it1 != ite1;++it1) {
		delete it1->second;
		it1->second = 0;
	}
	mOperations.clear();
	for(LConditions::iterator it2=mConditions.begin(),ite2=mConditions.end();it2 != ite2;++it2) {
		delete it2->second;
		it2->second = 0;
	}
	mConditions.clear();
	for(LReports::iterator it3=mReports.begin(),ite3=mReports.end();it3 != ite3;++it3) {
		delete it3->second;
		it3->second = 0;
	}
	mReports.clear();
	for(LActions::iterator it4=mActions.begin(),ite4=mActions.end();it4 != ite4;++it4) {
		delete it4->second;
		it4->second = 0;
	}
	mActions.clear();
	for(LEvents::iterator it5=mEvents.begin(),ite5=mEvents.end();it5 != ite5;++it5) {
		delete it5->second;
		it5->second = 0;
	}
	mEvents.clear();
}

} //end namespace CORINET


