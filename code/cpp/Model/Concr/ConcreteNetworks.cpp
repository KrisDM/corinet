/*********************************************************************************************
 * Name      :  ConcreteNetworks.cpp
 *
 * Purpose   :  Concrete types of networks. Networks differ mainly in the order of operations
 *				such as integrating, learning and reset. Allowing the network to decide for 
 *				itself its next step allows a uniform execution mechanism in the engine.
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

#include "ConcreteNetworks.h"
#include <Util/Iterator.h>
#include <Model/Block.h>

namespace CORINET {

CNetworkDiscrete::CNetworkDiscrete(size_t* s,double* params) : CNetworkImpl(s[0],s[1])
{
	mCurrentIntegrationStep = 0;
	mPathLength = static_cast<size_t>(params[0]);
}

CNetworkDiscrete::~CNetworkDiscrete()
{

}

void CNetworkDiscrete::Initialise()
{
	mCurrentIntegrationStep = 0;
	CNetworkImpl::Initialise();
}

NextStep CNetworkDiscrete::Integrate()
{
	bool conv = true;
	LBlockPool::iterator ite(mBlockPool.end());
	for(LBlockPool::iterator it=mBlockPool.begin();it!=ite;++it) {
		conv &= (*it)->Integrate();
	}

	if (conv) {
		if (++mCurrentIntegrationStep > mPathLength)
			return NEXT_LEARN;
	}
	if (mNodePool.max() == 0)
		return NEXT_LEARN;
	return NEXT_INTEGRATE;
}

NextStep CNetworkDiscrete::Learn(bool train)
{	
	return CNetworkImpl::Learn(train);
}

NextStep CNetworkDiscrete::Reset(double) 
{
	mCurrentIntegrationStep = 0;
	return CNetworkImpl::Reset();
}

void CNetworkDiscrete::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mPathLength = static_cast<size_t>(v);
		break;
	}
}

double CNetworkDiscrete::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = static_cast<double>(mPathLength);
		break;
	}
	return v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

CNetworkDynamic::CNetworkDynamic(size_t* s,double* params) : CNetworkImpl(s[0],s[1])
{
	mCurrentTime = 0.0;
	mStepsPerTimeUnit = params[0];
	mTime4ThisPattern = 0.0;
}

CNetworkDynamic::~CNetworkDynamic()
{

}

void CNetworkDynamic::Initialise()
{
	mCurrentTime = 0.0;
	mTime4ThisPattern = 0.0;
	CNetworkImpl::Initialise();
}

NextStep CNetworkDynamic::SetInput(size_t startindex,SubArrayIteratorConst& vals,double t)
{
	mCurrentTime = 0.0;
	mTime4ThisPattern = t;
	return CNetworkImpl::SetInput(startindex,vals,t);
}

NextStep CNetworkDynamic::Integrate()
{
	LBlockPool::iterator ite(mBlockPool.end());
	for(LBlockPool::iterator it=mBlockPool.begin();it!=ite;++it) {
		(*it)->Integrate();
	}
	return NEXT_LEARN;
}

NextStep CNetworkDynamic::Learn(bool train)
{
	CNetworkImpl::Learn(train);
	mCurrentTime += 1.0/mStepsPerTimeUnit;
	if (mCurrentTime + 1e-10 < mTime4ThisPattern) {
		return NEXT_INTEGRATE;
	}
	else
		return NEXT_ENGINE;
}

NextStep CNetworkDynamic::Reset(double t)
{
	mCurrentTime = 0.0;
	if (t < 0.0) {//do a quick reset of the whole network
		return CNetworkImpl::Reset();
	}
	else if (t > 0.0) {
		for(size_t i=0;i<mNumInputs;++i) {//present a 0 pattern to the input and run the network for a certain time
			mNodePool[i] = 0.0;
		}
		mTime4ThisPattern = t;
		return NEXT_INTEGRATE;
	}
	else //go straight to next pattern presentation without reset
		return NEXT_ENGINE;
}

void CNetworkDynamic::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mStepsPerTimeUnit = val;
		break;
	}
}

double CNetworkDynamic::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mStepsPerTimeUnit;
		break;
	}
	return v;
}

} //end namespace CORINET



