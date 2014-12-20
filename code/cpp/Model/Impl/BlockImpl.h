/*********************************************************************************************
 * Name      :  BlockImpl.h
 *
 * Purpose   :  Implementation class for blocks, the basic unit of function in the network.
 *				This class assembles generic functionality for blocks.
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

#ifndef CORINET_BLOCKIMPL
#define CORINET_BLOCKIMPL

#include <Model/Block.h>
#include <valarray>
#include <vector>

namespace CORINET {
	class SubArrayIteratorConst;
	class HBlockOutput;
	class FOutputFunction;
	class CIntegrationSite;

class CBlockImpl : public CBlock {
private:
	SubArrayIteratorConst* pBlockOutputConst;
	SubArrayIterator* pBlockOutput;
protected:
	typedef std::vector<CIntegrationSite*> LIntegrationSitePool;
	typedef std::vector<SubArrayIteratorConst*> LIntValsPool;
	HBlockOutput* pOutputVals; //node values of block, a subset of all input and output nodes in the network
	LIntegrationSitePool mIntegrationSites;
	LIntValsPool mIntValPointers;
	FOutputFunction* pOutputFun;
public:
	CBlockImpl();
	virtual ~CBlockImpl();
	bool Integrate();
	bool Learn();
	void CalculateOutput();
	void Initialise();
	void Reset();

	//initialisation functions
	void AddIntegrationSite(CIntegrationSite* const);
	void SetOutputFunction(FOutputFunction* const);
	void SetOutputIndices(std::valarray<double>*,size_t,size_t);

	//access functions
	SubArrayIteratorConst* GetOutputConst();
	SubArrayIterator* GetOutput();
};

} //end namespace CORINET

#endif //CORINET_BLOCKIMPL

