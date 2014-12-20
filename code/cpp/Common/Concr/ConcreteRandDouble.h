/*********************************************************************************************
 * Name      :  ConcreteRandDouble.h
 *
 * Purpose   :  Classes for different distributions of doubles.
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

#ifndef CORINET_RANDDOUBLECONCR
#define CORINET_RANDDOUBLECONCR

#include <Common/Impl/RandDoubleImpl.h>

namespace CORINET {

class RandUniDouble : public RandDoubleImpl {//uniform random double in interval [low,high[
	double mLow,mHigh;
public:
	RandUniDouble(size_t*,double*);
	virtual ~RandUniDouble();
	double operator()();
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class RandUniDoublePart : public RandDoubleImpl {//uniform random double in interval [low,high[ with probability mProb, otherwise 0
	double mLow,mHigh,mProb;
public:
	RandUniDoublePart(size_t*,double*);
	virtual ~RandUniDoublePart();
	double operator()();
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class RandNormal : public RandDoubleImpl {//normal distribution
	double mMean,mStd;
	double mRandVal;
	bool bFlag;
public:
	RandNormal(size_t*,double*);
	virtual ~RandNormal();
	double operator()();
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class RandExp1 : public RandDoubleImpl {//exponential distribution
	double mMean;
public:
	RandExp1(size_t*,double*);
	virtual ~RandExp1();
	double operator()();
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class RandLog1 : public RandDoubleImpl {//a simple logarithmic distribution in interval [0,high[
	double mHigh;
public:
	RandLog1(size_t*,double*);
	virtual ~RandLog1();
	double operator()();
	void SetParam(size_t,double);
	double GetParam(size_t);
};

} //end namespace CORINET

#endif //CORINET_RANDDOUBLECONCR

