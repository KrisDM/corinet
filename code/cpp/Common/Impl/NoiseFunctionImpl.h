/*********************************************************************************************
 * Name      :  NoiseFunctionImpl.h
 *
 * Purpose   :  Function objects implementing noise effects in model and task.
 *				This is the implementation class.
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

#ifndef CORINET_NOISEFUNCTIONIMPL
#define CORINET_NOISEFUNCTIONIMPL

#include <Common/NoiseFunction.h>

namespace CORINET {
	class RandDouble;

class FNoiseFunctionImpl : public FNoiseFunction {
protected:
	RandDouble* pRG;
public:
	virtual ~FNoiseFunctionImpl();
	void Initialise();
	void Reset();
	void SetRandGen(RandDouble*);
};

} //end namespace CORINET

#endif //CORINET_NOISEFUNCTIONIMPL
