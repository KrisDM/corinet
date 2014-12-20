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

#include "ExTimeInfoImpl.h"

namespace CORINET {

CExTimeInfoImpl::~CExTimeInfoImpl()
{

}

size_t CExTimeInfoImpl::GetTotalCycles() const
{
	return 0;
}
	
size_t CExTimeInfoImpl::GetTotalConfigs() const
{
	return 0;
}

size_t CExTimeInfoImpl::GetTotalRuns() const
{
	return 0;
}

size_t CExTimeInfoImpl::GetCycle() const
{
	return 0;
}

size_t CExTimeInfoImpl::GetConfig() const
{
	return 0;
}

size_t CExTimeInfoImpl::GetRun() const
{
	return 0;
}

size_t CExTimeInfoImpl::GetPartEntry() const
{
	return 0;
}

size_t CExTimeInfoImpl::GetGlobalIteration() const
{
	return 0;
}

size_t CExTimeInfoImpl::GetIteration() const
{
	return 0;
}

size_t CExTimeInfoImpl::GetIntegration() const
{
	return 0;
}
	
CExecutionElement* CExTimeInfoImpl::GetPart() const
{
	return 0;
}

CTask* CExTimeInfoImpl::GetPartTasks() const
{
	return 0;
}

CNetwork* CExTimeInfoImpl::GetNetwork() const
{
	return 0;
}
	
void CExTimeInfoImpl::IncrConfig()
{
	
}

void CExTimeInfoImpl::IncrRun()
{
	
}

void CExTimeInfoImpl::IncrIteration()
{
	
}

void CExTimeInfoImpl::IncrIntegration()
{
	
}

void CExTimeInfoImpl::SetTotalConfigs(size_t v)
{
	
}

void CExTimeInfoImpl::SetTotalRuns(size_t v)
{
	
}

void CExTimeInfoImpl::SetConfig(size_t v)
{
	
}

void CExTimeInfoImpl::SetRun(size_t v)
{

}

void CExTimeInfoImpl::SetPartEntry(size_t v)
{
	
}

void CExTimeInfoImpl::SetGlobalIteration(size_t v)
{
	
}
		
void CExTimeInfoImpl::SetIteration(size_t v)
{
	
}

void CExTimeInfoImpl::SetIntegration(size_t v)
{
	
}

void CExTimeInfoImpl::SetPart(CExecutionElement* pe)
{
	
}
	
void CExTimeInfoImpl::SetNetwork(CNetwork* pn)
{
	
}

void CExTimeInfoImpl::AddTask(CTask* pt)
{
	
}

void CExTimeInfoImpl::ClearTasks()
{
	
}

} //end namespace CORINET



