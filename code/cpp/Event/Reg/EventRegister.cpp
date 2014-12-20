/*********************************************************************************************
 * Name      :  EventRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of events with
 *				the factory manager for the abstract CEvent type. The name used here should
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

#include <Event/Concr/ConcreteEvents.h>
#include <Util/Factory.h>

namespace CORINET {

GET_REGISTER(CEvent)

REGISTER_CLASS_2(CEvent,CEventModel1,eventModelV1)

} //end namespace CORINET
