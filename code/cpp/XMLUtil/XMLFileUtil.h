/*********************************************************************************************
 * Name      :  XMLFileUtil.h
 *
 * Purpose   :  File utility functions.
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

#ifndef CORINET_XMLFILEUTIL
#define CORINET_XMLFILEUTIL

#include <Platform/Platform.h>
#include <string>
#include <vector>
#include <xercesc/util/XercesDefs.hpp>

namespace XERCES_CPP_NAMESPACE {
	class XMLFormatTarget;
}

namespace CORINET {

class XMLFileUtil {
public:
	static std::string GetFullPath(const XMLCh* const fileName);
	static void GetFullPath(XMLCh* const fullPath,const XMLCh* const fileName);
	static void GetFullPath(XMLCh* const fullPath,const std::string& fileName);
	static void WriteToTarget(char* str,size_t numchars,XERCES_CPP_NAMESPACE::XMLFormatTarget*);
};

} //end namespace CORINET

#endif //CORINET_XMLFILEUTIL

