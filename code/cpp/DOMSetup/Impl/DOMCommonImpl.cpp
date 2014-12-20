/*********************************************************************************************
 * Name      :  DOMCommonImpl.cpp
 *
 * Purpose   :  Implementation class handling randGens, attenuation and noiseFunctions.
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

#include "DOMCommonImpl.h"
#include <DOMSetup/Misc/DOMHelperFunctions.h>
#include <Setup/Makers.h>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

CDOMCommonImpl::CDOMCommonImpl() : mRandMakers(),mAttenuationMakers(),mNoiseMakers()
{

}
	
CDOMCommonImpl::~CDOMCommonImpl()
{
	ReleaseAll();
}

void CDOMCommonImpl::Handle(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create)
{
	//handle the <randGen> elements
	const DOMNodeList* pDOMrandGenList = GetElementList(setupDoc,XMLStrDefs::randGen);
	for(XMLSize_t i1=0,is1=pDOMrandGenList->getLength();i1<is1;++i1) {
		//get the current element
		const DOMElement* pDOMrandGen = GetElement(pDOMrandGenList,i1);
		//check its type
		const DOMElement* pDOMvalRandGen = GetType(pDOMrandGen,valDoc,eHandler);

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalRandGen,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMrandGen,pDOMvalRandGen,eHandler,pDOMrandGen);
		
		//now that all checks have completed, create the randMaker if needed
		if (create) {
			SRandGenMaker* randMaker = new SRandGenMaker(XMLStringUtil::XML2Str(pDOMrandGen->getAttribute(XMLStrDefs::type)));
			mRandMakers.insert(LRandMakers::value_type(pDOMrandGen,randMaker));
			for(size_t i=0,is=vals.size();i<is;++i) {
				randMaker->randParams[i] = vals[i];
			}
			if (pDOMrandGen->hasAttribute(XMLStrDefs::seed)) {
				randMaker->seed = XMLStringUtil::XML2Int(pDOMrandGen->getAttribute(XMLStrDefs::seed));
			}
		}
	}

	//handle the <attenuation> elements
	const DOMNodeList* pDOMattenuationList = GetElementList(setupDoc,XMLStrDefs::attenuation);
	for(XMLSize_t i2=0,is2=pDOMattenuationList->getLength();i2<is2;++i2) {
		//get the current element
		const DOMElement* pDOMattenuation = GetElement(pDOMattenuationList,i2);
		//check its type
		const DOMElement* pDOMvalAttenuation = GetType(pDOMattenuation,valDoc,eHandler);

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalAttenuation,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMattenuation,pDOMvalAttenuation,eHandler,pDOMattenuation);
		
		//now that all checks have completed, create the attenuationMaker if needed
		if (create) {
			SAttenuationMaker* attenuationMaker = new SAttenuationMaker(XMLStringUtil::XML2Str(pDOMattenuation->getAttribute(XMLStrDefs::type)));
			mAttenuationMakers.insert(LAttenuationMakers::value_type(pDOMattenuation,attenuationMaker));
			for(size_t i=0,is=vals.size();i<is;++i) {
				attenuationMaker->attenuationParams[i] = vals[i];
			}
			attenuationMaker->state = GetBool(pDOMvalAttenuation,XMLStrDefs::state);
		}
	}

	//handle the <noiseFunction> elements
	const DOMNodeList* pDOMnoiseList = GetElementList(setupDoc,XMLStrDefs::noiseFunction);
	for(XMLSize_t i3=0,is3=pDOMnoiseList->getLength();i3<is3;++i3) {
		//get the current element and the subelement containing the parameters
		const DOMElement* pDOMnoise = GetElement(pDOMnoiseList,i3);
		const DOMElement* pDOMnoiseParams = GetElement(pDOMnoise,XMLStrDefs::noiseParams,0);

		//check its type
		const DOMElement* pDOMvalNoise = GetType(pDOMnoise,valDoc,eHandler);

		//check the presence of <randGen> element
		CheckChildElement(pDOMnoise,pDOMvalNoise,eHandler,XMLStrDefs::randGen);

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalNoise,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMnoiseParams,pDOMvalNoise,eHandler,pDOMnoise);
		
		//now that all checks have completed, create the noiseMaker if needed
		if (create) {
			SNoiseFunctionMaker* noiseMaker = new SNoiseFunctionMaker(XMLStringUtil::XML2Str(pDOMnoise->getAttribute(XMLStrDefs::type)));
			mNoiseMakers.insert(LNoiseMakers::value_type(pDOMnoise,noiseMaker));
			for(size_t i=0,is=vals.size();i<is;++i) {
				noiseMaker->noiseParams[i] = vals[i];
			}
			noiseMaker->randMaker = mRandMakers[GetElement(pDOMnoise,XMLStrDefs::randGen,0)];
			noiseMaker->state = GetBool(pDOMvalNoise,XMLStrDefs::state);
		}
	}
}

SRandGenMaker* CDOMCommonImpl::GetRandMaker(const DOMElement* el)
{
	if (mRandMakers.find(el) != mRandMakers.end())
		return mRandMakers[el];
	else
		return 0;
}
	
SAttenuationMaker* CDOMCommonImpl::GetAttenuationMaker(const DOMElement* el)
{
	if (mAttenuationMakers.find(el) != mAttenuationMakers.end())
		return mAttenuationMakers[el];
	else
		return 0;
}
	
SNoiseFunctionMaker* CDOMCommonImpl::GetNoiseMaker(const DOMElement* el)
{
	if (mNoiseMakers.find(el) != mNoiseMakers.end())
		return mNoiseMakers[el];
	else
		return 0;
}

SMaker* CDOMCommonImpl::GetMaker(const DOMElement* el)
{
	if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::randGen)) {
		if (mRandMakers.find(el) != mRandMakers.end())
			return mRandMakers[el];
	}
	else if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::attenuation)) {
		if (mAttenuationMakers.find(el) != mAttenuationMakers.end())
			return mAttenuationMakers[el];
	}
	else if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::noiseFunction)) {
		if (mNoiseMakers.find(el) != mNoiseMakers.end())
			return mNoiseMakers[el];
	}
	return 0;
}

void CDOMCommonImpl::ReleaseAll()
{
	for(LRandMakers::iterator it1=mRandMakers.begin(),ite1=mRandMakers.end();it1 != ite1;++it1) {
		delete it1->second;
		it1->second = 0;
	}
	mRandMakers.clear();
	for(LAttenuationMakers::iterator it2=mAttenuationMakers.begin(),ite2=mAttenuationMakers.end();it2 != ite2;++it2) {
		delete it2->second;
		it2->second = 0;
	}
	mAttenuationMakers.clear();
	for(LNoiseMakers::iterator it3=mNoiseMakers.begin(),ite3=mNoiseMakers.end();it3 != ite3;++it3) {
		delete it3->second;
		it3->second = 0;
	}
	mNoiseMakers.clear();
}

} //end namespace CORINET





