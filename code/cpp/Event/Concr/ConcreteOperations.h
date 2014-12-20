/*********************************************************************************************
 * Name      :  ConcreteOperations.h
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

#ifndef CORINET_OPERATIONCONCR
#define CORINET_OPERATIONCONCR

#include <Event/Impl/OperationImpl.h>

namespace CORINET {


class FAssign : public FOperationImpl {
public:
	FAssign();
	virtual ~FAssign();
	double operator()(double);
};

class FAdd : public FOperationImpl {
public:
	FAdd();
	virtual ~FAdd();
	double operator()(double);
};

class FSubtract : public FOperationImpl {
public:
	FSubtract();
	virtual ~FSubtract();
	double operator()(double);
};

class FMultiply : public FOperationImpl {
public:
	FMultiply();
	virtual ~FMultiply();
	double operator()(double);
};

class FDivide : public FOperationImpl {
public:
	FDivide();
	virtual ~FDivide();
	double operator()(double);
};

} //end namespace CORINET

#endif //CORINET_OPERATIONCONCR

