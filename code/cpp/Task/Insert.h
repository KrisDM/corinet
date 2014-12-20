/*********************************************************************************************
 * Name      :  Insert.h
 *
 * Purpose   :  Abstract interface for insert elements, parts of compositeTasks.
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

#ifndef CORINET_INSERT
#define CORINET_INSERT

#include <Util/ParamInterface.h>
#include <limits>

namespace CORINET {
	class MatrixIterator;

class FInsert : public CParamInterface {
public:
	virtual ~FInsert() {}

	virtual void Initialise() =0;
	virtual void operator()(bool,MatrixIterator*) =0;
	virtual void Finalise() =0;
};

} //end namespace CORINET

#endif //CORINET_INSERT
