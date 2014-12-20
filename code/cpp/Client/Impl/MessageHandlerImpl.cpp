/*********************************************************************************************
 * Name      :  MessageHandlerImpl.cpp
 *
 * Purpose   :  Implementation handling messages from client to the application environment.
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

#include "MessageHandlerImpl.h"
#include <iostream>

namespace CORINET {
	
	CMessageHandlerConsole::CMessageHandlerConsole(bool quiet) : bQuiet(quiet)
{

}
	
CMessageHandlerConsole::~CMessageHandlerConsole()
{

}
	
void CMessageHandlerConsole::Handle(const std::string& message,bool force)
{
	if (force || !bQuiet)
		std::cout << "\n" << message << "\n" << std::flush;;
}

void CMessageHandlerConsole::HandleAndFlush(const std::string& message,bool force)
{
	if (force || !bQuiet)
		std::cout << "\r" << message << std::flush;
}

} //end namespace CORINET
