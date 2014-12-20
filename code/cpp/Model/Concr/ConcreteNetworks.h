/*********************************************************************************************
 * Name      :  ConcreteNetworks.h
 *
 * Purpose   :  Concrete types of networks. Networks differ mainly in the order of operations
 *				such as integrating, learning and reset. Allowing the network to decide for 
 *				itself its next step allows a uniform execution mechanism for experiments.
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

#ifndef CORINET_NETWORKCONCR
#define CORINET_NETWORKCONCR

#include <Model/Impl/NetworkImpl.h>

namespace  CORINET {

class CNetworkDiscrete : public CNetworkImpl {
	size_t mCurrentIntegrationStep;
	size_t mPathLength;
public:
	CNetworkDiscrete(size_t*,double*);
	virtual ~CNetworkDiscrete();
	void Initialise();
	NextStep Integrate();
	NextStep Learn(bool);
	NextStep Reset(double);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CNetworkDynamic : public CNetworkImpl {
	double mCurrentTime;
	double mStepsPerTimeUnit;
	double mTime4ThisPattern;
public:
	CNetworkDynamic(size_t*,double*);
	virtual ~CNetworkDynamic();
	void Initialise();
	NextStep SetInput(size_t,SubArrayIteratorConst&,double);
	NextStep Integrate();
	NextStep Learn(bool);
	NextStep Reset(double);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

} //end namespace CORINET

#endif //CORINET_NETWORKCONCR

