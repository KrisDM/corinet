/*********************************************************************************************
 * Name      :  InitialisationImpl.cpp
 *
 * Purpose   :  Function objects implementing weight initialisations..
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

#include "InitialisationImpl.h"

namespace CORINET {

FInitialisationImpl::~FInitialisationImpl()
{

}

void FInitialisationImpl::Initialise()
{

}

void FInitialisationImpl::Reset()
{

}

void FInitialisationImpl::SetWPointer(const std::valarray<double>* pvals)
{
	pValues = pvals;
}

void FInitialisationImpl::SetRandGen(RandDouble* prg)
{
	pRandGen = prg;
}



} //end namespace CORINET
