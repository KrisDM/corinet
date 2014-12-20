/*********************************************************************************************
 * Name      :  ConcreteBlocks.h
 *
 * Purpose   :  Concrete types of blocks.
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


#ifndef CORINET_BLOCKCONCR
#define CORINET_BLOCKCONCR

#include <Model/Impl/BlockImpl.h>

namespace CORINET {

class CBlockNormal : public CBlockImpl {
	const size_t mNodes;
public:
	CBlockNormal(size_t*,double*);
	virtual ~CBlockNormal();
	bool Integrate(); //returns a bool to indicate whether integration has completed or not
	bool Learn(); //always returns false
};

class CBlockConstr : public CBlockImpl {
	size_t mStartNodes;
	size_t mCurrentNodes;
public:
	CBlockConstr(size_t*,double*);
	virtual ~CBlockConstr();
	bool Integrate(); //returns a bool to indicate whether integration has completed or not
	bool Learn(); //returns true when last available node has learned
	void Initialise();
	void SetParam(size_t,double);
	double GetParam(size_t);
};

} //end namespace CORINET

#endif //CORINET_BLOCKCONCR

