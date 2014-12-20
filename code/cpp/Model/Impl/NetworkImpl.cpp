/*********************************************************************************************
 * Name      :  NetworkImpl.cpp
 *
 * Purpose   :  Implementation of networks. A network consists of a collection of neuronblocks,
 *				the pool of all external input and nodevalues, and some bookkeeping information.
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

#include "NetworkImpl.h"
#include <Util/Iterator.h>
#include <Model/Block.h>

namespace CORINET {

CNetworkImpl::CNetworkImpl(size_t numinputs,size_t numnodes) : mNumInputs(numinputs),mNodePool(0.0,numinputs+numnodes)
{
	pNetStateConst = 0;
	pNetInputConst = 0;
	pNetOutputConst = 0;
	pNetIOConst = 0;
	pNetState = 0;
}

CNetworkImpl::~CNetworkImpl()
{	
	
}

void CNetworkImpl::Initialise()
{
	for(LBlockPool::iterator it=mBlockPool.begin(),ite(mBlockPool.end());it!=ite;++it) {
		(*it)->Initialise();
	}
	mNodePool = 0.0;
}

void CNetworkImpl::Finalise()
{

}

NextStep CNetworkImpl::SetInput(size_t startindex,SubArrayIteratorConst& vals,double)
{
	for(size_t i=0,is=vals.size();i<is;++i) 
		mNodePool[i+startindex] = vals[i];
	return NEXT_ENGINE;
}

NextStep CNetworkImpl::Integrate()
{
	return NEXT_LEARN;
}

void CNetworkImpl::CalculateOutput()
{
	LBlockPool::iterator ite(mBlockPool.end());
	for(LBlockPool::iterator it=mBlockPool.begin();it!=ite;++it) {
		(*it)->CalculateOutput();
	}
}

NextStep CNetworkImpl::Learn(bool train)
{
	if (train) {
		LBlockPool::iterator ite(mBlockPool.end());
		for(LBlockPool::iterator it=mBlockPool.begin();it!=ite;++it) {
			(*it)->Learn();
		}
	}
	return NEXT_ENGINE;
}

NextStep CNetworkImpl::Reset(double)
{
	LBlockPool::iterator ite(mBlockPool.end());
	for(LBlockPool::iterator it=mBlockPool.begin();it!=ite;++it) {
		(*it)->Reset();
	}
	mNodePool = 0.0;
	return NEXT_ENGINE;
}

void CNetworkImpl::AddBlock(CBlock* const pblock,bool outputBlock)
{
	mBlockPool.push_back(pblock);
	mOutputBlocks.push_back(outputBlock);
}

std::valarray<double>* CNetworkImpl::GetNodePool()
{
	return &mNodePool;
}

SubArrayIteratorConst* CNetworkImpl::GetStateConst()
{
	if (!pNetStateConst) {
		pNetStateConst = new SubArrayIteratorConst(&mNodePool,0,mNodePool.size());
	}
	return pNetStateConst;
}

SubArrayIteratorConst* CNetworkImpl::GetInputConst()
{
	if (!pNetInputConst) {
		pNetInputConst = new SubArrayIteratorConst(&mNodePool,0,mNumInputs);
	}
	return pNetInputConst;
}
	
MultipleSubArrayIteratorConst* CNetworkImpl::GetOutputConst()
{
	if (!pNetOutputConst) {
		pNetOutputConst = new MultipleSubArrayIteratorConst();
		for(size_t i=0,sb=mOutputBlocks.size();i<sb;++i) {
			if (mOutputBlocks[i]) {
				pNetOutputConst->AddSubArray(mBlockPool[i]->GetOutputConst());
			}
		}
	}
	return pNetOutputConst;
}
	
MultipleSubArrayIteratorConst* CNetworkImpl::GetIOConst()
{
	if (!pNetIOConst) {
		pNetIOConst = new MultipleSubArrayIteratorConst();
		pNetIOConst->AddSubArray(GetInputConst());
		for(size_t i=0,sb=mOutputBlocks.size();i<sb;++i) {
			if (mOutputBlocks[i]) {
				pNetIOConst->AddSubArray(mBlockPool[i]->GetOutputConst());
			}
		}
	}
	return pNetIOConst;
}
	
SubArrayIterator* CNetworkImpl::GetState()
{
	if (!pNetState) {
		pNetState = new SubArrayIterator(&mNodePool,0,mNodePool.size());
	}
	return pNetState;
}

} //end namespace CORINET



