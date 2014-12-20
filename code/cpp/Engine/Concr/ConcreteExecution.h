/*********************************************************************************************
 * Name      :  ConcreteExecution.h
 *
 * Purpose   :  Concrete types of execution.
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

#ifndef CORINET_EXECUTIONCONCR
#define CORINET_EXECUTIONCONCR

#include <Engine/Impl/ExecutionImpl.h>
#include <vector>

namespace CORINET {
	

class CExecutionV1 : public CExecutionImpl {
	std::vector<CNetwork*> mNetworks;
	std::vector<CTask*> mTasks;
	std::vector<CEvent*> mEvents;
	CLoops* pLoops;
	CExecutionElement* pMainSequence;
public:
	CExecutionV1();
	virtual ~CExecutionV1();
	void operator()(CStatus*);

	void AddNetwork(CNetwork*);
	void AddTask(CTask*);
	void AddEvent(CEvent*);
	void AddExecutionElement(CExecutionElement*);
	void AddLoops(CLoops*);
};

class CExecutionPatternGenerator : public CExecutionImpl {
	CTask* pTask;
	CEvent* pEvent;
public:
	CExecutionPatternGenerator();
	virtual ~CExecutionPatternGenerator();
	void operator()(CStatus*);

	void AddTask(CTask*);
	void AddEvent(CEvent*);
};

class CExecutionRandTest : public CExecutionImpl {
	RandDouble* pRandGen;
	CReport* pReport;
	size_t mPrecision;
public:
	CExecutionRandTest();
	virtual ~CExecutionRandTest();
	void operator()(CStatus*);

	void SetRandGen(RandDouble*);
	void SetReport(CReport*,size_t);
};

} //end namespace CORINET

#endif //CORINET_EXECUTIONCONCR

