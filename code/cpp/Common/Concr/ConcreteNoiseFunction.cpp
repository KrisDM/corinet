/*********************************************************************************************
 * Name      :  ConcreteNoiseFunction.cpp
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


#include "ConcreteNoiseFunction.h"
#include <Util/Iterator.h>
#include <Common/RandGen.h>

namespace CORINET {


FNoiseFunctionAdditive::FNoiseFunctionAdditive(size_t*,double*)
{

}


FNoiseFunctionAdditive::~FNoiseFunctionAdditive()
{

}


void FNoiseFunctionAdditive::operator()(SubArrayIterator& y)
{
	for(y.begin();!y.end();++y) {
		(*y) += (*pRG)();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////


FNoiseFunctionMultiplicative::FNoiseFunctionMultiplicative(size_t*,double* params)
{

}


FNoiseFunctionMultiplicative::~FNoiseFunctionMultiplicative()
{

}


void FNoiseFunctionMultiplicative::operator()(SubArrayIterator& y)
{
	for(y.begin();!y.end();++y) {
		(*y) *= (1.0 + (*pRG)());
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////


FNoiseFunctionAdditiveClip::FNoiseFunctionAdditiveClip(size_t*,double* params) : mLow(params[0]),mHigh(params[1])
{
	
}


FNoiseFunctionAdditiveClip::~FNoiseFunctionAdditiveClip()
{

}


void FNoiseFunctionAdditiveClip::operator()(SubArrayIterator& y)
{
	for(y.begin();!y.end();++y) {
		(*y) += (*pRG)();
		if ((*y) < mLow) 
			(*y) = mLow;
		else if ((*y) > mHigh)
			(*y) = mHigh;
	}
}


void FNoiseFunctionAdditiveClip::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mLow = val;
		break;
	case 1:
		mHigh = val;
		break;
	}
}


double FNoiseFunctionAdditiveClip::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mLow;
		break;
	case 1:
		v = mHigh;
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////


FNoiseFunctionMultiplicativeClip::FNoiseFunctionMultiplicativeClip(size_t*,double* params) : mLow(params[0]),mHigh(params[1])
{
	
}


FNoiseFunctionMultiplicativeClip::~FNoiseFunctionMultiplicativeClip()
{

}


void FNoiseFunctionMultiplicativeClip::operator()(SubArrayIterator& y)
{
	for(y.begin();!y.end();++y) {
		(*y) *= (1.0 + (*pRG)());
		if ((*y) < mLow) 
			(*y) = mLow;
		else if ((*y) > mHigh)
			(*y) = mHigh;
	}
}


void FNoiseFunctionMultiplicativeClip::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mLow = val;
		break;
	case 1:
		mHigh = val;
		break;
	}
}


double FNoiseFunctionMultiplicativeClip::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mLow;
		break;
	case 1:
		v = mHigh;
		break;
	}
	return v;
}

} //end namespace CORINET

