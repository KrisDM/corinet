/*********************************************************************************************
 * Name      :  ConcreteLoops.cpp
 *
 * Purpose   :  Functionality for running loops over multiple parameter or weight values.
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

#include "ConcreteLoops.h"
#include <Util/ParamInterface.h>
#include <Model/Initialisation.h>
#include <limits>

namespace CORINET {

/////////////////////////////////////////////////////////////////////////////////////////////////////

CLoopsV1::CLoopsV1() : mTotalConfigs(1),mLoops()
{
	
}
	
CLoopsV1::~CLoopsV1() 
{
	
}

void CLoopsV1::Begin() 
{
	for(size_t i=mLoops.size();i>0;--i) {
		mLoops[i-1]->Begin();
	}
}

void CLoopsV1::operator++()
{
	for(size_t i=mLoops.size();i>0;--i) {
		if (++(*mLoops[i-1])) {
			break;
		}
	}
}
	
size_t CLoopsV1::Configs() const
{
	return mTotalConfigs;
}

void CLoopsV1::AddLoop(CLoop* pl) 
{
	mLoops.push_back(pl);
	mTotalConfigs *= pl->Configs();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CLoopV1::CLoopV1() : mCurrent(0),mConfigs(0),mLoopElements()
{
	
}

CLoopV1::~CLoopV1()
{
	
}

void CLoopV1::Begin()
{
	mCurrent = 0;
	for(size_t i=0,s=mLoopElements.size();i<s;++i) { 
		mLoopElements[i]->Update(mCurrent);
	}
}
	
size_t CLoopV1::operator++()
{
	if (++mCurrent == mConfigs) 
		mCurrent = 0;
	for(size_t i=0,s=mLoopElements.size();i<s;++i) { 
		mLoopElements[i]->Update(mCurrent);
	}
	return mCurrent;//returns 0 when this loop reaches the end of its parameter values
}
	
size_t CLoopV1::Configs() const 
{
	return mConfigs;
}

void CLoopV1::AddLoopElement(CLoopElement* pv)
{
	mLoopElements.push_back(pv);
}

void CLoopV1::SetSize(size_t c)
{
	mConfigs = c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CLoopVarV1::CLoopVarV1() : mParamNum(std::numeric_limits<size_t>::max()),pParamVals(0),mTargets()
{
	
}

CLoopVarV1::~CLoopVarV1()
{
	
}

void CLoopVarV1::Update(size_t valnum) 
{
	for(size_t i=0,s=mTargets.size();i<s;++i) {
		mTargets[i]->SetParam(mParamNum,(*pParamVals)[valnum]);
	}
}

size_t CLoopVarV1::Size() const
{
	return pParamVals->size();
}

void CLoopVarV1::AddValues(const std::valarray<double>* pv)
{
	pParamVals = pv;
}

void CLoopVarV1::AddTarget(void* pi,size_t param)
{
	mTargets.push_back(static_cast<CParamInterface*>(pi));
	mParamNum = param;
}

////////////////////////////////////////////////////////////////////////////////////////////////

CLoopWeightsV1::CLoopWeightsV1() : mWeightVals(),mTargets() 
{
	
}

CLoopWeightsV1::~CLoopWeightsV1()
{
	
}

void CLoopWeightsV1::Update(size_t valnum) 
{
	for(size_t i=0,s=mTargets.size();i<s;++i) {
		mTargets[i]->SetWPointer(mWeightVals[valnum]);
	}
}

size_t CLoopWeightsV1::Size() const
{
	return mWeightVals.size();
}

void CLoopWeightsV1::AddValues(const std::valarray<double>* pv)
{
	mWeightVals.push_back(pv);
}

void CLoopWeightsV1::AddTarget(void* pi,size_t)
{
	mTargets.push_back(static_cast<FInitialisation*>(pi));
}

////////////////////////////////////////////////////////////////////////////////////////////////




} //end namespace CORINET
