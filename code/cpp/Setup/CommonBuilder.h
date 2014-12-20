/*********************************************************************************************
 * Name      :  CommonBuilder.h
 *
 * Purpose   :  Create random generators, attenuation and noise functions and cleanup after use. 
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

#ifndef CORINET_COMMONBUILDER
#define CORINET_COMMONBUILDER

#include <Platform/Platform.h>
#include <vector>

namespace CORINET {
	class RandGen;
	class FAttenuation;
	class FNoiseFunction;
	struct SRandGenMaker;
	struct SAttenuationMaker;
	struct SNoiseFunctionMaker;
	struct SMaker;

class CCommonBuilder {
public:
	virtual ~CCommonBuilder() {}

	//create functions
	virtual RandGen* Create(SRandGenMaker*) =0;
	virtual FAttenuation* Create(SAttenuationMaker*,size_t) =0;
	virtual FNoiseFunction* Create(SNoiseFunctionMaker*,size_t) =0;

	//access functions 
	virtual RandGen* Get(SRandGenMaker*) =0;
	virtual std::vector<void*>& GetVoid(SMaker*) =0;
	
	//cleanup function
	virtual void ReleaseAll() =0;
};

} //end namespace CORINET

#endif //CORINET_COMMONBUILDER

