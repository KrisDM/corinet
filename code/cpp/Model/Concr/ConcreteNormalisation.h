/*********************************************************************************************
 * Name      :  Normalisation.h
 *
 * Purpose   :  Normalisation rules for weights.
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

#ifndef CORINET_NORMALISATIONCONCR
#define CORINET_NORMALISATIONCONCR

#include <Model/Impl/NormalisationImpl.h>

namespace CORINET {


class FNormalisationNormNone : public FNormalisationImpl {
public:
	FNormalisationNormNone(size_t*,double*);
	virtual ~FNormalisationNormNone();
	void operator()(HWeights&);
};

class FNormalisationNormNode : public FNormalisationImpl {
	double mPosNorm,mPosConstrain,mPosMax,mNegNorm,mNegConstrain,mNegMax;
public:
	FNormalisationNormNode(size_t*,double*);
	virtual ~FNormalisationNormNode();
	void operator()(HWeights&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class FNormalisationNormInput : public FNormalisationImpl {
	double mPosNorm,mPosConstrain,mPosMax,mNegNorm,mNegConstrain,mNegMax;
public:
	FNormalisationNormInput(size_t*,double*);
	virtual ~FNormalisationNormInput();
	void operator()(HWeights&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

} //end namespace CORINET

#endif //CORINET_NORMALISATIONCONCR
