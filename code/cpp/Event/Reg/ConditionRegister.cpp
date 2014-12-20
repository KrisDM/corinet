/*********************************************************************************************
 * Name      :  ConditionRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of conditions with
 *				the factory manager for the abstract FCondition type. The name used here should
 *				be the name used in XML CORINET language definition.
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

#include <Event/Concr/ConcreteConditions.h>
#include <Util/Factory.h>

namespace CORINET {

GET_REGISTER(FCondition)

REGISTER_CLASS_2(FCondition,FCMultiple,multiple)
REGISTER_CLASS_2(FCondition,FCEquals,equals)
REGISTER_CLASS_2(FCondition,FCGT,gt)
REGISTER_CLASS_2(FCondition,FCGTE,gteq)
REGISTER_CLASS_2(FCondition,FCLT,lt)
REGISTER_CLASS_2(FCondition,FCLTE,lteq)

} //end namespace CORINET
