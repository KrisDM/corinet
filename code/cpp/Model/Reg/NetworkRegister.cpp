/*********************************************************************************************
 * Name      :  NetworkRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of networks with
 *				the factory manager for the abstract CNetwork type. The name used here should
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

#include <Model/Concr/ConcreteNetworks.h>
#include <Util/Factory.h>

namespace CORINET {

GET_REGISTER(CNetwork)

REGISTER_CLASS_1(CNetwork,CNetworkDiscrete,discrete)
REGISTER_CLASS_1(CNetwork,CNetworkDynamic,dynamic)

} //end namespace CORINET
