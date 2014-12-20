/*********************************************************************************************
 * Name      :  ConcreteOperations.cpp
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

#include "ConcreteOperations.h"

namespace CORINET {

FAssign::FAssign()
{
	mCurrent = 0;
	pVals = 0;
}

FAssign::~FAssign()
{

}

double FAssign::operator()(double val) 
{
	return (*pVals)[mCurrent];
}

//////////////////////////////////////////////////////////////////////////////////////////////////

FAdd::FAdd()
{
	mCurrent = 0;
	pVals = 0;
}

FAdd::~FAdd()
{

}

double FAdd::operator()(double val) 
{	
	return val + (*pVals)[mCurrent];
}

//////////////////////////////////////////////////////////////////////////////////////////////////

FSubtract::FSubtract()
{
	mCurrent = 0;
	pVals = 0;
}

FSubtract::~FSubtract()
{

}

double FSubtract::operator()(double val) 
{
	return val - (*pVals)[mCurrent];
}

///////////////////////////////////////////////////////////////////////////////////////////////////

FMultiply::FMultiply()
{
	mCurrent = 0;
	pVals = 0;
}

FMultiply::~FMultiply()
{

}

double FMultiply::operator()(double val) 
{
	return val * (*pVals)[mCurrent];
}

///////////////////////////////////////////////////////////////////////////////////////////////////

FDivide::FDivide()
{
	mCurrent = 0;
	pVals = 0;
}

FDivide::~FDivide()
{

}

double FDivide::operator()(double val) 
{
	return val / (*pVals)[mCurrent];
}

} //end namespace CORINET

