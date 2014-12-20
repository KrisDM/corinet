/*********************************************************************************************
 * Name      :  ConcreteExTimeInfo.h
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

#ifndef CORINET_EXTIMEINFOCONCR
#define CORINET_EXTIMEINFOCONCR

#include <Engine/Impl/ExTimeInfoImpl.h>
#include <vector>

namespace CORINET {

class CExTimeInfoV1 : public CExTimeInfo {
	size_t mTotalConfigs;
	size_t mTotalRuns;
	size_t mConfig;
	size_t mRun;
	size_t mPartEntry;
	size_t mGlobalIteration;
	size_t mIteration;
	size_t mIntegration;
	CExecutionElement* pPart;
	CNetwork* pNetwork;
	std::vector<CTask*> mTasks;
	mutable size_t mTaskCounter;
public:
	CExTimeInfoV1();
	virtual ~CExTimeInfoV1();

	size_t GetTotalCycles() const;
	size_t GetTotalConfigs() const;
	size_t GetTotalRuns() const;

	size_t GetCycle() const;
	size_t GetConfig() const;
	size_t GetRun() const;

	size_t GetPartEntry() const;
	size_t GetGlobalIteration() const;
	size_t GetIteration() const;
	size_t GetIntegration() const;
	
	CExecutionElement* GetPart() const;
	CTask* GetPartTasks() const;
	CNetwork* GetNetwork() const;
	
	void IncrConfig();
	void IncrRun();
	void IncrIteration();
	void IncrIntegration();

	void SetTotalConfigs(size_t);
	void SetTotalRuns(size_t);
	void SetConfig(size_t);
	void SetRun(size_t);
	void SetPartEntry(size_t);
	void SetGlobalIteration(size_t);
	void SetIteration(size_t);
	void SetIntegration(size_t);

	void SetPart(CExecutionElement*);
	void SetNetwork(CNetwork*);
	void AddTask(CTask*);
	void ClearTasks();
};

class CExTimeInfoPatternGenerator : public CExTimeInfoImpl {
	size_t mTotalRuns;
	size_t mRun;
	CTask* pTask;
	mutable bool bTask;
public:
	CExTimeInfoPatternGenerator();
	virtual ~CExTimeInfoPatternGenerator();

	size_t GetTotalRuns() const;
	size_t GetRun() const;
	void IncrRun();
	void SetTotalRuns(size_t);
	void SetRun(size_t);
	CTask* GetPartTasks() const;
	void AddTask(CTask*);
};

class CExTimeInfoRandTest : public CExTimeInfoImpl {
	size_t mTotalRuns;
	size_t mRun;
public:
	CExTimeInfoRandTest();
	virtual ~CExTimeInfoRandTest();

	size_t GetTotalRuns() const;
	size_t GetRun() const;
	void IncrRun();
	void SetTotalRuns(size_t);
	void SetRun(size_t);
};

} //end namespace CORINET
	
#endif //CORINET_EXTIMEINFOCONCR

