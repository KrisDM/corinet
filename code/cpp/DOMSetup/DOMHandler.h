/*********************************************************************************************
 * Name      :  DOMHandler.h
 *
 * Purpose   :  Interface for handling DOM.
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

#ifndef CORINET_DOMHANDLER
#define CORINET_DOMHANDLER

#include <Platform/Platform.h>
#include <xercesc/util/XercesDefs.hpp>

namespace XERCES_CPP_NAMESPACE {
	class DOMDocument;
	class DOMErrorHandler;
}

namespace CORINET {
	struct SEngineMaker;	

class CDOMHandler {	
public:
	virtual ~CDOMHandler() {}

	virtual void Handle(XERCES_CPP_NAMESPACE::DOMDocument* doc1,const XERCES_CPP_NAMESPACE::DOMDocument* doc2,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create) =0;

	//access functions
	virtual SEngineMaker* GetEngineMaker() =0;

	//cleanup
	virtual void ReleaseAll() =0;
};

} //end namespace CORINET

#endif //CORINET_DOMHANDLER




