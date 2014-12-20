/*********************************************************************************************
 * Name      :  ConcreteAttenuation.cpp
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


#include "ConcreteAttenuation.h"
#include <Util/Iterator.h>

namespace CORINET {

///////////////////////////////////////////////////////////////////////////////////////////////////////

FAttenuationClipLow::FAttenuationClipLow(size_t*,double* params) : mLow(params[0])
{
	
}

FAttenuationClipLow::~FAttenuationClipLow()
{

}

void FAttenuationClipLow::operator()(SubArrayIterator& y)
{
	for(y.begin();!y.end();++y) {
		if ((*y) < mLow)
			(*y) = mLow;
	}
}

void FAttenuationClipLow::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mLow = val;
		break;
	}
}

double FAttenuationClipLow::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mLow;
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

FAttenuationClip::FAttenuationClip(size_t*,double* params) : mLow(params[0]),mHigh(params[1])
{
	
}

FAttenuationClip::~FAttenuationClip()
{

}

void FAttenuationClip::operator()(SubArrayIterator& y)
{
	for(y.begin();!y.end();++y) {
		if ((*y) < mLow) 
			(*y) = mLow;
		else if ((*y) > mHigh)
			(*y) = mHigh;
	}
}

void FAttenuationClip::SetParam(size_t p,double val)
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

double FAttenuationClip::GetParam(size_t p)
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

FAttenuationTime1::FAttenuationTime1(size_t* s,double* params) : yCum(0.0,s[0]),mLow(params[0]),mHigh(params[1]),
	mTauC(params[2]),mNTauC(1-params[2])
{
	
}

FAttenuationTime1::~FAttenuationTime1()
{

}

void FAttenuationTime1::Initialise()
{
	yCum = 0.0;
}

void FAttenuationTime1::Reset()
{
	yCum = 0.0;
}

void FAttenuationTime1::operator()(SubArrayIterator& y)
{
	for(size_t j=0,js=y.size();j<js;++j) {
		y[j] /= (1.0+yCum[j]);
		if (y[j] < mLow) 
			y[j] = mLow;
		else if (y[j] > mHigh)
			y[j] = mHigh;
		yCum[j] = mTauC*y[j] +mNTauC*yCum[j];
		if (yCum[j] < gPrecision)
			yCum[j] = 0.0;
	}
}

void FAttenuationTime1::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mLow = val;
		break;
	case 1:
		mHigh = val;
		break;
	case 2:
		mTauC = val;
		mNTauC = 1 - val;
		break;
	}
}

double FAttenuationTime1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mLow;
		break;
	case 1:
		v = mHigh;
		break;
	case 2:
		v = mTauC;
		break;
	}
	return v;
}


} //end namespace CORINET
