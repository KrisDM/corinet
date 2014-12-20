/*********************************************************************************************
 * Name      :  OutputFunctionImpl.cpp
 *
 * Purpose   :  Definition of general base class for concrete types of outputfunction. 
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


#include "OutputFunctionImpl.h"
#include <Common/Attenuation.h>
#include <Common/NoiseFunction.h>

namespace CORINET {

FOutputFunctionImpl::~FOutputFunctionImpl()
{
	
}

void FOutputFunctionImpl::Initialise()
{
	if (pAttenuation) pAttenuation->Initialise();
	if (pNoise) pNoise->Initialise();
}

void FOutputFunctionImpl::Reset()
{
	if (pAttenuation) pAttenuation->Reset();
	if (pNoise) pNoise->Reset();
}

void FOutputFunctionImpl::SetAttenuation(FAttenuation* pat)
{
	pAttenuation = pat;	
}
	
void FOutputFunctionImpl::SetNoise(FNoiseFunction* pn)
{
	pNoise = pn;
}

} //end namespace CORINET
