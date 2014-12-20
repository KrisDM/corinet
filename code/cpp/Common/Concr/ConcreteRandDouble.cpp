/*********************************************************************************************
 * Name      :  ConcreteRandDouble.cpp
 *
 * Purpose   :  Various random distributions of doubles.
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

#include "ConcreteRandDouble.h"
#include <cmath>

namespace CORINET {


RandUniDouble::RandUniDouble(size_t*,double* params) : mLow(params[0]),mHigh(params[1])
{
	
}

RandUniDouble::~RandUniDouble()
{

}

double RandUniDouble::operator()()
{
	return (mHigh-mLow)*mDraw.fdraw() + mLow;
}

void RandUniDouble::SetParam(size_t p,double v)
{
	switch (p) {
	case 0: 
		mLow = v;
		break;
	case 1:
		mHigh = v;
		break;
	}
}

double RandUniDouble::GetParam(size_t p)
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

//////////////////////////////////////////////////////////////////////////////////////////////////

RandUniDoublePart::RandUniDoublePart(size_t*,double* params) : mLow(params[0]),mHigh(params[1]),mProb(params[2])
{

}

RandUniDoublePart::~RandUniDoublePart()
{

}

double RandUniDoublePart::operator()()
{
	if (mDraw.fdraw() < mProb) 
		return (mHigh-mLow)*mDraw.fdraw() + mLow; 
	else 
		return 0.0;
}

void RandUniDoublePart::SetParam(size_t p,double v)
{
	switch (p) {
	case 0: 
		mLow = v;
		break;
	case 1:
		mHigh = v;
		break;
	case 2:
		mProb = v;
		break;
	}
}

double RandUniDoublePart::GetParam(size_t p)
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
		v = mProb;
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

RandNormal::RandNormal(size_t*,double* params) : mMean(params[0]),mStd(params[1])
{
	bFlag = false;
	mRandVal = 0.0;
}

RandNormal::~RandNormal()
{

}

double RandNormal::operator()() 
{
	if (bFlag) {
		bFlag = false;
		return mRandVal;
	}
	else {
		double tmp1,tmp2,rsq;
		do {
			tmp1 = 2.0*mDraw.fdraw() - 1.0;
			tmp2 = 2.0*mDraw.fdraw() - 1.0;
			rsq = tmp1*tmp1 + tmp2*tmp2;
		} 
		while (rsq >= 1.0 || rsq == 0);
		double fac = sqrt(-2.0*log(rsq)/rsq);
		mRandVal = mMean + tmp1*fac*mStd;
		bFlag = true;
		return mMean + tmp2*fac*mStd;
	}	
}

void RandNormal::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mMean = v;
		break;
	case 1:
		mStd = v;
		break;
	}
}

double RandNormal::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mMean;
		break;
	case 1:
		v = mStd;
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

RandExp1::RandExp1(size_t*,double* params) : mMean(params[0])
{
	
}

RandExp1::~RandExp1()
{

}

double RandExp1::operator()() 
{
	return -mMean*log(mDraw.fdraw());
}

void RandExp1::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mMean = v;
		break;
	}
}

double RandExp1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mMean;
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

RandLog1::RandLog1(size_t*,double* params) : mHigh(params[0]) 
{
	
}

RandLog1::~RandLog1()
{

}

double RandLog1::operator()() 
{
	return mHigh*mDraw.fdraw()*mDraw.fdraw();
}

void RandLog1::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mHigh = v;
		break;
	}
}

double RandLog1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mHigh;
		break;
	}
	return v;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

} //end namespace CORINET



