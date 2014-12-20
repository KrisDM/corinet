/*********************************************************************************************
 * Name      :  ConcreteOutputFun.h
 *
 * Purpose   :  Concrete types of outputfunctions, combining integration results from 
 *				individual integration sites into an overall node activity value.
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

#ifndef CORINET_OUTPUTFUNCONCR
#define CORINET_OUTPUTFUNCONCR

#include <Model/Impl/OutputFunctionImpl.h>

namespace CORINET {

///////////////////////////////////////////////////////////////////
//Output functions for neurons with unlimited integration sites
///////////////////////////////////////////////////////////////////

class FOutputFunctionAddSites : public FOutputFunctionImpl {
public:
	FOutputFunctionAddSites(size_t*,double*);
	virtual ~FOutputFunctionAddSites();
	void operator()(const std::vector<SubArrayIteratorConst*>&,HBlockOutput&);
};

class FOutputFunctionMaxSites : public FOutputFunctionImpl {
public:
	FOutputFunctionMaxSites(size_t*,double*);
	virtual ~FOutputFunctionMaxSites();
	void operator()(const std::vector<SubArrayIteratorConst*>&,HBlockOutput&);
};
///////////////////////////////////////////////////////////////////
//Output functions for nodes with two integration sites
///////////////////////////////////////////////////////////////////

class FOutputFunctionModulate1 : public FOutputFunctionImpl {
	double mA;
public:
	FOutputFunctionModulate1(size_t*,double*);
	virtual ~FOutputFunctionModulate1();
	void operator()(const std::vector<SubArrayIteratorConst*>&,HBlockOutput&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

} //end namespace CORINET

#endif //CORINET_OUTPUTFUNCONCR

