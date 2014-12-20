/*********************************************************************************************
 * Name      :  ClientRegister.cpp
 *
 * Purpose   :  Register of client applications.
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

#include <Client/ClientRegister.h>
#include "ClientImpl.h"
#include "MessageHandlerImpl.h"

namespace CORINET {
	
CClientRegister::~CClientRegister()
{

}

CClient* CClientRegister::GetClient(const std::string& appInputFormat,const std::string& appEnvironment,bool quiet)
{
	CMessageHandler* theHandler = 0;
	CClient* theApp = 0;
	if (appEnvironment == "console") {
		theHandler = new CMessageHandlerConsole(quiet);
	}
	if (appInputFormat == "xml") {
		theApp = new CClientXML(theHandler);
	}
	return theApp;
}

void CClientRegister::Release(CClient* theApp)
{
	if (theApp) {
		delete theApp;
	}
}

} //end namespace CORINET


