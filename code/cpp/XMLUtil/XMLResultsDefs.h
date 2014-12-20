/*********************************************************************************************
 * Name      :  XMLResultsDefs.h
 *
 * Purpose   :  Keywords from CORINET Markup Language <results> files defined in Xerces-C XMLCh format.
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

#ifndef CORINET_XMLRESULTSDEFS
#define CORINET_XMLRESULTSDEFS

#include <Platform/Platform.h>
#include <xercesc/util/XMLUniDefs.hpp>

namespace CORINET {

class XMLResultsDefs {
public:
	//from results
	static const XMLCh results[];
	static const XMLCh execution[];
	static const XMLCh network[];
	static const XMLCh task[];
	static const XMLCh id[];
	static const XMLCh weights[];
	static const XMLCh synapses[];
	static const XMLCh values[];
	static const XMLCh type[];
	static const XMLCh config[];
	static const XMLCh cycle[];
	static const XMLCh i[];
	static const XMLCh n[];
	static const XMLCh p[];
	static const XMLCh r[];
	static const XMLCh run[];
	static const XMLCh s[];
	static const XMLCh v[];
	static const XMLCh w[];
	
	//various
	static const XMLCh LS[];
};

} //end namespace CORINET

#endif //CORINET_XMLRESULTSDEFS

