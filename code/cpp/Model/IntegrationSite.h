/*********************************************************************************************
 * Name      :  IntegrationSite.h
 *
 * Purpose   :  Abstract interface for integration sites.
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

#ifndef CORINET_INTEGRATIONSITE
#define CORINET_INTEGRATIONSITE

#include <Util/ParamInterface.h>

namespace CORINET {
	class HBlockOutput;
	class SubArrayIterator;
	class SubArrayIteratorConst;
	class IndirectIterator;
	class IndirectIteratorConst;
	class MatrixIterator;
	class MatrixIteratorConst;
	class SynapseWrapper;
	
class CIntegrationSite : public CParamInterface {
public:
	virtual ~CIntegrationSite() {}

	//interface for blocks
	virtual void Initialise() =0;
	virtual bool Integrate(size_t,HBlockOutput&) =0;
	virtual bool Learn(size_t,HBlockOutput&) =0;
	virtual void Reset() =0;

	//access functions for event handlers etc.
	virtual IndirectIteratorConst* GetInputConst() =0;
	virtual IndirectIterator* GetInput() =0;
	virtual SubArrayIteratorConst* GetOutputConst() =0;
	virtual SubArrayIterator* GetOutput() =0;
	virtual MatrixIteratorConst* GetWeightsConst() =0;
	virtual MatrixIterator* GetWeights() =0;
	virtual SynapseWrapper* GetSynapses() =0;
};

} //end namespace CORINET

#endif //CORINET_INTEGRATIONSITE

