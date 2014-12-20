/*********************************************************************************************
 * Name      :  Network.h
 *
 * Purpose   :  Abstract interface for networks.
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

#ifndef CORINET_NETWORK
#define CORINET_NETWORK

#include <Util/ParamInterface.h>

namespace CORINET {
	class SubArrayIterator;
	class SubArrayIteratorConst;
	class MultipleSubArrayIteratorConst;

enum NextStep {
	NEXT_ENGINE = 0,
	NEXT_INTEGRATE = 1,
	NEXT_LEARN = 2
};

class CNetwork : public CParamInterface {
public:
	virtual ~CNetwork() {}

	//interface for execution engine
	virtual void Initialise() =0;
	virtual void Finalise() =0;
	virtual NextStep Reset(double) =0;
	virtual NextStep SetInput(size_t,SubArrayIteratorConst&,double) =0;
	virtual NextStep Integrate() =0;
	virtual void CalculateOutput() =0;
	virtual NextStep Learn(bool) =0;
	
	//access functions for event handlers etc.
	virtual SubArrayIteratorConst* GetStateConst() =0;
	virtual SubArrayIteratorConst* GetInputConst() =0;
	virtual MultipleSubArrayIteratorConst* GetOutputConst() =0;
	virtual MultipleSubArrayIteratorConst* GetIOConst() =0;
	virtual SubArrayIterator* GetState() =0;
};

} //end namespace CORINET

#endif //CORINET_NETWORK
