/*********************************************************************************************
 * Name      :  Loop.h
 *
 * Purpose   :  Functionality for running loops over multiple parameter or weight values.
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

#ifndef CORINET_LOOP
#define CORINET_LOOP

#include <Util/ParamInterface.h>

namespace CORINET {

class CLoops {
public:
	virtual ~CLoops() {}
	virtual void Begin() =0;
	virtual void operator++() =0;
	virtual size_t Configs() const =0;
};

class CLoop {
public:
	virtual ~CLoop() {}
	virtual void Begin() =0;
	virtual size_t operator++() =0;
	virtual size_t Configs() const =0;
};

class CLoopElement {
public:
	virtual ~CLoopElement() {}
	virtual void Update(size_t) =0;
	virtual size_t Size() const =0;
};

} //end namespace CORINET

#endif //CORINET_LOOP

