/*********************************************************************************************
 * Name      :  ExTimeInfoImpl.h
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

#ifndef CORINET_EXTIMEINFOIMPL
#define CORINET_EXTIMEINFOIMPL

#include <Engine/ExTimeInfo.h>

namespace CORINET {

class CExTimeInfoImpl : public CExTimeInfo {
public:
	virtual ~CExTimeInfoImpl();

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

} //end namespace CORINET
	
#endif //CORINET_EXTIMEINFO

