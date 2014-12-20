/*********************************************************************************************
 * Name      :  XMLRegister.cpp
 *
 * Purpose   :  Get specific handlers from here.
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

#include <xercesc/dom/DOM.hpp>
#include <XMLUtil/XMLRegister.h>
#include "DOMErrorImpl.h"

XERCES_CPP_NAMESPACE_USE

namespace CORINET {

CXMLRegister::~CXMLRegister()
{

}

DOMErrorHandler* CXMLRegister::CreateErrorHandler(CMessageHandler* const pmes)
{
	DOMErrorHandler* eHandler = new CErrorHandlerImpl(pmes);
	return eHandler;
}

} //end namespace CORINET


