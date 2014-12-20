/*********************************************************************************************
 * Name      :  DataSource.h
 *
 * Purpose   :  Abstract interface for external, non-XML data formats.
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

#ifndef CORINET_DATASOURCE
#define CORINET_DATASOURCE

#include <Util/ParamInterface.h>
#include <valarray>

namespace CORINET {

class CDataSource : public CParamInterface {
public:
	virtual ~CDataSource() {}

	virtual void Initialise() =0;
	virtual const std::valarray<double>* Get(size_t) =0;
	virtual void Finalise() =0;
};

} //end namespace CORINET

#endif //CORINET_DATASOURCE
