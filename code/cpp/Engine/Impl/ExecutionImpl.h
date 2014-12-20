/*********************************************************************************************
 * Name      :  ExecutionImpl.h
 *
 * Purpose   :  Implementation class for execution elements.
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

#ifndef CORINET_EXECUTIONIMPL
#define CORINET_EXECUTIONIMPL

#include <Engine/Execution.h>

namespace CORINET {
	class CNetwork;
	class CTask;
	class CEvent;
	class CExecutionElement;
	class CLoops;
	class CExTimeInfo;
	class RandDouble;
	class CReport;

class CExecutionImpl : public CExecution {
protected:
	CExTimeInfo* pExTimeInfo;
public:
	virtual ~CExecutionImpl();
	virtual void AddNetwork(CNetwork*);
	virtual void AddTask(CTask*);
	virtual void AddEvent(CEvent*);
	virtual void AddExecutionElement(CExecutionElement*);
	virtual void AddLoops(CLoops*);
	virtual void SetExTimeInfo(CExTimeInfo*);

	//for randTest only
	virtual void SetRandGen(RandDouble*);
	virtual void SetReport(CReport*,size_t);
};

} //end namespace CORINET

#endif //CORINET_EXECUTIONIMPL

