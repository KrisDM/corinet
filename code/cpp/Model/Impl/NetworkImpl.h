/*********************************************************************************************
 * Name      :  NetworkImpl.h
 *
 * Purpose   :  Implementation class for networks. This is not a concrete type of network, but
 *				a class assembling common structure of concrete networks.
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


#ifndef CORINET_NETWORKIMPL
#define CORINET_NETWORKIMPL

#include <Model/Network.h>
#include <valarray>
#include <vector>

namespace  CORINET {
	class CBlock;

class CNetworkImpl : public CNetwork {
private:
	SubArrayIteratorConst* pNetStateConst;
	SubArrayIteratorConst* pNetInputConst;
	MultipleSubArrayIteratorConst* pNetOutputConst;
	MultipleSubArrayIteratorConst* pNetIOConst;
	SubArrayIterator* pNetState;
protected:
	typedef std::vector<CBlock*> LBlockPool;
	const size_t mNumInputs;
	std::valarray<double> mNodePool; //the collection of all external input and node activation values
	LBlockPool mBlockPool;
	std::vector<bool> mOutputBlocks;
public:
	CNetworkImpl(size_t,size_t);
	virtual ~CNetworkImpl();

	void Initialise();
	void Finalise();
	NextStep SetInput(size_t,SubArrayIteratorConst&,double);
	NextStep Integrate();
	void CalculateOutput();
	NextStep Learn(bool);
	NextStep Reset(double =0.0);

	//initialising functions
	void AddBlock(CBlock* const,bool);

	std::valarray<double>* GetNodePool();

	//access functions for event handlers etc.
	SubArrayIteratorConst* GetStateConst();
	SubArrayIteratorConst* GetInputConst();
	MultipleSubArrayIteratorConst* GetOutputConst();
	MultipleSubArrayIteratorConst* GetIOConst();
	SubArrayIterator* GetState();
};

} //end namespace CORINET

#endif //CORINET_NETWORK

