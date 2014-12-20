/*********************************************************************************************
 * Name      :  StatusImpl.cpp
 *
 * Purpose   :  Implementation class providing information on the status of the experiment.
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

#include "ConcreteStatus.h"
#include <Engine/ExTimeInfo.h>
#include <Client/MessageHandler.h>
#include <cstdio>

namespace CORINET {

CStatusEngineV1::CStatusEngineV1() : mCurrentExecution(0),mTotalExecutions(0),ost()
{
	
}
	
CStatusEngineV1::~CStatusEngineV1()
{

}
	
void CStatusEngineV1::operator()(CExTimeInfo* pET)
{
	ost << "EXECUTION " << mCurrentExecution+1 << "/" << mTotalExecutions << "    CYCLE " << pET->GetCycle()+1 << "/" << pET->GetTotalCycles() << "       " << '\0';	
	ost.seekp(0);
	pMessageHandler->HandleAndFlush(ost.str());
}

void CStatusEngineV1::IncrExecution()
{
	++mCurrentExecution;
}

void CStatusEngineV1::SetTotalExecutions(size_t tex)
{
	mTotalExecutions = tex;
}

} //end namespace CORINET

