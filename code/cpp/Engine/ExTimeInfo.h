/*********************************************************************************************
 * Name      :  ExTimeInfo.h
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

#ifndef CORINET_EXTIMEINFO
#define CORINET_EXTIMEINFO

#include <Platform/Platform.h>

namespace CORINET {
	class CTask;
	class CNetwork;
	class CExecutionElement;

class CExTimeInfo {
public:
	virtual ~CExTimeInfo() {}

	virtual size_t GetTotalCycles() const =0;
	virtual size_t GetTotalConfigs() const =0;
	virtual size_t GetTotalRuns() const =0;

	virtual size_t GetCycle() const =0;
	virtual size_t GetConfig() const =0;
	virtual size_t GetRun() const =0;

	virtual size_t GetPartEntry() const =0;
	virtual size_t GetGlobalIteration() const =0;
	virtual size_t GetIteration() const =0;
	virtual size_t GetIntegration() const =0;
	
	virtual CExecutionElement* GetPart() const =0;
	virtual CTask* GetPartTasks() const =0;
	virtual CNetwork* GetNetwork() const =0;
	
	virtual void IncrConfig() =0;
	virtual void IncrRun() =0;
	virtual void IncrIteration() =0;
	virtual void IncrIntegration() =0;

	virtual void SetTotalConfigs(size_t) =0;
	virtual void SetTotalRuns(size_t) =0;
	virtual void SetConfig(size_t) =0;
	virtual void SetRun(size_t) =0;
	virtual void SetPartEntry(size_t) =0;
	virtual void SetGlobalIteration(size_t) =0;
	virtual void SetIteration(size_t) =0;
	virtual void SetIntegration(size_t) =0;

	virtual void SetPart(CExecutionElement*) =0;
	virtual void SetNetwork(CNetwork*) =0;
	virtual void AddTask(CTask*) =0;
	virtual void ClearTasks() =0;
};

} //end namespace CORINET
	
#endif //CORINET_EXTIMEINFO
