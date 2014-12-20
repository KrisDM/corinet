/*********************************************************************************************
 * Name      :  CommonBuilder.cpp
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

#include "CommonBuilderImpl.h"
#include <Util/Factory.h>
#include <Common/RandGen.h>
#include <Common/Impl/AttenuationImpl.h>
#include <Common/Impl/NoiseFunctionImpl.h>
#include <Setup/Makers.h>
#include <limits>

namespace CORINET {

CCommonBuilderImpl::CCommonBuilderImpl() : mRandGens(),mAttenuations(),mNoiseFunctions(),
										   mTempAttenuation(),mTempNoiseFunction(),mTempObject()
{

}

CCommonBuilderImpl::~CCommonBuilderImpl()
{
	ReleaseAll();
}

RandGen* CCommonBuilderImpl::Create(SRandGenMaker* prm)
{
	if (mRandGens.find(prm) == mRandGens.end()) {
		RandGen* prg = CFactoryManager<RandDouble>::CreateInstance(prm->type,0,prm->randParams);
		if (!prg) {
			prg = CFactoryManager<RandInt>::CreateInstance(prm->type,0,prm->randParams);
		}

		if (!prg) //unknown type of random generator
			throw ECreation("random generator",prm->type);
		else
			mRandGens.insert(LRandGens::value_type(prm,prg));

		//intialise
		if (prm->seed < std::numeric_limits<size_t>::max())
			prg->Seed(prm->seed);
		else
			prg->Seed();
	}
	return mRandGens[prm];
}
	
FAttenuation* CCommonBuilderImpl::Create(SAttenuationMaker* pam,size_t s)
{
	FAttenuation* pat;
	//if pam->state, then a new function object needs to be created for every call of the Create function
	if (pam->state || (mAttenuations.find(pam) == mAttenuations.end())) {
		pat = CFactoryManager<FAttenuation>::CreateInstance(pam->type,&s,pam->attenuationParams);

		if (!pat)
			throw ECreation("attenuation function",pam->type);
		else
			mAttenuations.insert(LAttenuations::value_type(pam,pat));
	}
	else {
		pat = mAttenuations.find(pam)->second;
	}
	return pat;
}
	
FNoiseFunction* CCommonBuilderImpl::Create(SNoiseFunctionMaker* pnm,size_t s)
{
	FNoiseFunction* pnf;
	//if pnm->state, then a new function object needs to be created for every call of the Create function
	if (pnm->state || (mNoiseFunctions.find(pnm) == mNoiseFunctions.end())) {
		pnf = CFactoryManager<FNoiseFunction>::CreateInstance(pnm->type,&s,pnm->noiseParams);

		if (!pnf)
			throw ECreation("noise function",pnm->type);
		else
			mNoiseFunctions.insert(LNoiseFunctions::value_type(pnm,pnf));

		if (pnm->randMaker)
			static_cast<FNoiseFunctionImpl*>(pnf)->SetRandGen(static_cast<RandDouble*>(Create(pnm->randMaker)));
		else
			static_cast<FNoiseFunctionImpl*>(pnf)->SetRandGen(0);
	}
	else {
		pnf = mNoiseFunctions.find(pnm)->second;
	}
	return pnf;
}

RandGen* CCommonBuilderImpl::Get(SRandGenMaker* rm)
{
	if (mRandGens.find(rm) != mRandGens.end())
		return mRandGens[rm];
	else
		return 0;
}

std::vector<void*>& CCommonBuilderImpl::GetVoid(SMaker* maker)
{
	mTempObject.clear();
	if (maker->makerType == "randGen") {
		if (mRandGens.find(static_cast<SRandGenMaker*>(maker)) != mRandGens.end()) {
			mTempObject.push_back(mRandGens[static_cast<SRandGenMaker*>(maker)]);
		}
	}
	else if (maker->makerType == "attenuation") {
		if (mAttenuations.find(static_cast<SAttenuationMaker*>(maker)) != mAttenuations.end()) {
			SAttenuationMaker* am = static_cast<SAttenuationMaker*>(maker);
			for(LAttenuations::iterator it=mAttenuations.lower_bound(am),ite=mAttenuations.upper_bound(am);it != ite;++it) {
				mTempObject.push_back(it->second);
			}
		}
	}
	else if (mNoiseFunctions.find(static_cast<SNoiseFunctionMaker*>(maker)) != mNoiseFunctions.end()) {
		SNoiseFunctionMaker* nm = reinterpret_cast<SNoiseFunctionMaker*>(maker);
		for(LNoiseFunctions::iterator it=mNoiseFunctions.lower_bound(nm),ite=mNoiseFunctions.upper_bound(nm);it != ite;++it) {
			mTempObject.push_back(it->second);
		}
	}
	return mTempObject;
}
	
void CCommonBuilderImpl::ReleaseAll()
{
	for(LRandGens::iterator it1=mRandGens.begin(),ite1=mRandGens.end();it1 != ite1;++it1) {
		delete it1->second;
		it1->second = 0;
	}
	mRandGens.clear();
	for(LAttenuations::iterator it2=mAttenuations.begin(),ite2=mAttenuations.end();it2 != ite2;++it2) {
		delete it2->second;
		it2->second = 0;
	}
	mAttenuations.clear();
	for(LNoiseFunctions::iterator it3=mNoiseFunctions.begin(),ite3=mNoiseFunctions.end();it3 != ite3;++it3) {
		delete it3->second;
		it3->second = 0;
	}
	mNoiseFunctions.clear();
}


} //end namespace CORINET



