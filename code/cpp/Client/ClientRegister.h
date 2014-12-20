/*********************************************************************************************
 * Name      :  ClientRegister.h
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

#ifndef CORINET_CLIENTREGISTER
#define CORINET_CLIENTREGISTER

#include <Platform/Platform.h>
#include <string>

namespace CORINET {
	class CClient;
	
class CClientRegister {
public:
	~CClientRegister();
	static CClient* GetClient(const std::string& appInputFormat,const std::string& appEnvironment,bool quiet);
	static void Release(CClient* clientApp);
};

} //end namespace CORINET

#endif //CORINET_CLIENTREGISTER

