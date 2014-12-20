/*********************************************************************************************
 * Name      :  StatusRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of CStatus with
 *				the factory manager for the abstract CStatus type. 
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

#include <Engine/Concr/ConcreteStatus.h>
#include <Util/Factory.h>

namespace CORINET {

GET_REGISTER(CStatus)

REGISTER_CLASS_2(CStatus,CStatusEngineV1,engineV1)

} //end namespace CORINET
