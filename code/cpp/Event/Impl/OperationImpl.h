/*********************************************************************************************
 * Name      :  OperationImpl.h
 *
 * Purpose   :  Function objects implementing the operations in "modifyXXX" event handlers.
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

#ifndef CORINET_OPERATIONIMPL
#define CORINET_OPERATIONIMPL

#include <Event/Operation.h>
#include <valarray>

namespace CORINET {

class FOperationImpl : public FOperation {
protected:
	size_t mCurrent;
	const std::valarray<double>* pVals;
public:
	virtual ~FOperationImpl();
	void Next();
	void SetVals(const std::valarray<double>*);
};

} //end namespace CORINET

#endif //CORINET_OPERATIONIMPL

