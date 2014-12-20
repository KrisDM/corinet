/*********************************************************************************************
 * Name      :  ConcreteConditions.cpp
 *
 * Purpose   :  Function objects implementing the operators for conditions in event handlers.
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

#include "ConcreteConditions.h"

namespace CORINET {

bool FCMultiple::operator()(double val) const 
{
	for(size_t i=0,s=pCondVals->size();i<s;++i) {
		if ((val+1)/(*pCondVals)[i] == static_cast<int>((val+1)/(*pCondVals)[i])) 
			return true;
	}
	return false;
}

bool FCEquals::operator()(double val) const 
{
	for(size_t i=0,s=pCondVals->size();i<s;++i) {
		if (val == (*pCondVals)[i]) 
			return true;
	}
	return false;
}

bool FCGT::operator()(double val) const 
{
	for(size_t i=0,s=pCondVals->size();i<s;++i) {
		if (val > (*pCondVals)[i]) 
		return true;
	}
	return false;
}

bool FCGTE::operator()(double val) const 
{
	for(size_t i=0,s=pCondVals->size();i<s;++i) {
		if (val >= (*pCondVals)[i]) 
			return true;
	}
	return false;
}

bool FCLT::operator()(double val) const 
{
	for(size_t i=0,s=pCondVals->size();i<s;++i) {
		if (val < (*pCondVals)[i]) 
			return true;
	}
	return false;
}

bool FCLTE::operator()(double val) const 
{
	for(size_t i=0,s=pCondVals->size();i<s;++i) {
		if (val <= (*pCondVals)[i]) 
			return true;
	}
	return false;
}

} //end namespace CORINET



