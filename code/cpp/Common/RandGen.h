/*********************************************************************************************
 * Name      :  RandGen.h
 *
 * Purpose   :  Abstract interface for pseudo random number generators.
 *
 * Notes	 :	The actual method for generating random numbers is not 
 *				guaranteed machine-independent and may not work on all processors.
 *				See the implementation files for compatibility issues.
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

#ifndef CORINET_RANDGEN
#define CORINET_RANDGEN

#include <Platform/Platform.h>
#include <Util/ParamInterface.h>

namespace CORINET {

class RandGen : public CParamInterface {
public:
	virtual ~RandGen() {}
	virtual void Seed() =0;
	virtual void Seed(size_t) =0;
	virtual void Reset() =0;	
};

class RandInt : public RandGen {
public:
	virtual ~RandInt() {}
	virtual int operator()() =0;
};

class RandDouble : public RandGen {
public:
	virtual ~RandDouble() {}
	virtual double operator()() =0;
};

} //end namespace CORINET

#endif //CORINET_RANDGEN


