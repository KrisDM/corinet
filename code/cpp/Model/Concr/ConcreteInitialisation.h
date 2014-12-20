/*********************************************************************************************
 * Name      :  ConcreteInitialisation.h
 *
 * Purpose   :  Concrete initialisation functions.
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

#ifndef CORINET_INITIALISATIONCONCR
#define CORINET_INITIALISATIONCONCR

#include <Model/Impl/InitialisationImpl.h>

namespace CORINET {

class FInitialisationExplicit : public FInitialisationImpl {
public:
	FInitialisationExplicit(size_t*,double*);
	virtual ~FInitialisationExplicit();
	void operator()(HWeights&);
};

class FInitialisationValue : public FInitialisationImpl {
	double mValue;
public:
	FInitialisationValue(size_t*,double*);
	virtual ~FInitialisationValue();
	void operator()(HWeights&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class FInitialisationDiagonal : public FInitialisationImpl {
	double mValue;
public:
	FInitialisationDiagonal(size_t*,double*);
	virtual ~FInitialisationDiagonal();
	void operator()(HWeights&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class FInitialisationRandom : public FInitialisationImpl {
public:
	FInitialisationRandom(size_t*,double*);
	virtual ~FInitialisationRandom();
	void operator()(HWeights&);
};

class FInitialisationInputSize : public FInitialisationImpl {
public:
	FInitialisationInputSize(size_t*,double*);
	virtual ~FInitialisationInputSize();
	void operator()(HWeights&);
};

class FInitialisationNodeSize : public FInitialisationImpl {	
public:
	FInitialisationNodeSize(size_t*,double*);
	virtual ~FInitialisationNodeSize();
	void operator()(HWeights&);
};

} //end namespace CORINET

#endif //CORINET_INITIALISATIONCONCR
