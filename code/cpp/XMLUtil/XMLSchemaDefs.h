/*********************************************************************************************
 * Name      :  XMLSchemaLocations.h
 *
 * Purpose   :  Schema locations from CORINET Markup Language defined in Xerces-C XMLCh format.
 *				The locations are defined relative to the CORINETROOT environment variable.
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

#ifndef CORINET_XMLSCHEMALOCATIONS
#define CORINET_XMLSCHEMALOCATIONS

#include <xercesc/util/XMLUniDefs.hpp>
#include <Platform/Platform.h>

namespace CORINET {

class XMLSchemaNames {
public:
	static const XMLCh CORINETSetup[];
	static const XMLCh CORINETSetupList[];
	static const XMLCh CORINETDefinition[];
	static const XMLCh CORINETGenerator[];
	static const XMLCh CORINETResults[];
	static const XMLCh XSI[];
	static const XMLCh xsi[];
	static const XMLCh xmlns[];
	static const XMLCh schemaLocation[];
};

class XMLSchemaLocations {
public:
	static const XMLCh CORINETSetup[];
	static const XMLCh CORINETSetupList[];
	static const XMLCh CORINETDefinition[];
	static const XMLCh CORINETGenerator[];
	static const XMLCh CORINETResults[];
};

} //end namespace CORINET

#endif //CORINET_XMLSCHEMALOCATIONS

