/*********************************************************************************************
 * Name      :  ConcreteBlocks.cpp
 *
 * Purpose   :  Concrete types of blocks of neurons.
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

#include "ConcreteBlocks.h"
#include <Model/IntegrationSite.h>
#include <Model/OutputFunction.h>
#include <Model/Misc/Nodes.h>

namespace CORINET {

CBlockNormal::CBlockNormal(size_t* s,double*) : mNodes(s[0])
{
	
}
	
CBlockNormal::~CBlockNormal() 
{

}
	
bool CBlockNormal::Integrate() //returns a bool to indicate whether integration has completed or not
{
	bool conv = true;
	const LIntegrationSitePool::iterator ite(mIntegrationSites.end());
	for(LIntegrationSitePool::iterator it=mIntegrationSites.begin();it!=ite;++it) {
		conv &= (*it)->Integrate(mNodes,*pOutputVals);
	}
	return conv;
}
	
bool CBlockNormal::Learn() 
{
	bool incr = false;
	const LIntegrationSitePool::iterator ite(mIntegrationSites.end());
	for(LIntegrationSitePool::iterator it=mIntegrationSites.begin();it!=ite;++it)
		incr |= (*it)->Learn(mNodes,*pOutputVals);
	return incr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

CBlockConstr::CBlockConstr(size_t*,double* params) : mStartNodes(static_cast<size_t>(params[0]))
{
	
}
	
CBlockConstr::~CBlockConstr() 
{

}
	
bool CBlockConstr::Integrate() //returns a bool to indicate whether integration has completed or not
{
	bool conv = true;
	const LIntegrationSitePool::iterator ite(mIntegrationSites.end());
	for(LIntegrationSitePool::iterator it=mIntegrationSites.begin();it!=ite;++it) {
		conv &= (*it)->Integrate(mCurrentNodes,*pOutputVals);
	}
	return conv;
}
	
bool CBlockConstr::Learn() 
{
	bool incr = false;
	const LIntegrationSitePool::iterator ite(mIntegrationSites.end());
	for(LIntegrationSitePool::iterator it=mIntegrationSites.begin();it!=ite;++it)
		incr |= (*it)->Learn(mCurrentNodes,*pOutputVals);
	if (incr && mCurrentNodes<pOutputVals->size()-1)
		++mCurrentNodes;
	return incr;
}

void CBlockConstr::Initialise()
{
	mCurrentNodes = mStartNodes;
	CBlockImpl::Initialise();
}

void CBlockConstr::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mCurrentNodes = static_cast<size_t>(val);
		break;
	}
}

double CBlockConstr::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = static_cast<double>(mCurrentNodes);
		break;
	}
	return v;
}

} //end namespace CORINET


