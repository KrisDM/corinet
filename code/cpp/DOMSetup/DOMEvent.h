/*********************************************************************************************
 * Name      :  DOMEvent.h
 *
 * Purpose   :  Interface for handling event handlers and child elements.
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

#ifndef CORINET_DOMEVENT
#define CORINET_DOMEVENT

#include <Platform/Platform.h>
#include <xercesc/dom/DOM.hpp>
#include <vector>
#include <string>

namespace CORINET {
	struct SEventMaker;
	struct SMaker;

class CDOMEvent {
	
public:
	virtual ~CDOMEvent() {}

	virtual void Handle(const XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create) =0;

	//access functions
	virtual SEventMaker* GetEventMaker(const XERCES_CPP_NAMESPACE::DOMElement*) =0;
	virtual SMaker* GetMaker(const XERCES_CPP_NAMESPACE::DOMElement*) =0;
	virtual const std::vector<const XERCES_CPP_NAMESPACE::DOMElement*>* GetPartEvents(const XERCES_CPP_NAMESPACE::DOMElement*) =0;
	virtual bool HasLocation(const std::string&) =0;
	//cleanup
	virtual void ReleaseAll() =0;
};

} //end namespace CORINET

#endif //CORINET_DOMEVENT




