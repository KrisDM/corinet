/*********************************************************************************************
 * Name      :  DOMDefaultsImpl.cpp
 *
 * Purpose   :  Implementation class for making the SMaker structs from DOM setup information. 
 *				The final results is returned as an SEngineMaker.
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

#include "DOMDefaultsImpl.h"
#include <DOMSetup/Misc/DOMHelperFunctions.h>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

CDOMDefaultsImpl::CDOMDefaultsImpl() : mParamTargetDefaults(),mInitTargetDefaults(),mNormTargetDefaults(),
									   mOutputTargetDefaults(),mAttenuationTargetDefaults(),mNoiseTargetDefaults(),
									   mPatternSetTargetDefaults(),mDataSourceTargetDefaults(),
									   mParamTypeDefaults(),mInitTypeDefaults(),mNormTypeDefaults(),
									   mOutputTypeDefaults(),mAttenuationTypeDefaults(),mNoiseTypeDefaults()
{

}	

CDOMDefaultsImpl::~CDOMDefaultsImpl()
{
	ReleaseAll();
}

void CDOMDefaultsImpl::AddParamsFromList(const DOMNodeList* paramList,std::vector<const DOMElement*>& vec,DOMErrorHandler* eHandler)
{
	for(XMLSize_t k1=0,ks1=paramList->getLength();k1<ks1;++k1) {
		const DOMElement* pDOMparam = GetElement(paramList,k1);
		for(size_t m1=0;m1<vec.size();++m1) {
			if (XMLStringUtil::Equals(vec[m1]->getAttribute(XMLStrDefs::name),pDOMparam->getAttribute(XMLStrDefs::name))) {
				CErrorHandler::PrepareError("Parameter defined multiple times in target- or typeDefaults.",pDOMparam,eHandler);
			}
		}
		vec.push_back(pDOMparam);
	}
}

void CDOMDefaultsImpl::AddTargetParams(const DOMElement* pDOMDefault,const DOMDocument* setupDoc,DOMErrorHandler* eHandler)
{
	std::vector<XMLCh*> targets = XMLStringUtil::Tokenise(pDOMDefault->getAttribute(XMLStrDefs::targets));
	XMLJanitor jan(targets);
	const DOMNodeList* pDOMparamList = GetElementList(pDOMDefault,XMLStrDefs::param);
	const DOMNodeList* pDOMloopParamList = GetElementList(pDOMDefault,XMLStrDefs::loopParam);
	for(size_t j1=0,js1=targets.size();j1<js1;++j1) {
		std::vector<const DOMElement*>& thisvec = mParamTargetDefaults[setupDoc->getElementById(targets[j1])];
		AddParamsFromList(pDOMparamList,thisvec,eHandler);
		AddParamsFromList(pDOMloopParamList,thisvec,eHandler);
	}
}

void CDOMDefaultsImpl::AddTypeParams(const DOMElement* pDOMDefault,const DOMDocument* setupDoc,DOMErrorHandler* eHandler)
{
	std::vector<XMLCh*> types = XMLStringUtil::Tokenise(pDOMDefault->getAttribute(XMLStrDefs::types));
	XMLJanitor jan(types);
	const DOMNodeList* pDOMparamList = GetElementList(pDOMDefault,XMLStrDefs::param);
	for(size_t j1=0,js1=types.size();j1<js1;++j1) {
		std::vector<const DOMElement*>& thisvec = mParamTypeDefaults[XMLStringUtil::XML2Str(types[j1])];
		AddParamsFromList(pDOMparamList,thisvec,eHandler);
	}
}

void CDOMDefaultsImpl::AddTargetObjects(LTarget2El& targetmap,const DOMElement* pDOMDefault,const XMLCh* tagName,
									 const DOMDocument* setupDoc,DOMErrorHandler* eHandler)
{
	std::vector<XMLCh*> targets = XMLStringUtil::Tokenise(pDOMDefault->getAttribute(XMLStrDefs::targets));
	XMLJanitor jan(targets);
	const DOMElement* pDOMfunction = GetElement(pDOMDefault,tagName,0);
	for(size_t j1=0,js1=targets.size();j1<js1;++j1) {
		const DOMElement* thistarget = setupDoc->getElementById(targets[j1]);
		if (targetmap.find(thistarget) == targetmap.end()) {
			targetmap.insert(LTarget2El::value_type(thistarget,pDOMfunction));
		}
		else {
			CErrorHandler::PrepareError("Multiple <" + XMLStringUtil::XML2Str(tagName) + "> defined for same target in <targetDefaults>.",pDOMDefault,eHandler);
		}
	}
}

void CDOMDefaultsImpl::AddTypeObjects(LType2El& typemap,const DOMElement* pDOMDefault,const XMLCh* tagName,DOMErrorHandler* eHandler)
{
	std::vector<XMLCh*> types = XMLStringUtil::Tokenise(pDOMDefault->getAttribute(XMLStrDefs::types));
	XMLJanitor jan(types);
	const DOMElement* pDOMfunction = GetElement(pDOMDefault,tagName,0);
	for(size_t j1=0,js1=types.size();j1<js1;++j1) {
		std::string typestr = XMLStringUtil::XML2Str(types[j1]);
		if (typemap.find(typestr) == typemap.end()) {
			typemap.insert(LType2El::value_type(typestr,pDOMfunction));
		}
		else {
			CErrorHandler::PrepareError("Multiple <" + XMLStringUtil::XML2Str(tagName) + "> defined for same type in <typeDefaults>.",pDOMDefault,eHandler);
		}
	}
}

void CDOMDefaultsImpl::AddOutputFunctions(LNumSites2El& typemap,const DOMElement* pDOMDefault,DOMErrorHandler* eHandler)
{
	std::vector<XMLCh*> numsites = XMLStringUtil::Tokenise(pDOMDefault->getAttribute(XMLStrDefs::numSites));
	XMLJanitor jan(numsites);
	const DOMElement* pDOMfunction = GetElement(pDOMDefault,XMLStrDefs::outputFunction,0);
	for(size_t j1=0,js1=numsites.size();j1<js1;++j1) {
		size_t thisnum = XMLStringUtil::XML2Int(numsites[j1]);
		if (typemap.find(thisnum) == typemap.end()) {
			typemap.insert(LNumSites2El::value_type(thisnum,pDOMfunction));
		}
		else {
			CErrorHandler::PrepareError("Multiple <outputFunction> defined for same number of <integrationSite> in <typeDefaults>.",pDOMDefault,eHandler);
		}
	}
}

void CDOMDefaultsImpl::CheckTypes(const DOMElement* thisEl,const DOMDocument* valDoc,DOMErrorHandler* eHandler,const XMLCh* targetName1,const XMLCh* targetName2)
{
	std::vector<XMLCh*> types = XMLStringUtil::Tokenise(thisEl->getAttribute(XMLStrDefs::types));
	XMLJanitor jan(types);
	for(size_t j1=0,js1=types.size();j1<js1;++j1) {
		const DOMElement* pDOMvalEl = valDoc->getElementById(types[j1]);
		if (!pDOMvalEl) {
			CErrorHandler::PrepareError("Unknown type name.",thisEl,eHandler);
		}
		else if (!XMLStringUtil::Equals(targetName1,pDOMvalEl->getTagName()) &&
			!XMLStringUtil::Equals(targetName2,pDOMvalEl->getTagName())) {
			CErrorHandler::PrepareError("Wrong type name for element.",thisEl,eHandler);
		}
	}
}

void CDOMDefaultsImpl::Handle(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler)
{
	const DOMElement* pDOMTargetDefaults = GetElement(setupDoc,XMLStrDefs::targetDefaults,0);
	if (pDOMTargetDefaults) {
		const DOMNodeList* pDOMDefaultList = GetElementList(pDOMTargetDefaults,XMLStrDefs::xmldefault);
		for(XMLSize_t i1=0,is1=pDOMDefaultList->getLength();i1<is1;++i1) {
			const DOMElement* pDOMDefault = GetElement(pDOMDefaultList,i1);
			CheckDupl(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets);
			if (GetElement(pDOMDefault,XMLStrDefs::taskParams,0)) {
				CheckIDREFS(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::task,XMLStrDefs::compositeTask);
				AddTargetParams(pDOMDefault,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::netParams,0)) {
				CheckIDREFS(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::network);
				AddTargetParams(pDOMDefault,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::blockParams,0)) {
				CheckIDREFS(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::block);
				AddTargetParams(pDOMDefault,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::siteParams,0)) {
				CheckIDREFS(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::integrationSite);
				AddTargetParams(pDOMDefault,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::initialisation,0)) {
				CheckIDREFS(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::integrationSite);
				AddTargetObjects(mInitTargetDefaults,pDOMDefault,XMLStrDefs::initialisation,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::normalisation,0)) {
				CheckIDREFS(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::integrationSite);
				AddTargetObjects(mNormTargetDefaults,pDOMDefault,XMLStrDefs::normalisation,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::outputFunction,0)) {
				CheckIDREFS(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::block);
				AddTargetObjects(mOutputTargetDefaults,pDOMDefault,XMLStrDefs::outputFunction,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::attenuation,0)) {
				CheckIDREFS(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::task,XMLStrDefs::outputFunction,true);
				AddTargetObjects(mAttenuationTargetDefaults,pDOMDefault,XMLStrDefs::attenuation,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::noiseFunction,0)) {
				CheckIDREFS(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::task,XMLStrDefs::outputFunction,true);
				AddTargetObjects(mNoiseTargetDefaults,pDOMDefault,XMLStrDefs::noiseFunction,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::patternSet,0)) {
				CheckIDREFS(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::task);
				AddTargetObjects(mPatternSetTargetDefaults,pDOMDefault,XMLStrDefs::patternSet,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::dataSource,0)) {
				CheckIDREFS(pDOMDefault,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::task);
				AddTargetObjects(mDataSourceTargetDefaults,pDOMDefault,XMLStrDefs::dataSource,setupDoc,eHandler);
			}
		}
	}
	const DOMElement* pDOMTypeDefaults = GetElement(setupDoc,XMLStrDefs::typeDefaults,0);
	if (pDOMTypeDefaults) {
		const DOMNodeList* pDOMDefaultList = GetElementList(pDOMTypeDefaults,XMLStrDefs::xmldefault);
		for(XMLSize_t i1=0,is1=pDOMDefaultList->getLength();i1<is1;++i1) {
			const DOMElement* pDOMDefault = GetElement(pDOMDefaultList,i1);
			if (pDOMDefault->hasAttribute(XMLStrDefs::types))
				CheckDupl(pDOMDefault,setupDoc,eHandler,XMLStrDefs::types);
			if (pDOMDefault->hasAttribute(XMLStrDefs::numSites))
				CheckDupl(pDOMDefault,setupDoc,eHandler,XMLStrDefs::numSites);
			if (GetElement(pDOMDefault,XMLStrDefs::taskParams,0)) {
				ExOrAttr(XMLStrDefs::types,XMLStrDefs::numSites,pDOMDefault,eHandler);
				CheckTypes(pDOMDefault,valDoc,eHandler,XMLStrDefs::task);
				AddTypeParams(pDOMDefault,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::netParams,0)) {
				ExOrAttr(XMLStrDefs::types,XMLStrDefs::numSites,pDOMDefault,eHandler);
				CheckTypes(pDOMDefault,valDoc,eHandler,XMLStrDefs::network);
				AddTypeParams(pDOMDefault,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::blockParams,0)) {
				ExOrAttr(XMLStrDefs::types,XMLStrDefs::numSites,pDOMDefault,eHandler);
				CheckTypes(pDOMDefault,valDoc,eHandler,XMLStrDefs::block);
				AddTypeParams(pDOMDefault,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::siteParams,0)) {
				ExOrAttr(XMLStrDefs::types,XMLStrDefs::numSites,pDOMDefault,eHandler);
				CheckTypes(pDOMDefault,valDoc,eHandler,XMLStrDefs::integrationSite);
				AddTypeParams(pDOMDefault,setupDoc,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::initialisation,0)) {
				ExOrAttr(XMLStrDefs::types,XMLStrDefs::numSites,pDOMDefault,eHandler);
				CheckTypes(pDOMDefault,valDoc,eHandler,XMLStrDefs::integrationSite);
				AddTypeObjects(mInitTypeDefaults,pDOMDefault,XMLStrDefs::initialisation,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::normalisation,0)) {
				ExOrAttr(XMLStrDefs::types,XMLStrDefs::numSites,pDOMDefault,eHandler);
				CheckTypes(pDOMDefault,valDoc,eHandler,XMLStrDefs::integrationSite);
				AddTypeObjects(mNormTypeDefaults,pDOMDefault,XMLStrDefs::normalisation,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::outputFunction,0)) {
				ExOrAttr(XMLStrDefs::numSites,XMLStrDefs::types,pDOMDefault,eHandler);
				AddOutputFunctions(mOutputTypeDefaults,pDOMDefault,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::attenuation,0)) {
				ExOrAttr(XMLStrDefs::types,XMLStrDefs::numSites,pDOMDefault,eHandler);
				CheckTypes(pDOMDefault,valDoc,eHandler,XMLStrDefs::task,XMLStrDefs::outputFunction);
				AddTypeObjects(mAttenuationTypeDefaults,pDOMDefault,XMLStrDefs::attenuation,eHandler);
			}
			else if (GetElement(pDOMDefault,XMLStrDefs::noiseFunction,0)) {
				ExOrAttr(XMLStrDefs::types,XMLStrDefs::numSites,pDOMDefault,eHandler);
				CheckTypes(pDOMDefault,valDoc,eHandler,XMLStrDefs::task,XMLStrDefs::outputFunction);
				AddTypeObjects(mNoiseTypeDefaults,pDOMDefault,XMLStrDefs::noiseFunction,eHandler);
			}
		}
	}
}

const std::vector<const DOMElement*>* CDOMDefaultsImpl::GetParams(const DOMElement* el)
{
	if (mParamTargetDefaults.find(el) != mParamTargetDefaults.end()) {
		return &(mParamTargetDefaults[el]);
	}
	else
		return 0;
}
	
const std::vector<const DOMElement*>* CDOMDefaultsImpl::GetParams(const XMLCh* typeXCh)
{
	std:: string typestr = XMLStringUtil::XML2Str(typeXCh);
	if (mParamTypeDefaults.find(typestr) != mParamTypeDefaults.end()) {
		return &(mParamTypeDefaults[typestr]);
	}
	else
		return 0;
}
	
const DOMElement* CDOMDefaultsImpl::GetObject(const DOMElement* el,const XMLCh* tag)
{
	const DOMElement* defaultEl = 0;
	if (XMLStringUtil::Equals(tag,XMLStrDefs::initialisation)) {
		if (mInitTargetDefaults.find(el) != mInitTargetDefaults.end())
			defaultEl = mInitTargetDefaults[el];
	}
	else if (XMLStringUtil::Equals(tag,XMLStrDefs::normalisation)) {
		if (mNormTargetDefaults.find(el) != mNormTargetDefaults.end())
			defaultEl = mNormTargetDefaults[el];
	}
	else if (XMLStringUtil::Equals(tag,XMLStrDefs::outputFunction)) {
		if (mOutputTargetDefaults.find(el) != mOutputTargetDefaults.end())
			defaultEl = mOutputTargetDefaults[el];
	}
	else if (XMLStringUtil::Equals(tag,XMLStrDefs::attenuation)) {
		if (mAttenuationTargetDefaults.find(el) != mAttenuationTargetDefaults.end())
			defaultEl = mAttenuationTargetDefaults[el];
	}
	else if (XMLStringUtil::Equals(tag,XMLStrDefs::noiseFunction)) {
		if (mNoiseTargetDefaults.find(el) != mNoiseTargetDefaults.end())
			defaultEl = mNoiseTargetDefaults[el];
	}
	else if (XMLStringUtil::Equals(tag,XMLStrDefs::patternSet)) {
		if (mPatternSetTargetDefaults.find(el) != mPatternSetTargetDefaults.end())
			defaultEl = mPatternSetTargetDefaults[el];
	}
	else if (XMLStringUtil::Equals(tag,XMLStrDefs::dataSource)) {
		if (mDataSourceTargetDefaults.find(el) != mDataSourceTargetDefaults.end())
			defaultEl = mDataSourceTargetDefaults[el];
	}
	return defaultEl;
}
	
const DOMElement* CDOMDefaultsImpl::GetObject(const XMLCh* typeXCh,const XMLCh* tag)
{
	const DOMElement* defaultEl = 0;
	std::string typestr = XMLStringUtil::XML2Str(typeXCh);
	if (XMLStringUtil::Equals(tag,XMLStrDefs::initialisation)) {
		if (mInitTypeDefaults.find(typestr) != mInitTypeDefaults.end())
			defaultEl = mInitTypeDefaults[typestr];
	}
	else if (XMLStringUtil::Equals(tag,XMLStrDefs::normalisation)) {
		if (mNormTypeDefaults.find(typestr) != mNormTypeDefaults.end())
			defaultEl = mNormTypeDefaults[typestr];
	}
	else if (XMLStringUtil::Equals(tag,XMLStrDefs::attenuation)) {
		if (mAttenuationTypeDefaults.find(typestr) != mAttenuationTypeDefaults.end())
			defaultEl = mAttenuationTypeDefaults[typestr];
	}
	else if (XMLStringUtil::Equals(tag,XMLStrDefs::noiseFunction)) {
		if (mNoiseTypeDefaults.find(typestr) != mNoiseTypeDefaults.end())
			defaultEl = mNoiseTypeDefaults[typestr];
	}
	return defaultEl;
}

const DOMElement* CDOMDefaultsImpl::GetOutputFunction(size_t numsites)
{
	const DOMElement* defaultEl = 0;
	if (mOutputTypeDefaults.find(numsites) != mOutputTypeDefaults.end())
		defaultEl = mOutputTypeDefaults[numsites];
	return defaultEl;
}

void CDOMDefaultsImpl::ReleaseAll()
{
	mParamTargetDefaults.clear();
	mInitTargetDefaults.clear();
	mNormTargetDefaults.clear();
	mOutputTargetDefaults.clear();
	mAttenuationTargetDefaults.clear();
	mNoiseTargetDefaults.clear();
	mPatternSetTargetDefaults.clear();
	mDataSourceTargetDefaults.clear();
	mParamTypeDefaults.clear();
	mInitTypeDefaults.clear();
	mNormTypeDefaults.clear();
	mOutputTypeDefaults.clear();
	mAttenuationTypeDefaults.clear();
	mNoiseTypeDefaults.clear();
}

} //end namespace CORINET
