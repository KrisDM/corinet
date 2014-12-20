/*********************************************************************************************
 * Name      :  ExecutionImpl.cpp
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

#include "ExecutionImpl.h"

namespace CORINET {

CExecutionImpl::~CExecutionImpl()
{

}

void CExecutionImpl::AddNetwork(CNetwork*)
{

}

void CExecutionImpl::AddTask(CTask*)
{

}

void CExecutionImpl::AddEvent(CEvent*)
{

}

void CExecutionImpl::AddExecutionElement(CExecutionElement*)
{

}

void CExecutionImpl::AddLoops(CLoops*)
{

}

void CExecutionImpl::SetExTimeInfo(CExTimeInfo* pet)
{
	pExTimeInfo = pet;
}

void CExecutionImpl::SetRandGen(RandDouble*)
{

}

void CExecutionImpl::SetReport(CReport*,size_t)
{

}

} //end namespace CORINET
