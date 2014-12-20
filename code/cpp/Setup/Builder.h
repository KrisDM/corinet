/*********************************************************************************************
 * Name      :  Builder.h
 *
 * Purpose   :  Create execution engine, networks, tasks and events. 
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

#ifndef CORINET_BUILDER
#define CORINET_BUILDER

#include <Platform/Platform.h>
#include <vector>

namespace CORINET {
	class CMessageHandler;
	class CEngine;
	class CExecution;

class CBuilder {
public:
	virtual ~CBuilder() {}
	//create functions
	virtual CEngine* CreateEngine(CMessageHandler*) =0;
	virtual CExecution* CreateExecution() =0;
	
	//cleanup functions
	virtual void ReleaseExecution() =0;
	virtual void ReleaseAll() =0;
};

} //end namespace CORINET

#endif //CORINET_BUILDER

