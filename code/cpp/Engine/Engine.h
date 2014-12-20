/*********************************************************************************************
 * Name      :  Engine.h
 *
 * Purpose   :  Interface for the execution engine. An execution engine, when set up properly,
 *				creates and runs networks with the appropriate tasks as input, as specified by 
 *				one or more execution structures.
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

#ifndef CORINET_ENGINE
#define CORINET_ENGINE

#include <Platform/Platform.h>

namespace CORINET {
	class CBuilder;

class CEngine {
public:
	virtual ~CEngine() {}
	virtual void Execute(CBuilder*) =0;
};

} //end namespace CORINET

#endif //CORINET_ENGINE
