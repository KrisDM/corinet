/*********************************************************************************************
 * Name      :  DOMDefaults.h
 *
 * Purpose   :  Interface for handling the defaults in an experiment setup document.
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

#ifndef CORINET_DOMDEFAULTS
#define CORINET_DOMDEFAULTS

#include <Platform/Platform.h>
#include <xercesc/dom/DOM.hpp>
#include <vector>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

class CDOMDefaults {
	
public:
	virtual ~CDOMDefaults() {}

	virtual void Handle(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler) =0;

	//access functions
	virtual const std::vector<const DOMElement*>* GetParams(const DOMElement*) =0;
	virtual const std::vector<const DOMElement*>* GetParams(const XMLCh*) =0;
	virtual const DOMElement* GetObject(const DOMElement*,const XMLCh*) =0;
	virtual const DOMElement* GetObject(const XMLCh*,const XMLCh*) =0;
	virtual const DOMElement* GetOutputFunction(size_t) =0;

	//cleanup
	virtual void ReleaseAll() =0;
};

} //end namespace CORINET

#endif //CORINET_DOMDEFAULTS



