/*********************************************************************************************
 * Name      :  DOMRegister.h
 *
 * Purpose   :  Get a suitable DOM handler from here.
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

#ifndef CORINET_DOMREGISTER
#define CORINET_DOMREGISTER

#include <Platform/Platform.h>
#include <string>

namespace XERCES_CPP_NAMESPACE {
	class DOMDocument;
}

namespace CORINET {
	class CDOMHandler;
	
class CDOMRegister {
public:
	~CDOMRegister();
	static CDOMHandler* CreateHandler(const XERCES_CPP_NAMESPACE::DOMDocument*);
};

} //end namespace CORINET

#endif //CORINET_DOMREGISTER

