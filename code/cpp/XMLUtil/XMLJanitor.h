/*********************************************************************************************
 * Name      :  XMLJanitor.h
 *
 * Purpose   :  Releasing vectors of XMLCh*.
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

#ifndef CORINET_XMLJANITOR
#define CORINET_XMLJANITOR

#include <Platform/Platform.h>
#include <vector>
#include <xercesc/util/XercesDefs.hpp>

namespace CORINET {

class XMLJanitor {
	std::vector<XMLCh*>& mGuarded;
public:
	XMLJanitor(std::vector<XMLCh*>&);
	~XMLJanitor();
};

} //end namespace CORINET

#endif //CORINET_XMLJANITOR




