/*********************************************************************************************
 * Name      :  Block.h
 *
 * Purpose   :  Abstract interface for blocks of neurons. 
 *				A block is the basic unit of simulation within a network.
 *				All neurons in a block are of the same type, having the same integration sites 
 *				and outputfunction. Furthermore, if the output of block A is used as input to
 *				block B, then all neurons of block A serve as input to all neurons of block B.
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

#ifndef CORINET_BLOCK
#define CORINET_BLOCK

#include <Util/ParamInterface.h>

namespace CORINET {
	class SubArrayIterator;
	class SubArrayIteratorConst;

class CBlock : public CParamInterface {
public:
	virtual ~CBlock() {}

	//interface for networks
	virtual void Initialise() =0;
	virtual bool Integrate() =0;
	virtual void CalculateOutput() =0;
	virtual bool Learn() =0;	
	virtual void Reset() =0;

	//access functions for event handlers etc.
	virtual SubArrayIteratorConst* GetOutputConst()=0;
	virtual SubArrayIterator* GetOutput() =0;
};

} //end namespace CORINET

#endif //CORINET_BLOCK


