/*********************************************************************************************
 * Name      :  NoiseFunctionImpl.cpp
 *
 * Purpose   :  Function objects implementing different noise effects in model and task.
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

#include "NoiseFunctionImpl.h"

namespace CORINET {

FNoiseFunctionImpl::~FNoiseFunctionImpl()
{
	
}

void FNoiseFunctionImpl::Initialise()
{

}

void FNoiseFunctionImpl::Reset()
{

}

void FNoiseFunctionImpl::SetRandGen(RandDouble* prg)
{
	pRG = prg;
}

} //end namespace CORINET

