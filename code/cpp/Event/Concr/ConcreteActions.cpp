/*********************************************************************************************
 * Name      :  ConcreteActions.cpp
 *
 * Purpose   :  Concrete actions.
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

#include "ConcreteActions.h"
#include <Event/Impl/ActionImpl.cpp> //template function definitions
#include <Event/Operation.h>
#include <Event/Report.h>
#include <Event/Impl/ReportImpl.h>
#include <Engine/ExTimeInfo.h>
#include <Model/Network.h>
#include <Model/Block.h>
#include <Model/IntegrationSite.h>
#include <Task/Task.h>

namespace CORINET {

CRecordNetState::CRecordNetState()
{

}

CRecordNetState::~CRecordNetState()
{
	
}

void CRecordNetState::AddTarget(void* parent,void* target,std::string idstr,std::string parentid,size_t)
{
	SubArrayIteratorConst* pit = static_cast<CNetwork*>(target)->GetStateConst();
	pReporter->MakeTargetNode(pit,idstr,"netState",parentid);
	mTargets.push_back(LTargetAndParent(pit,parent));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRecordNetInput::CRecordNetInput()
{

}

CRecordNetInput::~CRecordNetInput()
{
	
}

void CRecordNetInput::AddTarget(void* parent,void* target,std::string idstr,std::string parentid,size_t)
{
	SubArrayIteratorConst* pit = static_cast<CNetwork*>(target)->GetInputConst();
	pReporter->MakeTargetNode(pit,idstr,"netInput",parentid);
	mTargets.push_back(LTargetAndParent(pit,parent));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRecordNetOutput::CRecordNetOutput()
{

}

CRecordNetOutput::~CRecordNetOutput()
{
	
}

void CRecordNetOutput::AddTarget(void* parent,void* target,std::string idstr,std::string parentid,size_t)
{
	MultipleSubArrayIteratorConst* pit = static_cast<CNetwork*>(target)->GetOutputConst();
	pReporter->MakeTargetNode(pit,idstr,"netOutput",parentid);
	mTargets.push_back(LTargetAndParent(pit,parent));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRecordNetIO::CRecordNetIO()
{

}

CRecordNetIO::~CRecordNetIO()
{
	
}

void CRecordNetIO::AddTarget(void* parent,void* target,std::string idstr,std::string parentid,size_t)
{
	MultipleSubArrayIteratorConst* pit = static_cast<CNetwork*>(target)->GetIOConst();
	pReporter->MakeTargetNode(pit,idstr,"netIO",parentid);
	mTargets.push_back(LTargetAndParent(pit,parent));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRecordBlockOutput::CRecordBlockOutput()
{

}

CRecordBlockOutput::~CRecordBlockOutput()
{

}

void CRecordBlockOutput::AddTarget(void* parent,void* target,std::string idstr,std::string parentid,size_t)
{
	SubArrayIteratorConst* pit = static_cast<CBlock*>(target)->GetOutputConst();
	pReporter->MakeTargetNode(pit,idstr,"blockOutput",parentid);
	mTargets.push_back(LTargetAndParent(pit,parent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRecordWeights::CRecordWeights()
{

}

CRecordWeights::~CRecordWeights()
{

}

void CRecordWeights::AddTarget(void* parent,void* target,std::string idstr,std::string parentid,size_t)
{
	MatrixIteratorConst* pit = static_cast<CIntegrationSite*>(target)->GetWeightsConst();
	pReporter->MakeTargetNode(pit,idstr,"weights",parentid);
	mTargets.push_back(LTargetAndParent(pit,parent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRecordSynapses::CRecordSynapses()
{

}

CRecordSynapses::~CRecordSynapses()
{

}

void CRecordSynapses::AddTarget(void* parent,void* target,std::string idstr,std::string parentid,size_t)
{
	SynapseWrapper* pit = static_cast<CIntegrationSite*>(target)->GetSynapses();
	pReporter->MakeTargetNode(pit,idstr,"synapses",parentid);
	mTargets.push_back(LTargetAndParent(pit,parent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRecordIntegrationValues::CRecordIntegrationValues()
{

}

CRecordIntegrationValues::~CRecordIntegrationValues()
{

}

void CRecordIntegrationValues::AddTarget(void* parent,void* target,std::string idstr,std::string parentid,size_t)
{
	SubArrayIteratorConst* pit = static_cast<CIntegrationSite*>(target)->GetOutputConst();
	pReporter->MakeTargetNode(pit,idstr,"integrationValues",parentid);
	mTargets.push_back(LTargetAndParent(pit,parent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRecordIntegrationInput::CRecordIntegrationInput()
{

}

CRecordIntegrationInput::~CRecordIntegrationInput()
{

}

void CRecordIntegrationInput::AddTarget(void* parent,void* target,std::string idstr,std::string parentid,size_t)
{
	IndirectIteratorConst* pit = static_cast<CIntegrationSite*>(target)->GetInputConst();
	pReporter->MakeTargetNode(pit,idstr,"integrationInput",parentid);
	mTargets.push_back(LTargetAndParent(pit,parent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRecordTaskPatterns::CRecordTaskPatterns()
{
	
}

CRecordTaskPatterns::~CRecordTaskPatterns()
{

}

void CRecordTaskPatterns::Handle(CExTimeInfo* eTI)
{
	for(LTargets::iterator it = mTargets.begin(),ite = mTargets.end();it != ite;++it) {
		while (CTask* thisTask = eTI->GetPartTasks()) {
			if (!thisTask)
				break;
			if (thisTask == it->second)
				pReporter->Write(mPrecision,it->first,eTI,1);
		}
	}
}

void CRecordTaskPatterns::AddTarget(void* parent,void* target,std::string idstr,std::string parentid,size_t)
{
	MatrixIteratorConst* pit = static_cast<CTask*>(target)->GetPatternConst();
	pReporter->MakeTargetNode(pit,idstr,"taskPatterns",parentid);
	mTargets.push_back(LTargetAndParent(pit,parent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CModifyNetState::CModifyNetState()
{

}

CModifyNetState::~CModifyNetState()
{

}

void CModifyNetState::AddTarget(void* parent,void* target,std::string,std::string,size_t)
{
	mTargets.push_back(LTargetAndParent(static_cast<CNetwork*>(target)->GetState(),parent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CModifyBlockOutput::CModifyBlockOutput()
{

}

CModifyBlockOutput::~CModifyBlockOutput()
{

}

void CModifyBlockOutput::AddTarget(void* parent,void* target,std::string,std::string,size_t)
{
	mTargets.push_back(LTargetAndParent(static_cast<CBlock*>(target)->GetOutput(),parent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CModifyIntegrationValues::CModifyIntegrationValues()
{

}

CModifyIntegrationValues::~CModifyIntegrationValues()
{

}

void CModifyIntegrationValues::AddTarget(void* parent,void* target,std::string,std::string,size_t)
{
	mTargets.push_back(LTargetAndParent(static_cast<CIntegrationSite*>(target)->GetOutput(),parent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CModifyIntegrationInput::CModifyIntegrationInput()
{

}

CModifyIntegrationInput::~CModifyIntegrationInput()
{

}

void CModifyIntegrationInput::AddTarget(void* parent,void* target,std::string,std::string,size_t)
{
	mTargets.push_back(LTargetAndParent(static_cast<CIntegrationSite*>(target)->GetInput(),parent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CModifyWeights::CModifyWeights()
{
	
}

CModifyWeights::~CModifyWeights()
{

}
	
void CModifyWeights::Handle(CExTimeInfo* eTI)
{
	bool next = false;
	CNetwork* thisNet = eTI->GetNetwork();
	for(LTargets::iterator it=mTargets.begin(),ite=mTargets.end();it != ite;++it) {
		if (!thisNet || thisNet == it->second) {
			next = true;
			if (pInputIndices && pNodeIndices) {
				for(size_t i=0,s = pInputIndices->size();i<s;++i) {
					double val = (*(it->first))((*pInputIndices)[i],(*pNodeIndices)[i]);
					for(size_t k=0;k<mOperations.size();k++) {
						val = mOperations[k]->operator()(val);
					}
					(*(it->first))((*pInputIndices)[i],(*pNodeIndices)[i]) = val;
				}
			}
			else if (pInputIndices) {
				for(size_t i=0,s = pInputIndices->size();i<s;++i) {
					MatrixIterator::RowIterator inputit = it->first->GetRow((*pInputIndices)[i]);
					for(inputit.begin();!inputit.end();++inputit) {
						double val = *inputit;
						for(size_t k=0,ks=mOperations.size();k<ks;++k) {
							val = (*(mOperations[k]))(val);
						}
						(*inputit) = val;
					}
				}
			}
			else if (pNodeIndices) {
				for(size_t j=0,s = pNodeIndices->size();j<s;++j) {
					MatrixIterator::ColIterator nodeit = it->first->GetCol((*pNodeIndices)[j]);
					for(nodeit.begin();!nodeit.end();++nodeit) {
						double val = *nodeit;
						for(size_t k=0,ks=mOperations.size();k<ks;++k) {
							val = (*(mOperations[k]))(val);
						}
						(*nodeit) = val;
					}	
				}
			}
		}
	}
	if (next) {
		for(size_t k=0,ks=mOperations.size();k<ks;++k) {
			mOperations[k]->Next();
		}
	}
}

void CModifyWeights::AddTarget(void* parent,void* target,std::string,std::string,size_t)
{
	mTargets.push_back(LTargetAndParent(static_cast<CIntegrationSite*>(target)->GetWeights(),parent));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CModifyParamTask::CModifyParamTask()
{

}

CModifyParamTask::~CModifyParamTask()
{

}

void CModifyParamTask::Handle(CExTimeInfo* eTI)
{
	bool next = false;
	for(LTargets::iterator it=mTargets.begin(),ite=mTargets.end();it != ite;++it) {
		while (CTask* thisTask = eTI->GetPartTasks()) {
			if (!thisTask)
				break;
			if (thisTask == it->second) {
				next = true;
				LParamInfo& paraminfo = it->first;
				double val = paraminfo.first->GetParam(paraminfo.second);
				for(size_t i=0;i<mOperations.size();i++) {
					val = mOperations[i]->operator()(val);
				}
				paraminfo.first->SetParam(paraminfo.second,val);
			}
		}
	}
	if (next) {
		for(size_t k=0,ks=mOperations.size();k<ks;++k) {
			mOperations[k]->Next();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CModifyParamNetwork::CModifyParamNetwork()
{

}

CModifyParamNetwork::~CModifyParamNetwork()
{

}

void CModifyParamNetwork::Handle(CExTimeInfo* eTI)
{
	bool next = false;
	CNetwork* thisNet = eTI->GetNetwork();

	for(LTargets::iterator it=mTargets.begin(),ite=mTargets.end();it != ite;++it) {
		if (!thisNet || thisNet == it->second) {
			next = true;
			LParamInfo& paraminfo = it->first;
			double val = paraminfo.first->GetParam(paraminfo.second);
			for(size_t i=0;i<mOperations.size();i++) {
				val = mOperations[i]->operator()(val);
			}
			paraminfo.first->SetParam(paraminfo.second,val);
		}
	}
	if (next) {
		for(size_t k=0,ks=mOperations.size();k<ks;++k) {
			mOperations[k]->Next();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CModifyParamExecution::CModifyParamExecution()
{

}

CModifyParamExecution::~CModifyParamExecution()
{

}

void CModifyParamExecution::Handle(CExTimeInfo* eTI)
{
	bool next = false;
	CExecutionElement* thisPart = eTI->GetPart();
	for(LTargets::iterator it=mTargets.begin(),ite=mTargets.end();it != ite;++it) {
		if (thisPart == it->second) {
			next = true;
			LParamInfo& paraminfo = it->first;
			double val = paraminfo.first->GetParam(paraminfo.second);
			for(size_t i=0;i<mOperations.size();i++) {
				val = mOperations[i]->operator()(val);
			}
			paraminfo.first->SetParam(paraminfo.second,val);
		}
	}
	if (next) {
		for(size_t k=0,ks=mOperations.size();k<ks;++k) {
			mOperations[k]->Next();
		}
	}
}

} //end namespace CORINET
