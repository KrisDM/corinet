/*********************************************************************************************
 * Name      :  ConcreteEngine.cpp
 *
 * Purpose   :  Concrete types of execution engine.
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

#include "ConcreteEngine.h"
#include <Setup/Builder.h>
#include <Engine/ExTimeInfo.h>
#include <Engine/Status.h>
#include <Engine/Execution.h>

namespace CORINET {

CEngineV1::CEngineV1() : pStatus(0)
{

}

CEngineV1::~CEngineV1()
{

}

void CEngineV1::Execute(CBuilder* pbuilder)
{
	CExecution* thisExecution = pbuilder->CreateExecution();
	while (thisExecution) {
		(*thisExecution)(pStatus);
		pbuilder->ReleaseExecution();
		if (pStatus)
			pStatus->IncrExecution();
		thisExecution = pbuilder->CreateExecution();
	}
}

void CEngineV1::SetStatus(CStatus* pstatus)
{
	pStatus = pstatus;
}

} //end namespace CORINET
