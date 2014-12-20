/*********************************************************************************************
 * Name      :  ConcreteEvents.cpp
 *
 * Purpose   :  An event consists of a set of conditions and a set of actions.
 *				If the coniditions are true (all of them), then the actions are executed.
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

#include "ConcreteEvents.h"
#include <Engine/ExTimeInfo.h>
#include <Event/Action.h>
#include <Event/Condition.h>

namespace CORINET {

CEventModel1::CEventModel1() : mConditions(),mActions()
{

}

CEventModel1::~CEventModel1()
{
	
}

bool CEventModel1::CheckConditions(CExTimeInfo* eTI)
{
	bool returnval = true;
	for(LConditions::const_iterator it=mConditions.begin(),ite=mConditions.end();it != ite;++it) {
		switch (it->first) {
		case COND_CONFIG:
			returnval &= it->second->operator()(eTI->GetConfig());
			break;
		case COND_RUN:
			returnval &= it->second->operator()(eTI->GetRun());
			break;
		case COND_ENTRY:
			returnval &= it->second->operator()(eTI->GetPartEntry());
			break;
		case COND_ITERATION:
			returnval &= it->second->operator()(eTI->GetIteration());
			break;
		case COND_INTEGRATION:
			returnval &= it->second->operator()(eTI->GetIntegration());
			break;
		}
	}
	return returnval;
}

void CEventModel1::Initialise(CExTimeInfo* eTI)
{
	for(size_t i=0,s=mActions.size();i<s;++i) {
		mActions[i]->Initialise(eTI);
	}
}

void CEventModel1::Handle(CExTimeInfo* eTI)
{
	if (CheckConditions(eTI)) {
		for(size_t i=0,s=mActions.size();i<s;++i) {
			mActions[i]->Handle(eTI);
		}
	}
}

void CEventModel1::Finalise(CExTimeInfo* eTI)
{
	for(size_t i=0,s=mActions.size();i<s;++i) {
		mActions[i]->Finalise(eTI);
	}
}

void CEventModel1::AddCondition(const std::string& st,FCondition* cond)
{
	if (st == "config") {
		mConditions.insert(LConditions::value_type(COND_CONFIG,cond));
	}
	else if (st == "run") {
		mConditions.insert(LConditions::value_type(COND_RUN,cond));
	}
	else if (st == "entry") {
		mConditions.insert(LConditions::value_type(COND_ENTRY,cond));
	}
	else if (st == "iteration") {
		mConditions.insert(LConditions::value_type(COND_ITERATION,cond));
	}
	else if (st == "integration") {
		mConditions.insert(LConditions::value_type(COND_INTEGRATION,cond));
	}	
}

void CEventModel1::AddAction(CAction* action)
{
	mActions.push_back(action);
}

} //end namespace CORINET
