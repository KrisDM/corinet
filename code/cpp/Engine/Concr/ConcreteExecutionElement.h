/*********************************************************************************************
 * Name      :  ConcreteExecution.h
 *
 * Purpose   :  Concrete execution elements.
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

#ifndef CORINET_EXECUTEELEMENTCONCR
#define CORINET_EXECUTEELEMENTCONCR

#include <Engine/Impl/ExecutionElementImpl.h>
#include <valarray>
#include <map>
#include <vector>
#include <string>

namespace CORINET {
	class CNetwork;
	class CTask;
	class CEvent;
	class CExTimeInfo;

enum EventTimeV1 {
	AFTER_GENERATE,
	AFTER_INTEGRATE,
	AFTER_LEARN,
	AFTER_OUTPUT,
	AFTER_RESET,
	AFTER_RESETINTEGRATE,
	AFTER_RESETLEARN,
	AFTER_RESETOUTPUT,
	AFTER_SETINPUT,
	BEFORE_GENERATE,
	BEFORE_INTEGRATE,
	BEFORE_LEARN,
	BEFORE_RESET,	
	BEFORE_RESETINTEGRATE,	
	BEFORE_RESETLEARN,
	BEFORE_SETINPUT,
	BEGIN_ITERATION,
	BEGIN_PART,
	END_ITERATION,
	END_PART,
	DUMMY_TIME
};

class CExecutionSequenceV1 : public CExecutionElementImpl {
	typedef std::vector<CExecutionElement*> LExElements;
	size_t mSequenceEntry;
	const std::valarray<size_t>* pRepeats;
	LExElements mExElements;
public:
	CExecutionSequenceV1();
	virtual ~CExecutionSequenceV1();
	void operator()(CExTimeInfo*,std::vector<CNetwork*>&);

	void SetTimes(const std::valarray<size_t>*);
	void AddExElement(CExecutionElement*);
};

class CExecutionPartV1 : public CExecutionElementImpl {
	typedef std::vector<CTask*> LTasks;
	typedef std::map<EventTimeV1,std::vector<CEvent*> > LEvents;
	size_t mPartEntry;
	const std::valarray<size_t>* pIterations;
	bool bRandom;
	bool bLearn;
	bool bLearnDuringReset;
	bool bGenerateOnly;
	double mTimePerPattern;
	double mZeroTime;		
	LTasks mTasks;
	LEvents mEvents;
	inline void HandleEvents(EventTimeV1,CExTimeInfo*);
public:
	CExecutionPartV1(size_t*,double*);
	virtual ~CExecutionPartV1();
	void operator()(CExTimeInfo*,std::vector<CNetwork*>&);

	void SetParam(size_t,double);
	double GetParam(size_t);

	void SetTimes(const std::valarray<size_t>*);
	void AddTask(CTask*);
	void AddEvent(const std::string&,CEvent*);
};

} //end namespace CORINET

#endif //CORINET_EXECUTIONELEMENTCONCR

