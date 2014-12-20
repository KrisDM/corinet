/*********************************************************************************************
 * Name      :  CommonBuilderImpl.h
 *
 * Purpose   :  Create random generators, attenuation and noise functions and cleanup after use. 
 *				Implementation class.
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

#ifndef CORINET_COMMONBUILDERIMPL
#define CORINET_COMMONBUILDERIMPL

#include <Setup/CommonBuilder.h>
#include <map>

namespace CORINET {

class CCommonBuilderImpl : public CCommonBuilder {
	typedef std::map<SRandGenMaker*,RandGen*> LRandGens;
	typedef std::multimap<SAttenuationMaker*,FAttenuation*> LAttenuations;
	typedef std::multimap<SNoiseFunctionMaker*,FNoiseFunction*> LNoiseFunctions;
	LRandGens mRandGens;
	LAttenuations mAttenuations;
	LNoiseFunctions mNoiseFunctions;
	std::vector<FAttenuation*> mTempAttenuation;
	std::vector<FNoiseFunction*> mTempNoiseFunction;
	std::vector<void*> mTempObject;
public:
	CCommonBuilderImpl();
	virtual ~CCommonBuilderImpl();

	//create functions
	RandGen* Create(SRandGenMaker*);
	FAttenuation* Create(SAttenuationMaker*,size_t);
	FNoiseFunction* Create(SNoiseFunctionMaker*,size_t);

	//access functions
	RandGen* Get(SRandGenMaker*);
	std::vector<void*>& GetVoid(SMaker*);
	
	//cleanup function
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_COMMONBUILDERIMPL

