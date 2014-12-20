/*********************************************************************************************
 * Name      :  DOMErrorImpl.h
 *
 * Purpose   :  Implementation classes for ErrorHandler interface (derived from DOMErrorHandler).
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

#ifndef CORINET_DOMERRORIMPL
#define CORINET_DOMERRORIMPL

#include <XMLUtil/DOMError.h>
#include <sstream>

namespace CORINET {
	class CMessageHandler;

class CErrorHandlerImpl : public CErrorHandler {
	CMessageHandler* pMessageHandler;
	std::ostringstream ost;
public:
	CErrorHandlerImpl(CMessageHandler*);
	virtual ~CErrorHandlerImpl();
	bool handleError(const XERCES_CPP_NAMESPACE::DOMError&);
	void handleMessage(const std::string&); 
};

} //end namespace CORINET

#endif //CORINET_DOMERRORIMPL


