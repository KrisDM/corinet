/*********************************************************************************************
 * Name      :  ConcreteRandInt.h
 *
 * Purpose   :  Random distributions of ints.
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

#ifndef CORINET_RANDINTCONCR
#define CORINET_RANDINTCONCR

#include <Common/Impl/RandIntImpl.h>
#include <list>

namespace CORINET {

class RandUniInt : public RandIntImpl {//uniform random int in interval [low,high[
	int mLow,mHigh;
public:
	RandUniInt(size_t*,double*);
	virtual ~RandUniInt();
	int operator()();
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class RandSequence : public RandIntImpl {//random, non-repeating sequence of integers in interval [0,high[
	int mHigh;
	std::list<int> mSequence;
public:
	RandSequence(size_t*,double*);
	virtual ~RandSequence();
	int operator()();
	int operator()(int);
	void Seed();
	void Seed(size_t);
	void Reset();
	void SetParam(size_t,double);
	double GetParam(size_t);
};

} //end namespace CORINET

#endif //CORINET_RANDINTCONCR


