/*********************************************************************************************
 * Name      :  BlockImpl.cpp
 *
 * Purpose   :  Common block functionality
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

#include "BlockImpl.h"
#include <Model/Misc/Nodes.h>
#include <Model/OutputFunction.h>
#include <Model/IntegrationSite.h>

namespace CORINET {

CBlockImpl::CBlockImpl() 
{
	pOutputVals = 0;
	pBlockOutputConst = 0;
	pBlockOutput = 0;
}
	
CBlockImpl::~CBlockImpl() 
{
	delete pOutputVals;
	delete pBlockOutputConst;
	delete pBlockOutput;
}

bool CBlockImpl::Integrate()
{
	return true;
}

bool CBlockImpl::Learn()
{
	return false;
}

void CBlockImpl::CalculateOutput()
{
	(*pOutputFun)(mIntValPointers,*pOutputVals);
}

void CBlockImpl::Initialise()
{
	for(LIntegrationSitePool::iterator it=mIntegrationSites.begin(),ite=mIntegrationSites.end();it!=ite;++it) {
		(*it)->Initialise();
	}
	pOutputFun->Initialise();
}

void CBlockImpl::Reset()
{
	const LIntegrationSitePool::iterator ite(mIntegrationSites.end());
	for(LIntegrationSitePool::iterator it=mIntegrationSites.begin();it!=ite;++it) {
		(*it)->Reset();
	}
	pOutputFun->Reset();
}
	
void CBlockImpl::AddIntegrationSite(CIntegrationSite* const site) 
{
	mIntegrationSites.push_back(site);
	mIntValPointers.push_back(site->GetOutputConst());
}
	
void CBlockImpl::SetOutputFunction(FOutputFunction* const pof)
{
	pOutputFun = pof;
}

void CBlockImpl::SetOutputIndices(std::valarray<double>* pnodepool,size_t b,size_t s)
{
	pOutputVals = new HBlockOutput(pnodepool,b,s);
}

SubArrayIteratorConst* CBlockImpl::GetOutputConst()
{
	if (!pBlockOutputConst) {
		pBlockOutputConst = new SubArrayIteratorConst(*pOutputVals);
	}
	return pBlockOutputConst;
}
	
SubArrayIterator* CBlockImpl::GetOutput()
{
	if (!pBlockOutput) {
		pBlockOutput = new SubArrayIterator(*pOutputVals);
	}
	return pBlockOutput;
}

} //end namespace CORINET


