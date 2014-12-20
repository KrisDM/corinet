/*********************************************************************************************
 * Name      :  DOMGenerate.h
 *
 * Purpose   :  Generate C++ code from language definition file.
 *
 * Notes	 :	
 *
 * Info     :	http://www.corinet.org
 *
 * Copyright:	2006, King's College London
 *		
 * License  :   This program is free software; you can redistribute it and/or modify
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

#ifndef CORINET_DOMGENERATE
#define CORINET_DOMGENERATE

#include <XML/Error.h>

namespace XERCES_CPP_NAMESPACE {
	class DOMDocument;
}

namespace CORINETXML {
	using XERCES_CPP_NAMESPACE::DOMDocument;

class CDOMGenerate {
public:
	static void Generate(const DOMDocument*,const DOMDocument*,EBaseHandler*);
};

} //end namespace CORINETXML

#endif //CORINET_DOMMERGE
