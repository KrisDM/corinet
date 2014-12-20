/*********************************************************************************************
 * Name      :  OutputFunction.h
 *
 * Purpose   :  Abstract interface for function objects implementing outputfunctions. 
 *				An outputfunction combines the integration results from separate integration sites 
 *				into an overall node activity value.
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

#ifndef CORINET_OUTPUTFUNCTION
#define CORINET_OUTPUTFUNCTION

#include <Util/ParamInterface.h>
#include <vector>

namespace CORINET {
	class SubArrayIteratorConst;
	class HBlockOutput;

class FOutputFunction : public CParamInterface {
public:
	virtual ~FOutputFunction() {}
	virtual void Initialise() =0;
	virtual void operator()(const std::vector<SubArrayIteratorConst*>&,HBlockOutput&) =0;
	virtual void Reset() =0;
};

} //end namespace CORINET

#endif //CORINET_OUTPUTFUNCTION


