/*********************************************************************************************
 * Name      :  ConcreteExecution.cpp
 *
 * Purpose   :  Concrete types of execution
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

#include "ConcreteExecution.h"
#include <Util/Iterator.h>
#include <Engine/ExTimeInfo.h>
#include <Engine/ExecutionElement.h>
#include <Engine/Loop.h>
#include <Engine/Status.h>
#include <Common/RandGen.h>
#include <Model/Network.h>
#include <Task/Task.h>
#include <Event/Report.h>
#include <Event/Event.h>
#include <valarray>

namespace CORINET {

CExecutionV1::CExecutionV1() : mNetworks(),mTasks(),mEvents(),pLoops(0),pMainSequence(0)
{

}

CExecutionV1::~CExecutionV1()
{

}

void CExecutionV1::operator()(CStatus* pstatus)
{
	//run over all different configurations of networks and tasks
	const size_t ns = mNetworks.size();
	const size_t ts = mTasks.size();
	const size_t es = mEvents.size();
	for(pExTimeInfo->SetConfig(0),pLoops->Begin();pExTimeInfo->GetConfig() < pExTimeInfo->GetTotalConfigs();pExTimeInfo->IncrConfig(),++(*pLoops)) {
		//for each configuration, run the simulation a number of times
		for(pExTimeInfo->SetRun(0);pExTimeInfo->GetRun() < pExTimeInfo->GetTotalRuns();pExTimeInfo->IncrRun()) {
			if (pstatus)
				(*pstatus)(pExTimeInfo);
			//initialise all networks, tasks and events for this run
			for(size_t n1=0;n1 < ns;++n1) {
				mNetworks[n1]->Initialise();
			}
			for(size_t t1=0;t1 < ts;++t1) {
				mTasks[t1]->Initialise();
			}
			for(size_t e1=0;e1 < es;++e1) {
				mEvents[e1]->Initialise(pExTimeInfo);
			}

			//now perform the simulation itself, for all networks
			pExTimeInfo->SetGlobalIteration(0);
			(*pMainSequence)(pExTimeInfo,mNetworks);

			//do necessary cleanup before starting next run
			for(size_t n2=0;n2 < ns;++n2) {
				mNetworks[n2]->Finalise();
			}
			for(size_t t2=0;t2 < ts;++t2) {
				mTasks[t2]->Finalise();
			}
			for(size_t e2=0;e2 < es;++e2) {
				mEvents[e2]->Finalise(pExTimeInfo);
			}
		}
	}
}

void CExecutionV1::AddNetwork(CNetwork* pn)
{
	mNetworks.push_back(pn);
}

void CExecutionV1::AddTask(CTask* pt)
{
	mTasks.push_back(pt);
}

void CExecutionV1::AddEvent(CEvent* pe)
{
	mEvents.push_back(pe);
}

void CExecutionV1::AddExecutionElement(CExecutionElement* ps)
{
	pMainSequence = ps;
}

void CExecutionV1::AddLoops(CLoops* pl)
{
	pLoops = pl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

CExecutionPatternGenerator::CExecutionPatternGenerator() : pTask(0),pEvent(0)
{

}

CExecutionPatternGenerator::~CExecutionPatternGenerator()
{

}
	
void CExecutionPatternGenerator::operator()(CStatus*)
{
	pExTimeInfo->AddTask(pTask);
	for(pExTimeInfo->SetRun(0);pExTimeInfo->GetRun() < pExTimeInfo->GetTotalRuns();pExTimeInfo->IncrRun()) {
		pTask->Generate(true);
		pEvent->Handle(pExTimeInfo);
	}
}

void CExecutionPatternGenerator::AddTask(CTask* pt)
{
	pTask = pt;
}
	
void CExecutionPatternGenerator::AddEvent(CEvent* pe)
{
	pEvent = pe;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

CExecutionRandTest::CExecutionRandTest() : pRandGen(0),pReport(0),mPrecision(4)
{

}

CExecutionRandTest::~CExecutionRandTest()
{

}
	
void CExecutionRandTest::operator()(CStatus*)
{
	std::valarray<double>* presults = new std::valarray<double>(pExTimeInfo->GetTotalRuns());
	for(pExTimeInfo->SetRun(0);pExTimeInfo->GetRun() < pExTimeInfo->GetTotalRuns();pExTimeInfo->IncrRun()) {
		(*presults)[pExTimeInfo->GetRun()] = (*pRandGen)();
	}
	SubArrayIteratorConst* pit = new SubArrayIteratorConst(presults,0,presults->size());
	pReport->Write(mPrecision,pit,pExTimeInfo);
	delete pit;
	delete presults;
}

void CExecutionRandTest::SetRandGen(RandDouble* pr)
{
	pRandGen = pr;
}
	
void CExecutionRandTest::SetReport(CReport* pr,size_t prec)
{
	pReport = pr;
	mPrecision = 4;
}

} //end namespace CORINET
