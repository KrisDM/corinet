/*********************************************************************************************
 * Name      :  RandDoubleImpl.h
 *
 * Purpose   :  Implementation class for random generator returning doubles.
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

#ifndef CORINET_RANDDOUBLEIMPL
#define CORINET_RANDDOUBLEIMPL

#include <Common/RandGen.h>
#include "RandDraw.h"

namespace CORINET {

class RandDoubleImpl : public RandDouble {
protected:
	RandDraw mDraw;
public:
	virtual ~RandDoubleImpl() {}
	void Seed() {mDraw.seed();}
	void Seed(size_t s) {mDraw.seed(s);}
	void Reset() {}
};

} //end namespace CORINET

#endif //CORINET_RANDDOUBLEIMPL


