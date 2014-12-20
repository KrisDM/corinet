/*********************************************************************************************
 * Name      :  IntegrationSiteImpl.h
 *
 * Purpose   :  Implementation class for integration sites. This is still not a concrete type of
 *				integration site, but a general base class that assembles data and operations
 *				common to all types of integration sites. New types of integration sites are usually
 *				derived from this class.
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

#ifndef CORINET_INTEGRATIONSITEIMPL
#define CORINET_INTEGRATIONSITEIMPL

#include <Model/IntegrationSite.h>
#include <Model/Misc/Weights.h>
#include <valarray>

namespace CORINET {
	class HIntegrationInput;
	class FInitialisation;
	class FNormalisation;

class CIntegrationSiteImpl : public CIntegrationSite {//class containing data common to all types of integration sites
private:
	IndirectIteratorConst* pSiteInputConst;
	IndirectIterator* pSiteInput;
	SubArrayIteratorConst* pSiteOutputConst;
	SubArrayIterator* pSiteOutput;
	MatrixIteratorConst* pWeightsIteratorConst;
	MatrixIterator* pWeightsIterator;
protected:
	HIntegrationInput* pInputVals;//the input to this integration site
	std::valarray<double> mIntegrationVals; //the output of this integration site
	HWeights mWeights;
	FInitialisation* pInit;
	FNormalisation* pNorm;
	SynapseWrapper* pSynapseWrapper;
public:
	CIntegrationSiteImpl(size_t,size_t);
	virtual ~CIntegrationSiteImpl();
	void Initialise();
	void Reset();
	bool Integrate(size_t,HBlockOutput&);
	bool Learn(size_t,HBlockOutput&);

	void SetInputIndices(std::valarray<double>*,std::valarray<size_t>*);
	void SetInitialisation(FInitialisation*);
	void SetNormalisation(FNormalisation*);

	//access functions for event handlers etc.
	IndirectIteratorConst* GetInputConst();
	IndirectIterator* GetInput();
	SubArrayIteratorConst* GetOutputConst();
	SubArrayIterator* GetOutput();
	MatrixIteratorConst* GetWeightsConst();
	MatrixIterator* GetWeights();
	SynapseWrapper* GetSynapses();
};

} //end namespace CORINET

#endif //CORINET_INTEGRATIONSITEIMPL

