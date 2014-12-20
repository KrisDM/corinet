/*********************************************************************************************
 * Name      :  ConcreteRandInt.cpp
 *
 * Purpose   :  Distributions of random ints.
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

#include "ConcreteRandInt.h"
#include <iterator>

namespace CORINET {

RandUniInt::RandUniInt(size_t*,double* params) : mLow(static_cast<int>(params[0])),mHigh(static_cast<int>(params[1]))
{
	
}

RandUniInt::~RandUniInt()
{

}

int RandUniInt::operator()()
{
	int r = static_cast<int>((mHigh-mLow)*mDraw.fdraw()) + mLow;
	return (r==mHigh)?(mHigh-1):r;
}

void RandUniInt::SetParam(size_t p,double v)
{
	switch (p) {
	case 0: 
		mLow = static_cast<int>(v);
		break;
	case 1:
		mHigh = static_cast<int>(v);
		break;
	}
}

double RandUniInt::GetParam(size_t p)
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

RandSequence::RandSequence(size_t*,double* params) 
	: mHigh(static_cast<int>(params[0])),mSequence()
{
	
}

RandSequence::~RandSequence()
{

}

int RandSequence::operator()()
{
	if (!mSequence.size()) {
		for(int i=0;i<mHigh;++i) 
			mSequence.push_back(i);
	}
	std::list<int>::iterator it = mSequence.begin();
	std::advance(it,(*this)(mSequence.size()));
	int val = *it;
	mSequence.erase(it);
	return val;
}

int RandSequence::operator()(int high)
{
	int r = static_cast<int>((high)*mDraw.fdraw());
	return (r==high)?(high-1):r;
}


void RandSequence::Seed()
{
	Reset();
	RandIntImpl::Seed();
}

void RandSequence::Seed(size_t s)
{
	Reset();
	RandIntImpl::Seed(s);
}

void RandSequence::Reset()
{
	mSequence.clear();
}

void RandSequence::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mHigh = static_cast<int>(v);
		mSequence.clear();
		break;
	}
}

double RandSequence::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0: 
		v = mHigh;
		break;
	}
	return v;
}

} //end namespace CORINET



