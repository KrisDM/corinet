/*********************************************************************************************
 * Name      :  Attenuation.h
 *
 * Purpose   :  Function objects implementing different operations on output values and patterns.
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

#ifndef CORINET_ATTENUATION
#define CORINET_ATTENUATION

#include <Util/ParamInterface.h>

namespace CORINET {
	class SubArrayIterator;

class FAttenuation : public CParamInterface {
public:
	virtual ~FAttenuation() {}
	virtual void Initialise() =0;
	virtual void operator()(SubArrayIterator&) =0;
	virtual void Reset() =0;
};

} //end namespace CORINET

#endif //CORINET_ATTENUATION

