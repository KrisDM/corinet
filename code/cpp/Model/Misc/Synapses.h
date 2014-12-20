/*********************************************************************************************
 * Name      :  Synapses.h
 *
 * Purpose   :  Concrete wappers around per-synapse activation values.
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

#ifndef CORINET_SYNAPSES
#define CORINET_SYNAPSES

#include <Model/SynapseWrapper.h>
#include <Model/Misc/Nodes.h>

namespace CORINET {

class SynapsesDefault : public SynapseWrapper  {
	const size_t mInputs;
	SubArrayIteratorConst* pValuesIterator;
public:
	SynapsesDefault(size_t i,SubArrayIteratorConst* pv) : mInputs(i),pValuesIterator(pv) {} 
	virtual ~SynapsesDefault() {}
	double operator()(size_t input,size_t node) const {
		return (*pValuesIterator)[node];
	}
	size_t inputs() const {return mInputs;}
	size_t nodes() const {return pValuesIterator->size();}
};

class SynapseWrapperCompInt1 : public SynapseWrapper {
	const size_t mNodes;
	const std::valarray<double>* pMaxVals1;
	const std::valarray<double>* pMaxVals2;
	const std::valarray<size_t>* pMaxIndex;
public:
	SynapseWrapperCompInt1(size_t nodes,const std::valarray<double>* const pmv1,
		const std::valarray<double>* const pmv2,const std::valarray<size_t>* const pmi) : mNodes(nodes)
	{
		pMaxVals1 = pmv1;
		pMaxVals2 = pmv2;
		pMaxIndex = pmi;
	}
	virtual ~SynapseWrapperCompInt1() {}
	double operator()(size_t input,size_t node) const
	{
		if ((*pMaxIndex)[input] == node)
			return (*pMaxVals2)[input];
		else
			return (*pMaxVals1)[input];
	}
	size_t inputs() const {return pMaxVals1->size();}
	size_t nodes() const {return mNodes;}
};

class SynapseWrapperMaxInt1 : public SynapseWrapper {
	HIntegrationInput* pInputVals;
	HWeights* pWeights;
public:
	SynapseWrapperMaxInt1(HIntegrationInput* pin,HWeights* pw) 
	{
		pInputVals = pin;
		pWeights = pw;
	}
	virtual ~SynapseWrapperMaxInt1() {}
	double operator()(size_t input,size_t node) const {
		if (pWeights->MaxWForNodeSpecial(node) && pWeights->MaxWForInputSpecial(input,pWeights->NumNodes())) {
			return ((*pInputVals)[input])*(*pWeights)(input,node)*(*pWeights)(input,node)
			*pWeights->MaxWForNodeSpecial(node)*pWeights->MaxWForInputSpecial(input,pWeights->NumNodes());
		}
		else
			return 0.0;
	}
	size_t inputs() const {return pWeights->NumInputs();}
	size_t nodes() const {return pWeights->NumNodes();}
};

} //namespace CORINET

#endif //CORINET_SYNAPSES

