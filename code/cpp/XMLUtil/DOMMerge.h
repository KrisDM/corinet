/*********************************************************************************************
 * Name      :  DOMMerge.h
 *
 * Purpose   :  Merges two or more validation documents (sandbox files) into 1 DOM.
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

#ifndef CORINET_DOMMERGE
#define CORINET_DOMMERGE

#include <Platform/Platform.h>
#include <xercesc/dom/DOM.hpp>

namespace CORINET {

class CDOMMerge {
	static void MergeType(XERCES_CPP_NAMESPACE::DOMDocument*,const XERCES_CPP_NAMESPACE::DOMDocument*,
				   XERCES_CPP_NAMESPACE::DOMErrorHandler*,const XMLCh*);
public:
	~CDOMMerge() {}
	static void Merge(XERCES_CPP_NAMESPACE::DOMDocument*,const XERCES_CPP_NAMESPACE::DOMDocument*,
					  XERCES_CPP_NAMESPACE::DOMErrorHandler*);
};

} //end namespace CORINET

#endif //CORINET_DOMMERGE

