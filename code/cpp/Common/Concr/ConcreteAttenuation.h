/*********************************************************************************************
 * Name      :  ConcreteAttenuation.h
 *
 * Purpose   :  Concrete attenuation functions.
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

#ifndef CORINET_ATTENUATIONCONCR
#define CORINET_ATTENUATIONCONCR

#include <valarray>
#include <Common/Impl/AttenuationImpl.h>

namespace CORINET {

class FAttenuationClipLow : public FAttenuationImpl {
	double mLow;
public:
	FAttenuationClipLow(size_t*,double*);
	virtual ~FAttenuationClipLow();
	void operator()(SubArrayIterator&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class FAttenuationClip : public FAttenuationImpl {
	double mLow,mHigh;
public:
	FAttenuationClip(size_t*,double*);
	virtual ~FAttenuationClip();
	void operator()(SubArrayIterator&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class FAttenuationTime1 : public FAttenuationImpl {
	std::valarray<double> yCum;
	double mLow,mHigh;
	double mTauC,mNTauC;	
public:
	FAttenuationTime1(size_t*,double*);
	virtual ~FAttenuationTime1();
	void Initialise();
	void Reset();
	void operator()(SubArrayIterator&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

} //end namespace CORINET

#endif //CORINET_ATTENUATIONCONCR
