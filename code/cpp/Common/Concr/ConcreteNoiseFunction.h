/*********************************************************************************************
 * Name      :  ConcreteNoiseFunction.h
 *
 * Purpose   :  Concrete noise functions.
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

#ifndef CORINET_NOISEFUNCTIONCONCR
#define CORINET_NOISEFUNCTIONCONCR


#include <Common/Impl/NoiseFunctionImpl.h>

namespace CORINET {

class FNoiseFunctionAdditive : public FNoiseFunctionImpl {
public:
	FNoiseFunctionAdditive(size_t*,double*);
	virtual ~FNoiseFunctionAdditive();
	void operator()(SubArrayIterator&);
};

class FNoiseFunctionMultiplicative : public FNoiseFunctionImpl {
public:
	FNoiseFunctionMultiplicative(size_t*,double*);
	virtual ~FNoiseFunctionMultiplicative();
	void operator()(SubArrayIterator&);
};

class FNoiseFunctionAdditiveClip : public FNoiseFunctionImpl {
	double mLow,mHigh;
public:
	FNoiseFunctionAdditiveClip(size_t*,double*);
	virtual ~FNoiseFunctionAdditiveClip();
	void operator()(SubArrayIterator&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class FNoiseFunctionMultiplicativeClip : public FNoiseFunctionImpl {
	double mLow,mHigh;
public:
	FNoiseFunctionMultiplicativeClip(size_t*,double*);
	virtual ~FNoiseFunctionMultiplicativeClip();
	void operator()(SubArrayIterator&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

} //end namespace CORINET

#endif //CORINET_NOISEFUNCTIONCONCR

