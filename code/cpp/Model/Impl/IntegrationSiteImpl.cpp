/*********************************************************************************************
 * Name      :  IntegrationSiteImpl.cpp
 *
 * Purpose   :  General base class for concrete integration sites. Common functionality is defined here.
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

#include "IntegrationSiteImpl.h"
#include <Model/Initialisation.h>
#include <Model/Normalisation.h>
#include <Model/Misc/Nodes.h>
#include <Model/Misc/Weights.h>
#include <Model/Misc/Synapses.h>

namespace CORINET {

CIntegrationSiteImpl::CIntegrationSiteImpl(size_t inputs,size_t nodes) 
	: pInputVals(0),mIntegrationVals(0.0,nodes),mWeights(inputs,nodes)
{
	pSiteInputConst = 0;
	pSiteInput = 0;
	pSiteOutputConst = 0;
	pSiteOutput = 0;
	pWeightsIteratorConst = 0;
	pWeightsIterator = 0;
	pSynapseWrapper = 0;
}

CIntegrationSiteImpl::~CIntegrationSiteImpl() 
{
	delete pInputVals;
	delete pSiteInputConst;
	delete pSiteInput;
	delete pSiteOutputConst;
	delete pSiteOutput;
	delete pWeightsIteratorConst;
	delete pWeightsIterator;
	delete pSynapseWrapper;
}

void CIntegrationSiteImpl::Initialise()
{
	pInit->Initialise();
	pNorm->Initialise();
	mIntegrationVals = 0.0;
	(*pInit)(mWeights);
	(*pNorm)(mWeights);
}

void CIntegrationSiteImpl::Reset()
{
	pInit->Reset();
	pNorm->Reset();
}

bool CIntegrationSiteImpl::Integrate(size_t,HBlockOutput&)
{
	return true;
}

bool CIntegrationSiteImpl::Learn(size_t,HBlockOutput&)
{
	return false;
}

void CIntegrationSiteImpl::SetInputIndices(std::valarray<double>* pnodepool,std::valarray<size_t>* pindex)
{
	pInputVals = new HIntegrationInput(pnodepool,pindex);
}

void CIntegrationSiteImpl::SetInitialisation(FInitialisation* pi)
{
	pInit = pi;
}

void CIntegrationSiteImpl::SetNormalisation(FNormalisation* pn)
{
	pNorm = pn;
}

IndirectIteratorConst* CIntegrationSiteImpl::GetInputConst()
{
	if (!pSiteInputConst)
		pSiteInputConst = new IndirectIteratorConst(*pInputVals);
	return pSiteInputConst;
}
	
IndirectIterator* CIntegrationSiteImpl::GetInput()
{
	if (!pSiteInput)
		pSiteInput = new IndirectIterator(*pInputVals);
	return pSiteInput;
}
	
SubArrayIteratorConst* CIntegrationSiteImpl::GetOutputConst()
{
	if (!pSiteOutputConst)
		pSiteOutputConst = new SubArrayIteratorConst(&mIntegrationVals,0,mIntegrationVals.size());
	return pSiteOutputConst;
}
	
SubArrayIterator* CIntegrationSiteImpl::GetOutput()
{
	if (!pSiteOutput)
		pSiteOutput = new SubArrayIterator(&mIntegrationVals,0,mIntegrationVals.size());
	return pSiteOutput;
}
	
MatrixIteratorConst* CIntegrationSiteImpl::GetWeightsConst()
{
	if (!pWeightsIteratorConst)
		pWeightsIteratorConst = new MatrixIteratorConst(mWeights.GetVals(),mWeights.NumInputs());
	return pWeightsIteratorConst;
}
	
MatrixIterator* CIntegrationSiteImpl::GetWeights()
{
	if (!pWeightsIterator)
		pWeightsIterator = new MatrixIterator(mWeights.GetVals(),mWeights.NumInputs());
	return pWeightsIterator;
}

SynapseWrapper* CIntegrationSiteImpl::GetSynapses()
{
	if (!pSynapseWrapper)
		pSynapseWrapper = new SynapsesDefault(mWeights.NumNodes(),GetOutputConst());
	return pSynapseWrapper;
}

} //end namespace CORINET


