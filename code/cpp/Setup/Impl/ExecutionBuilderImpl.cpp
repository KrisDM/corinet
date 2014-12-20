/*********************************************************************************************
 * Name      :  ExecutionBuilderImpl.cpp
 *
 * Purpose   :  Create executions and cleanup after use. Implementation class. 
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

#include "ExecutionBuilderImpl.h"
#include <Engine/Impl/ExecutionImpl.h>
#include <Engine/Impl/ExecutionElementImpl.h>
#include <Engine/Impl/LoopImpl.h>
#include <Engine/ExTimeInfo.h>
#include <Util/Factory.h>
#include <Common/RandGen.h>
#include <Setup/Makers.h>
#include <Setup/CommonBuilder.h>
#include <Setup/NetBuilder.h>
#include <Setup/TaskBuilder.h>
#include <Setup/EventBuilder.h>

namespace CORINET {

CExecutionBuilderImpl::CExecutionBuilderImpl() : mLoopElements(),mLoops(),mExecutionElements(),pLoops(0),
												 pExecutionMaker(0),pExecution(0),pExTimeInfo(0),mTempObject(),mIDs(),
												 pCommonBuilder(0),pNetBuilder(0),pTaskBuilder(0),pEventBuilder(0)
												 
												 
{

}
	
CExecutionBuilderImpl::~CExecutionBuilderImpl()
{
	ReleaseAll();
}

void CExecutionBuilderImpl::SetCommonBuilder(CCommonBuilder* pcb)
{
	pCommonBuilder = pcb;
}

void CExecutionBuilderImpl::SetNetBuilder(CNetBuilder* pnb)
{
	pNetBuilder = pnb;
}

void CExecutionBuilderImpl::SetTaskBuilder(CTaskBuilder* ptb)
{
	pTaskBuilder = ptb;
}

void CExecutionBuilderImpl::SetEventBuilder(CEventBuilder* peb)
{
	pEventBuilder = peb;
}

CExecution* CExecutionBuilderImpl::Create(SExecutionMaker* pem)
{
	if (!pExecution) {
		pExecutionMaker = pem;
		
		pExecution = CFactoryManager<CExecution>::CreateInstance(pem->type);
		
		if (!pExecution) {
			throw ECreation("execution",pem->type);
		}
		
		//create all execution elements (but cannot be fully initialised at this point)
		if (pem->sequenceMaker) {
			static_cast<CExecutionImpl*>(pExecution)->AddExecutionElement(Create(pem->sequenceMaker));
		}
		
		//create networks (fully)
		for(size_t n=0,ns=pem->netMakers.size();n<ns;++n) {
			static_cast<CExecutionImpl*>(pExecution)->AddNetwork(pNetBuilder->Create(pem->netMakers[n]));
		}
		
		//create tasks (fully)
		for(size_t t=0,ts=pem->taskMakers.size();t<ts;++t) {
			static_cast<CExecutionImpl*>(pExecution)->AddTask(pTaskBuilder->Create(pem->taskMakers[t]));
		}
		
		//since all possible targets of events are created, events themselves can now be fully created
		for(size_t e=0,es=pem->eventMakers.size();e<es;++e) {
			static_cast<CExecutionImpl*>(pExecution)->AddEvent(pEventBuilder->Create(pem->eventMakers[e]));
		}
		
		//and the loops can also be created now
		if (pem->loopsMaker) {
			static_cast<CExecutionImpl*>(pExecution)->AddLoops(Create(pem->loopsMaker));
		}

		//now that everything is created, all execution elements can be finished with their tasks and events
		for(LExecutionElements::iterator it=mExecutionElements.begin(),ite=mExecutionElements.end();it != ite;++it) {
			SExecutionElementMaker* thismaker = it->first;
			CExecutionElement* thiselement = it->second;
			//add the tasks
			for(size_t t1=0,ts1=thismaker->taskMakers.size();t1<ts1;++t1) {
				static_cast<CExecutionElementImpl*>(thiselement)->AddTask(pTaskBuilder->Get(thismaker->taskMakers[t1]));
			}
			//add the events
			for(std::map<const std::string,std::vector<SEventMaker*> >::iterator 
				ev1=thismaker->eventMakers.begin(),eve=thismaker->eventMakers.end();ev1 != eve;++ev1) {
				std::vector<SEventMaker*>& eventVec = ev1->second;
				for(std::vector<SEventMaker*>::iterator it1=eventVec.begin(),ite1=eventVec.end();it1 != ite1;++it1)
					static_cast<CExecutionElementImpl*>(thiselement)->AddEvent(ev1->first,pEventBuilder->Get(*it1));
			}
		}
		//now create, initialise and set the execution time info
		pExTimeInfo = CFactoryManager<CExTimeInfo>::CreateInstance(pem->type);

		if (!pExTimeInfo) {
			throw ECreation("execution time info",pem->type);
		}
		if (pLoops)
			pExTimeInfo->SetTotalConfigs(pLoops->Configs());
		pExTimeInfo->SetTotalRuns(pem->numRuns);
		static_cast<CExecutionImpl*>(pExecution)->SetExTimeInfo(pExTimeInfo);

		//for randTest set randGen and reporter
		if (pem->randMaker)
			static_cast<CExecutionImpl*>(pExecution)->SetRandGen(static_cast<RandDouble*>(pCommonBuilder->Create(pem->randMaker)));
		if (pem->reportMaker)
			static_cast<CExecutionImpl*>(pExecution)->SetReport(pEventBuilder->Create(pem->reportMaker),pem->precision);
	}
	return pExecution;
}

CExecutionElement* CExecutionBuilderImpl::Create(SExecutionElementMaker* pem)
{
	if (mExecutionElements.find(pem) == mExecutionElements.end()) {
		size_t boolparams[4];
		boolparams[0] = pem->random;
		boolparams[1] = pem->learn;
		boolparams[2] = pem->learnDuringReset;
		boolparams[3] = pem->generate;

		CExecutionElement* pe = CFactoryManager<CExecutionElement>::CreateInstance(pem->type,boolparams,pem->executeParams);

		if (!pe) {
			throw ECreation("execution element",pem->type);
		}
		else
			mExecutionElements.insert(LExecutionElements::value_type(pem,pe));

		//set the repeat or iteration times
		static_cast<CExecutionElementImpl*>(pe)->SetTimes(pem->timeValues);
		//add the remaining parts or sequences
		for(size_t i=0,is=pem->partMakers.size();i<is;++i) {
			static_cast<CExecutionElementImpl*>(pe)->AddExElement(Create(pem->partMakers[i]));
		}
	}
	return mExecutionElements[pem];
}

CLoops* CExecutionBuilderImpl::Create(SLoopsMaker* plm)
{
	if (!pLoops) {
		pLoops = CFactoryManager<CLoops>::CreateInstance(plm->type);

		if (!pLoops)
			throw ECreation("loops",plm->type);

		//add the individual loops
		for(size_t i=0,is=plm->loopMakers.size();i<is;++i) {
			static_cast<CLoopsImpl*>(pLoops)->AddLoop(Create(plm->loopMakers[i]));
		}
	}
	return pLoops;
}

CLoop* CExecutionBuilderImpl::Create(SLoopMaker* plm)
{
	if (mLoops.find(plm) == mLoops.end()) {
		CLoop* pl = CFactoryManager<CLoop>::CreateInstance(plm->type);

		if (!pl)
			throw ECreation("loop",plm->type);
		else
			mLoops.insert(LLoops::value_type(plm,pl));

		//add the loopelements
		for(size_t i=0,is=plm->elemMakers.size();i<is;++i) {
			static_cast<CLoopImpl*>(pl)->AddLoopElement(Create(plm->elemMakers[i]));
		}
		//set the number of configurations of this loop
		static_cast<CLoopImpl*>(pl)->SetSize(plm->numConfigs);
	}
	return mLoops[plm];
}

CLoopElement* CExecutionBuilderImpl::Create(SLoopElementMaker* plm)
{
	if (mLoopElements.find(plm) == mLoopElements.end()) {
		CLoopElement* pl = CFactoryManager<CLoopElement>::CreateInstance(plm->type);

		if (!pl)
			throw ECreation("loopElement",plm->type);
		else
			mLoopElements.insert(LLoopElements::value_type(plm,pl));

		//add the parameter or weight values
		for(size_t i=0,is=plm->values.size();i<is;++i) {
			static_cast<CLoopElementImpl*>(pl)->AddValues(plm->values[i]);
		}
		//add the targets
		const std::string& makertype = plm->targets.operator[](0)->makerType;
		std::vector<void*>* tempobjects;
		for(size_t i1=0,is1=plm->targets.size();i1<is1;++i1) {
			if (makertype == "task") {
				tempobjects = &(pTaskBuilder->GetVoid(plm->targets.operator[](i1)));
			}
			else if (makertype == "network" || makertype == "block" || makertype == "integrationSite" ||
				makertype == "outputFunction" || makertype == "normalisation" || makertype == "initialisation") {
				tempobjects = &(pNetBuilder->GetVoid(plm->targets.operator[](i1)));
			}
			else if (makertype == "attenuation" || makertype == "noiseFunction" || makertype == "randGen") {
				tempobjects = &(pCommonBuilder->GetVoid(plm->targets.operator[](i1)));
			}
			else if (makertype == "executionElement") {
				tempobjects = &(this->GetVoid(plm->targets.operator[](i1)));
			}
			else {
				tempobjects = NULL;
			}
			for(size_t j=0,js=tempobjects->size();j<js;++j) {
				static_cast<CLoopElementImpl*>(pl)->AddTarget((*tempobjects)[j],plm->paramNums?(*(plm->paramNums))[i1]:0);
			}
		}
	}
	return mLoopElements[plm];
}

CExecution* CExecutionBuilderImpl::Get(SExecutionMaker*)
{
	return pExecution;
}
	
CExecutionElement* CExecutionBuilderImpl::Get(SExecutionElementMaker* pem)
{
	if (mExecutionElements.find(pem) != mExecutionElements.end())
		return mExecutionElements[pem];
	else
		return 0;
}

std::vector<void*>& CExecutionBuilderImpl::GetVoid(SMaker* maker)
{
	mTempObject.clear();
	if (maker->makerType == "executionElement") {
		if (mExecutionElements.find(static_cast<SExecutionElementMaker*>(maker)) != mExecutionElements.end()) {
			mTempObject.push_back(mExecutionElements[static_cast<SExecutionElementMaker*>(maker)]);
		}
	}
	return mTempObject;
}
	
const std::vector<std::pair<std::string,std::string> >& CExecutionBuilderImpl::GetTopLevelIDs()
{
	mIDs.clear();
	for(size_t i=0,is=pExecutionMaker->netMakers.size();i<is;++i) {
		mIDs.push_back(std::pair<std::string,std::string>("network",pExecutionMaker->netMakers[i]->idStr));
	}
	for(size_t i2=0,is2=pExecutionMaker->taskMakers.size();i2<is2;++i2) {
		if (!pExecutionMaker->taskMakers[i2]->insertMakers.size())
			mIDs.push_back(std::pair<std::string,std::string>("task",pExecutionMaker->taskMakers[i2]->idStr));
		else
			mIDs.push_back(std::pair<std::string,std::string>("compositeTask",pExecutionMaker->taskMakers[i2]->idStr));
	}
	return mIDs;
}

void CExecutionBuilderImpl::ReleaseAll()
{
	for(LLoopElements::iterator it1=mLoopElements.begin(),ite1=mLoopElements.end();it1 != ite1;++it1) {
		delete it1->second;
		it1->second = 0;
	}
	mLoopElements.clear();
	for(LLoops::iterator it2=mLoops.begin(),ite2=mLoops.end();it2 != ite2;++it2) {
		delete it2->second;
		it2->second = 0;
	}
	mLoops.clear();
	delete pLoops;
	pLoops = 0;
	for(LExecutionElements::iterator it3=mExecutionElements.begin(),ite3=mExecutionElements.end();it3 != ite3;++it3) {
		delete it3->second;
		it3->second = 0;
	}
	mExecutionElements.clear();
	pExecutionMaker = 0;
	delete pExecution;
	pExecution = 0;
	delete pExTimeInfo;
	pExTimeInfo = 0;
}

} //end namespace CORINET


