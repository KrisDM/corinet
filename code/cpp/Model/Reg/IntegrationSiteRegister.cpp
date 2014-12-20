/*********************************************************************************************
 * Name      :  IntegrationSiteRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of integration sites with
 *				the factory manager for the abstract CIntegrationSite type. The name used here should
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

#include <Model/Concr/ConcreteIntegrationSites.h>
#include <Util/Factory.h>

namespace CORINET {

GET_REGISTER(CIntegrationSite)

REGISTER_CLASS_1(CIntegrationSite,CIntegrationSiteAddInt1,addInt1)
REGISTER_CLASS_1(CIntegrationSite,CIntegrationSiteMaxInt1,maxInt1)
REGISTER_CLASS_1(CIntegrationSite,CIntegrationSiteCompInt1,compInt1)
REGISTER_CLASS_1(CIntegrationSite,CIntegrationSiteDisj1,disj1)
REGISTER_CLASS_1(CIntegrationSite,CIntegrationSiteDisj2,disj2)
REGISTER_CLASS_1(CIntegrationSite,CIntegrationSiteConj1,conj1)
REGISTER_CLASS_1(CIntegrationSite,CIntegrationSiteConj2,conj2)
REGISTER_CLASS_1(CIntegrationSite,CIntegrationSiteConj3,conj3)

} //end namespace CORINETFactory
