/*********************************************************************************************
 * Name      :  DOMExecution.h
 *
 * Purpose   :  Interface for handling execution makers and child elements.
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

#ifndef CORINET_DOMEXECUTION
#define CORINET_DOMEXECUTION

#include <Platform/Platform.h>
#include <xercesc/dom/DOM.hpp>

namespace CORINET {
	

class CDOMExecution {
	
public:
	virtual ~CDOMExecution() {}

	virtual void Handle(const XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create) =0;
	virtual void AddEvents(const XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create) =0;

	//access functions
	virtual SExecutionMaker* GetExecutionMaker(const XERCES_CPP_NAMESPACE::DOMElement*) =0;
	virtual SMaker* GetMaker(const XERCES_CPP_NAMESPACE::DOMElement*) =0;

	//cleanup
	virtual void ReleaseAll() =0;
};

} //end namespace CORINET

#endif //CORINET_DOMEXECUTION




