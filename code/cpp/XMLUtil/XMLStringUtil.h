/*********************************************************************************************
 * Name      :  XMLStringUtil.h
 *
 * Purpose   :  Utility functions for maninpulation of XMLCh strings. Wrapping useful functions
 *				of the xerces-c XMLString class and providing a few extra.
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

#ifndef CORINET_XMLSTRINGUTIL
#define CORINET_XMLSTRINGUTIL

#include <Platform/Platform.h>
#include <string>
#include <vector>
#include <xercesc/util/XercesDefs.hpp>

namespace CORINET {

class XMLStringUtil {
public:
	static int XML2Int(const XMLCh* const);
	static double XML2Dbl(const XMLCh* const);
	static std::string XML2Str(const XMLCh* const);
	static XMLCh* Str2XML(const std::string&);
	static void Str2XML(const std::string&,XMLCh* const,size_t);
	static void Int2XML(int,XMLCh* const,size_t);
	static void Dbl2XML(double,XMLCh* const,size_t);
	static std::vector<XMLCh*> Tokenise(const XMLCh* const);
	static XMLCh* Replicate(const XMLCh* const);
	static void Copy(XMLCh* const,const XMLCh* const);
	static void Append(XMLCh* const,const XMLCh* const);
	static void AppendWSpace(XMLCh* const,const XMLCh* const);
	static bool Equals(const XMLCh* const,const XMLCh* const);
	static bool EndsWith(const XMLCh* const,const XMLCh* const);
	static bool Contains(const XMLCh* const,XMLCh);
	static void FixURI(XMLCh* const);
	static void Space2Hex(XMLCh* const);
	static void CollapseWS(XMLCh* const);
	static void Release(XMLCh*);
	static void Release(std::vector<XMLCh*>&);
};

} //end namespace CORINET

#endif //CORINET_XMLSTRINGUTIL

