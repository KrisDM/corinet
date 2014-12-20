/*********************************************************************************************
 * Name      :  ConcreteExTimeInfo.cpp
 *
 * Purpose   :  Class providing information about the current time stamp in the execution.
 *				Concrete classes derived from this class are determined by the execution
 *				structure of the specific engine they are used in.
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

#include "ConcreteExTimeInfo.h"

namespace CORINET {

CExTimeInfoV1::CExTimeInfoV1() : mTotalConfigs(0),mTotalRuns(0),mConfig(0),mRun(0),
								 mPartEntry(0),mGlobalIteration(0),mIteration(0),mIntegration(0),
								 pPart(0),pNetwork(0),mTasks(),mTaskCounter(0)
{

}

CExTimeInfoV1::~CExTimeInfoV1()
{

}

size_t CExTimeInfoV1::GetTotalCycles() const
{
	return mTotalRuns*mTotalConfigs;
}
	
size_t CExTimeInfoV1::GetTotalConfigs() const
{
	return mTotalConfigs;
}

size_t CExTimeInfoV1::GetTotalRuns() const
{
	return mTotalRuns;
}

size_t CExTimeInfoV1::GetCycle() const
{
	return mConfig*mTotalRuns + mRun;
}

size_t CExTimeInfoV1::GetConfig() const
{
	return mConfig;
}

size_t CExTimeInfoV1::GetRun() const
{
	return mRun;
}

size_t CExTimeInfoV1::GetPartEntry() const
{
	return mPartEntry;
}

size_t CExTimeInfoV1::GetGlobalIteration() const
{
	return mGlobalIteration;
}

size_t CExTimeInfoV1::GetIteration() const
{
	return mIteration;
}

size_t CExTimeInfoV1::GetIntegration() const
{
	return mIntegration;
}
	
CExecutionElement* CExTimeInfoV1::GetPart() const
{
	return pPart;
}

CTask* CExTimeInfoV1::GetPartTasks() const
{
	if (mTaskCounter < mTasks.size())
		return mTasks[mTaskCounter++];
	else {
		mTaskCounter = 0;
		return 0;
	}
}

CNetwork* CExTimeInfoV1::GetNetwork() const
{
	return pNetwork;
}
	
void CExTimeInfoV1::IncrConfig()
{
	++mConfig;
}

void CExTimeInfoV1::IncrRun()
{
	++mRun;
}

void CExTimeInfoV1::IncrIteration()
{
	++mIteration;
	++mGlobalIteration;
}

void CExTimeInfoV1::IncrIntegration()
{
	++mIntegration;
}

void CExTimeInfoV1::SetTotalConfigs(size_t v)
{
	mTotalConfigs = v;
}

void CExTimeInfoV1::SetTotalRuns(size_t v)
{
	mTotalRuns = v;
}

void CExTimeInfoV1::SetConfig(size_t v)
{
	mConfig = v;
}

void CExTimeInfoV1::SetRun(size_t v)
{
	mRun = v;
}

void CExTimeInfoV1::SetPartEntry(size_t v)
{
	mPartEntry = v;
}

void CExTimeInfoV1::SetGlobalIteration(size_t v)
{
	mGlobalIteration = v;
}
		
void CExTimeInfoV1::SetIteration(size_t v)
{
	mIteration = v;
}

void CExTimeInfoV1::SetIntegration(size_t v)
{
	mIntegration = v;
}

void CExTimeInfoV1::SetPart(CExecutionElement* pe)
{
	pPart = pe;
}
	
void CExTimeInfoV1::SetNetwork(CNetwork* pn)
{
	pNetwork = pn;
}

void CExTimeInfoV1::AddTask(CTask* pt)
{
	mTasks.push_back(pt);
}

void CExTimeInfoV1::ClearTasks()
{
	mTasks.clear();
	mTaskCounter = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

CExTimeInfoPatternGenerator::CExTimeInfoPatternGenerator() : mTotalRuns(0),mRun(0),pTask(0),bTask(false)
{

}

CExTimeInfoPatternGenerator::~CExTimeInfoPatternGenerator()
{

}

size_t CExTimeInfoPatternGenerator::GetTotalRuns() const
{
	return mTotalRuns;
}

size_t CExTimeInfoPatternGenerator::GetRun() const
{
	return mRun;
}

CTask* CExTimeInfoPatternGenerator::GetPartTasks() const
{
	if (!bTask) {
		bTask = true;
		return pTask;
	}
	else {
		bTask = false;
		return 0;
	}
}

void CExTimeInfoPatternGenerator::IncrRun()
{
	++mRun;
}

void CExTimeInfoPatternGenerator::SetTotalRuns(size_t v)
{
	mTotalRuns = v;
}

void CExTimeInfoPatternGenerator::SetRun(size_t v)
{
	mRun = v;
}

void CExTimeInfoPatternGenerator::AddTask(CTask* pt)
{
	pTask = pt;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

CExTimeInfoRandTest::CExTimeInfoRandTest() : mTotalRuns(0),mRun(0)
{

}

CExTimeInfoRandTest::~CExTimeInfoRandTest()
{

}

size_t CExTimeInfoRandTest::GetTotalRuns() const
{
	return mTotalRuns;
}

size_t CExTimeInfoRandTest::GetRun() const
{
	return mRun;
}

void CExTimeInfoRandTest::IncrRun()
{
	++mRun;
}

void CExTimeInfoRandTest::SetTotalRuns(size_t v)
{
	mTotalRuns = v;
}

void CExTimeInfoRandTest::SetRun(size_t v)
{
	mRun = v;
}

} //end namespace CORINET

