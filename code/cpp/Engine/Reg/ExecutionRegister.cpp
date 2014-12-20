/*********************************************************************************************
 * Name      :  ExecutionRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of executions with
 *				the factory manager for the abstract CExecution type. The name used is dependent
 *				on the type of execution engine.
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

#include <Engine/Concr/ConcreteExecution.h>
#include <Util/Factory.h>

namespace CORINET {

GET_REGISTER(CExecution)

REGISTER_CLASS_2(CExecution,CExecutionV1,executionV1)
REGISTER_CLASS_2(CExecution,CExecutionPatternGenerator,patternGenerator)
REGISTER_CLASS_2(CExecution,CExecutionRandTest,randTest)

} //end namespace CORINET
