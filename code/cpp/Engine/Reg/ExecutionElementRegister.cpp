/*********************************************************************************************
 * Name      :  ExecutionElementRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of execution elements with
 *				the factory manager for the abstract CExecutionElement type. The name used here 
 *				is dependent on the XML format language and on the type of engine.
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

#include <Engine/Concr/ConcreteExecutionElement.h>
#include <Util/Factory.h>

namespace CORINET {

GET_REGISTER(CExecutionElement)

REGISTER_CLASS_2(CExecutionElement,CExecutionSequenceV1,sequenceV1) //doesn't take parameters
REGISTER_CLASS_1(CExecutionElement,CExecutionPartV1,partV1) //takes parameters

} //end namespace CORINET
