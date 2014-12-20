/*********************************************************************************************
 * Name      :  OutputFunctionImpl.h
 *
 * Purpose   :  Function object implementing outputfunctions. This is still not a concrete 
 *				outputfunction, but a general base class implementing common functionality.
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

#ifndef CORINET_OUTPUTFUNCTIONIMPL
#define CORINET_OUTPUTFUNCTIONIMPL

#include <Model/OutputFunction.h>

namespace CORINET {
	class FAttenuation;
	class FNoiseFunction;
	
class FOutputFunctionImpl : public FOutputFunction {
protected:
	FAttenuation* pAttenuation;
	FNoiseFunction* pNoise;
public:
	virtual ~FOutputFunctionImpl();
	void Initialise();
	void Reset();
	void SetAttenuation(FAttenuation*);
	void SetNoise(FNoiseFunction*);		
};

} //end namespace CORINET

#endif //CORINET_OUTPUTFUNCTIONIMPL

