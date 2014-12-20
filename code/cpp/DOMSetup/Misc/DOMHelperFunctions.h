/*********************************************************************************************
 * Name      :  DOMHelperFunctions.h
 *
 * Purpose   :  Common helper functions for validation and setup.
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

#ifndef CORINET_DOMHELPERFUNCTIONS
#define CORINET_DOMHELPERFUNCTIONS

XERCES_CPP_NAMESPACE_USE

#include <Util/Util.h>
#include <XMLUtil/DOMError.h>
#include <XMLUtil/XMLStrDefs.h>
#include <XMLUtil/XMLStringUtil.h>
#include <XMLUtil/XMLJanitor.h>
#include <xercesc/dom/DOM.hpp>
#include <string>
#include <vector>
#include <valarray>
#include <limits>

#define XERCES XERCES_CPP_NAMESPACE 

namespace {//unnamed namespace
	using CORINET::XMLStrDefs;
	using CORINET::XMLStringUtil;
	using CORINET::XMLJanitor;
	using CORINET::CErrorHandler;

void ExOrAttr(const XMLCh* attrName1,const XMLCh* attrName2,const DOMElement* el,DOMErrorHandler* eHandler)
{
	if (!el->hasAttribute(attrName1)) {
		CErrorHandler::PrepareError("Attribute \"" + XMLStringUtil::XML2Str(attrName1) + "\" missing in this type of element.",el,eHandler);
	}
	if (el->hasAttribute(attrName2)) {
		CErrorHandler::PrepareError("Attribute \"" + XMLStringUtil::XML2Str(attrName2) + "\" not allowed in this type of elemennt.",el,eHandler);
	}
}

const DOMNodeList* GetElementList(const DOMElement* parent,const XMLCh* tagName)
{
	return parent->getElementsByTagName(tagName);
}

const DOMNodeList* GetElementList(const DOMDocument* setupDoc,const XMLCh* tagName)
{
	return setupDoc->getElementsByTagName(tagName);
}

const DOMElement* GetElement(const DOMElement* parent,const XMLCh* tagName,size_t index)
{
	return static_cast<DOMElement*>(GetElementList(parent,tagName)->item(index));
}

const DOMElement* GetElement(const DOMDocument* setupDoc,const XMLCh* tagName,size_t index)
{
	return static_cast<DOMElement*>(GetElementList(setupDoc,tagName)->item(index));
}

const DOMElement* GetElement(const DOMNodeList* elList,size_t index)
{
	return static_cast<DOMElement*>(elList->item(index));
}

DOMElement* GetType(const DOMElement* thisEl,const DOMDocument* valDoc,DOMErrorHandler* eHandler)
{
	DOMElement* pDOMvalEl = 0;
	if (thisEl->hasAttribute(XMLStrDefs::type)) {
		const XMLCh* typeXCh = thisEl->getAttribute(XMLStrDefs::type);
		pDOMvalEl = valDoc->getElementById(typeXCh);
		if (!pDOMvalEl) {
			CErrorHandler::PrepareError("Unknown type name.",thisEl,eHandler);
		}
		else if (!XMLStringUtil::Equals(thisEl->getTagName(),pDOMvalEl->getTagName())) {
			CErrorHandler::PrepareError("Wrong type name for element.",thisEl,eHandler);
		}
	}
	return pDOMvalEl;
}

void CheckDupl(const DOMElement* thisEl,const DOMDocument* setupDoc,DOMErrorHandler* eHandler,
				 const XMLCh* attrName)
{
	if (thisEl->hasAttribute(attrName)) {
		std::vector<XMLCh*> idrefs = XMLStringUtil::Tokenise(thisEl->getAttribute(attrName));
		XMLJanitor jan(idrefs);
		for(size_t j=0,js=idrefs.size();j<js;++j) {
			const XMLCh* thisref = idrefs[j];
			for(size_t k=j+1,ks=idrefs.size();k<ks;++k) {
				if (XMLStringUtil::Equals(thisref,idrefs[k]))
					CErrorHandler::PrepareError("\"" + XMLStringUtil::XML2Str(thisref) + "\" used multiple times in \"" + XMLStringUtil::XML2Str(attrName) + "\".",thisEl,eHandler);
			}
		}
	}
}

bool CheckIDREF(const XMLCh* idref,const DOMDocument* setupDoc,const XMLCh* targetName)
{
	bool equals = false;
	DOMElement* thistarget = setupDoc->getElementById(idref);
	if (XMLStringUtil::Equals(thistarget->getTagName(),targetName)) {
		equals = true;
	}
	return equals;
}

void CheckIDREFS(const DOMElement* thisEl,const DOMDocument* setupDoc,DOMErrorHandler* eHandler,
				 const XMLCh* attrName,const XMLCh* targetName)
{
	if (thisEl->hasAttribute(attrName)) {
		std::vector<XMLCh*> idrefs = XMLStringUtil::Tokenise(thisEl->getAttribute(attrName));
		XMLJanitor jan(idrefs);
		for(size_t j=0,js=idrefs.size();j<js;++j) {
			const XMLCh* thisref = idrefs[j];
			if (!CheckIDREF(thisref,setupDoc,targetName)) {
				CErrorHandler::PrepareError("IDREF \"" + XMLStringUtil::XML2Str(thisref) + "\" refers to wrong type of element.",thisEl,eHandler);
			}
		}
	}
}				

void CheckIDREFS(const DOMElement* thisEl,const DOMDocument* setupDoc,DOMErrorHandler* eHandler,
				 const XMLCh* attrName,const XMLCh* targetName1,const XMLCh* targetName2,bool exor =false)
{
	if (thisEl->hasAttribute(attrName)) {
		std::vector<XMLCh*> idrefs = XMLStringUtil::Tokenise(thisEl->getAttribute(attrName));
		XMLJanitor jan(idrefs);
		bool target1 = false;
		bool target2 = false;
		for(size_t j=0,js=idrefs.size();j<js;++j) {
			const XMLCh* thisref = idrefs[j];
			if (!CheckIDREF(thisref,setupDoc,targetName1) && !CheckIDREF(thisref,setupDoc,targetName2)) {
				CErrorHandler::PrepareError("IDREF \"" + XMLStringUtil::XML2Str(thisref) + "\" refers to wrong type of element.",thisEl,eHandler);
			}
			if (exor) {
				target1 |= CheckIDREF(thisref,setupDoc,targetName1);
				target2 |= CheckIDREF(thisref,setupDoc,targetName2);
				if (target1 && target2) {
					CErrorHandler::PrepareError("<default> cannot be used in both <task> and <outputFunction> elements.",thisEl,eHandler);
				}
			}
		}
	}
}

size_t GetParamNum(const XMLCh* paramName,const DOMNodeList* valList)
{
	for(size_t j1=0,js1=valList->getLength();j1<js1;++j1) {
		const DOMElement* valParam = GetElement(valList,j1);
		if (XMLStringUtil::Equals(paramName,valParam->getAttribute(XMLStrDefs::name))) {
			return j1;
		}
	}
	return std::numeric_limits<size_t>::max();
}

size_t GetParamNum(const XMLCh* paramName,const DOMElement* valNode)
{
	const DOMNodeList* valList = GetElementList(valNode,XMLStrDefs::param);
	return GetParamNum(paramName,valList);
}

void GetParamVals(std::valarray<double>& vals,const DOMNodeList* elList,const DOMNodeList* valList,
				DOMErrorHandler* eHandler,const DOMElement* parentNode)
{
	for(XMLSize_t i1=0,is1=elList->getLength();i1<is1;++i1) {
		const DOMElement* pDOMParam = GetElement(elList,i1);
		const XMLCh* paramName = pDOMParam->getAttribute(XMLStrDefs::name);
		size_t paramnum = GetParamNum(paramName,valList);
		if (paramnum == std::numeric_limits<size_t>::max()) {
			CErrorHandler::PrepareError("Parameter \"" + XMLStringUtil::XML2Str(paramName) + "\" not allowed for this type.",parentNode,eHandler);
		}
		else if (vals[paramnum]>std::numeric_limits<double>::min()) {
			CErrorHandler::PrepareError("Parameter \"" + XMLStringUtil::XML2Str(paramName) + "\" defined multiple times.",parentNode,eHandler);
		}
		else if (pDOMParam->hasAttribute(XMLStrDefs::value)) {
			vals[paramnum] = XMLStringUtil::XML2Dbl(pDOMParam->getAttribute(XMLStrDefs::value));
		}
		else if (pDOMParam->hasAttribute(XMLStrDefs::values)) {
			std::vector<XMLCh*> values = XMLStringUtil::Tokenise(pDOMParam->getAttribute(XMLStrDefs::values));
			XMLJanitor jan(values);
			vals[paramnum] = XMLStringUtil::XML2Dbl(values[0]);
		}
	}
}

void GetDefaultParamVals(std::valarray<double>& vals,const std::vector<const DOMElement*>* elVec,const DOMNodeList* valList,
						 DOMErrorHandler* eHandler,const DOMElement* parentNode)
{
	for(size_t i1=0,is1=elVec->size();i1<is1;++i1) {
		const DOMElement* pDOMParam = (*elVec)[i1];
		const XMLCh* paramName = pDOMParam->getAttribute(XMLStrDefs::name);
		size_t paramnum = GetParamNum(paramName,valList);
		if (paramnum == std::numeric_limits<size_t>::max()) {
			CErrorHandler::PrepareError("Parameter \"" + XMLStringUtil::XML2Str(paramName) + "\" not allowed for this type.",parentNode,eHandler);
		}
		else if ((vals[paramnum] == std::numeric_limits<double>::min()) && pDOMParam->hasAttribute(XMLStrDefs::value)) {
			vals[paramnum] = XMLStringUtil::XML2Dbl(pDOMParam->getAttribute(XMLStrDefs::value));
		}
		else if ((vals[paramnum] == std::numeric_limits<double>::min()) && pDOMParam->hasAttribute(XMLStrDefs::values)) {
			std::vector<XMLCh*> values = XMLStringUtil::Tokenise(pDOMParam->getAttribute(XMLStrDefs::values));
			XMLJanitor jan(values);
			vals[paramnum] = XMLStringUtil::XML2Dbl(values[0]);
		}
	}
}

void GetOptionalParams(std::valarray<double>& vals,const DOMNodeList* valList)
{	
	for(XMLSize_t j1=0,js1=valList->getLength();j1<js1;++j1) {
		const DOMElement* valParam = GetElement(valList,j1);
		if ((vals[j1] == std::numeric_limits<double>::min()) && 
			XMLStringUtil::Equals(valParam->getAttribute(XMLStrDefs::use),XMLStrDefs::optional)) {
			vals[j1] = XMLStringUtil::XML2Dbl(valParam->getAttribute(XMLStrDefs::xmldefault));
		}
	}
}

void CheckMissingParams(std::valarray<double>& vals,const DOMNodeList* valList,
						DOMErrorHandler* eHandler,const DOMElement* parentNode)
{
	if (valList->getLength()) {
		for(size_t j=0,js=vals.size();j<js;++j) {
			if (vals[j] == std::numeric_limits<double>::min()) {
				const XMLCh* paramName = GetElement(valList,j)->getAttribute(XMLStrDefs::name);
				CErrorHandler::PrepareError("Parameter \"" + XMLStringUtil::XML2Str(paramName) + "\" not defined.",parentNode,eHandler);
			}
		}
	}
}

void HandleParams(std::valarray<double>& vals,const DOMElement* paramContainer,
				  const DOMElement* valEl,DOMErrorHandler* eHandler,const DOMElement* parentNode,
				  const std::vector<const DOMElement*>* targetDef =0,
				  const std::vector<const DOMElement*>* typeDef =0)
{
	//check the list of parameters for missing, duplicate and wrong parameters
	const DOMNodeList* pDOMvalParamList = GetElementList(valEl,XMLStrDefs::param);
	if (paramContainer) {
		const DOMNodeList* pDOMParamList = GetElementList(paramContainer,XMLStrDefs::param);
		const DOMNodeList* pDOMLoopParamList = GetElementList(paramContainer,XMLStrDefs::loopParam);		
		
		GetParamVals(vals,pDOMParamList,pDOMvalParamList,eHandler,parentNode);
		GetParamVals(vals,pDOMLoopParamList,pDOMvalParamList,eHandler,parentNode);
	}
	if (targetDef) {
		GetDefaultParamVals(vals,targetDef,pDOMvalParamList,eHandler,parentNode);
	}
	if (typeDef) {
		GetDefaultParamVals(vals,typeDef,pDOMvalParamList,eHandler,parentNode);
	}
	GetOptionalParams(vals,pDOMvalParamList);	
	CheckMissingParams(vals,pDOMvalParamList,eHandler,parentNode);
}

void CheckChildElement(const DOMElement* el,const DOMElement* valEl,
					   DOMErrorHandler* eHandler,const XMLCh* elName)
{
	const XMLCh* useXCh = valEl->getAttribute(elName);
	const DOMElement* pDOMchild = GetElement(el,elName,0);
	if (XMLStringUtil::Equals(useXCh,XMLStrDefs::prohibited) && pDOMchild) {
		CErrorHandler::PrepareError("<" + XMLStringUtil::XML2Str(elName) + "> prohibited for this type.",el,eHandler);
	}
	if (XMLStringUtil::Equals(useXCh,XMLStrDefs::required) && !pDOMchild) {
		CErrorHandler::PrepareError("<" + XMLStringUtil::XML2Str(elName) + "> required for this type.",el,eHandler);
	}
}

const DOMElement* BelongsToElementType(const DOMElement* el,const DOMDocument* setupDoc)
{
	const DOMElement* parentEl = el;
	for(;;) {
		const XMLCh* tagName = parentEl->getTagName();
		if (XMLStringUtil::Equals(tagName,XMLStrDefs::execution) || XMLStringUtil::Equals(tagName,XMLStrDefs::network) ||
			XMLStringUtil::Equals(tagName,XMLStrDefs::compositeTask) || XMLStringUtil::Equals(tagName,XMLStrDefs::experiment)) {
			return parentEl;
		}
		else if (XMLStringUtil::Equals(tagName,XMLStrDefs::task)) {
			if (!XMLStringUtil::Equals(static_cast<DOMElement*>(parentEl->getParentNode())->getTagName(),XMLStrDefs::insert))
				return parentEl;
		}
		if (XMLStringUtil::Equals(tagName,XMLStrDefs::xmldefault)) {
			std::vector<XMLCh*> targets = XMLStringUtil::Tokenise(parentEl->getAttribute(XMLStrDefs::targets));
			XMLJanitor jan(targets);
			parentEl = setupDoc->getElementById(targets[0]);
		}
		else
			parentEl = static_cast<DOMElement*>(parentEl->getParentNode());
	}
	return 0;
}

const DOMElement* BelongsToElement(const DOMElement* el,const DOMDocument* setupDoc)
{
	const DOMElement* parentEl = el;
	for(;;) {
		const XMLCh* tagName = parentEl->getTagName();
		if (XMLStringUtil::Equals(tagName,XMLStrDefs::execution) || XMLStringUtil::Equals(tagName,XMLStrDefs::network) ||
			XMLStringUtil::Equals(tagName,XMLStrDefs::compositeTask) || XMLStringUtil::Equals(tagName,XMLStrDefs::experiment) ||
			XMLStringUtil::Equals(tagName,XMLStrDefs::xmldefault)) {
			return parentEl;
		}
		else if (XMLStringUtil::Equals(tagName,XMLStrDefs::task)) {
			if (!XMLStringUtil::Equals(static_cast<DOMElement*>(parentEl->getParentNode())->getTagName(),XMLStrDefs::insert))
				return parentEl;
		}
		parentEl = static_cast<DOMElement*>(parentEl->getParentNode());
	}
	return 0;
}

bool GetBool(const DOMElement* el,const XMLCh* attrName)
{
	bool b = false;
	if (el->hasAttribute(attrName)) {
		std::string boolstr = XMLStringUtil::XML2Str(el->getAttribute(attrName));
		if ((boolstr == "true") || (boolstr == "1")) {
			b = true;
		}
	}
	return b;
}

std::valarray<size_t>* GetAttrInd(const DOMElement* pDOMel,const XMLCh* attrName)
{
	std::vector<XMLCh*> indXCh = XMLStringUtil::Tokenise(pDOMel->getAttribute(attrName));
	XMLJanitor jan(indXCh);
	std::valarray<size_t>* indices = new std::valarray<size_t>(indXCh.size());
	for(size_t i1=0,is1=indXCh.size();i1<is1;++i1) {
		(*indices)[i1] = XMLStringUtil::XML2Int(indXCh[i1]);
	}
	return indices;
}

std::valarray<double>* GetAttrVals(const DOMElement* pDOMel,const XMLCh* attrName)
{
	std::vector<XMLCh*> valsXCh = XMLStringUtil::Tokenise(pDOMel->getAttribute(attrName));
	XMLJanitor jan(valsXCh);
	std::valarray<double>* vals = new std::valarray<double>(valsXCh.size());
	for(size_t i1=0,is1=valsXCh.size();i1<is1;++i1) {
		(*vals)[i1] = XMLStringUtil::XML2Dbl(valsXCh[i1]);
	}
	return vals;
}

void Get2DVals(const DOMElement* pDOMel,size_t rows,size_t columns,const XMLCh* rowTag,const XMLCh* colTag,
				   const DOMElement* errorNode,DOMErrorHandler* eHandler,std::valarray<double>* vals =0)
{
	//read the weights in, or simply check their structure
	const DOMNodeList* pDOMcolList = GetElementList(pDOMel,colTag);
	if (pDOMcolList->getLength()) {
		if (pDOMcolList->getLength() != columns) {
			CErrorHandler::PrepareError("Wrong number of <" + XMLStringUtil::XML2Str(colTag) + "> elements.",errorNode,eHandler);
		}
		for(XMLSize_t c1=0;c1<columns;++c1) {
			const DOMElement* pDOMcol = GetElement(pDOMcolList,c1);
			DOMNodeList* pChildren = pDOMcol->getChildNodes();
			size_t rowCounter = 0;
			for(XMLSize_t v1=0,vs1=pChildren->getLength();v1<vs1;++v1) {
				if (pChildren->item(v1)->getNodeType() == DOMNode::TEXT_NODE) {
					std::vector<XMLCh*> valsXCh = XMLStringUtil::Tokenise(pChildren->item(v1)->getNodeValue());
					XMLJanitor jan(valsXCh);
					if (vals) {//read in the values
						for(size_t m1=0,ms1=valsXCh.size();m1<ms1;++m1) {
							if (rowCounter >= rows) {
								CErrorHandler::PrepareError("Too many values in <" + XMLStringUtil::XML2Str(colTag) + "> element.",errorNode,eHandler);
							}
							(*vals)[c1*rows+(rowCounter++)] = XMLStringUtil::XML2Dbl(valsXCh[m1]);
						}
					}
					else {//just check the number of inputs
						rowCounter += valsXCh.size();
					}
				}		
			}
			if (rowCounter != rows) {
				CErrorHandler::PrepareError("Wrong number of values in <" + XMLStringUtil::XML2Str(colTag) + "> element.",errorNode,eHandler);
			}
		}
	}
	else {
		const DOMNodeList* pDOMrowList = GetElementList(pDOMel,rowTag);
		if (pDOMrowList->getLength() != rows) {
			CErrorHandler::PrepareError("Wrong number of <" + XMLStringUtil::XML2Str(rowTag) + "> elements.",errorNode,eHandler);
		}
		for(XMLSize_t r1=0;r1<rows;++r1) {
			const DOMElement* pDOMrow = GetElement(pDOMrowList,r1);
			DOMNodeList* pChildren = pDOMrow->getChildNodes();
			size_t colCounter = 0;
			for(XMLSize_t v1=0,vs1=pChildren->getLength();v1<vs1;++v1) {
				if (pChildren->item(v1)->getNodeType() == DOMNode::TEXT_NODE) {
					std::vector<XMLCh*> valsXCh = XMLStringUtil::Tokenise(pChildren->item(v1)->getNodeValue());
					XMLJanitor jan(valsXCh);
					if (vals) {
						for(size_t m1=0,ms1=valsXCh.size();m1<ms1;++m1) {
							if (colCounter >= columns) {
								CErrorHandler::PrepareError("Too many values in <" + XMLStringUtil::XML2Str(rowTag) + "> element.",errorNode,eHandler);
							}
							(*vals)[(colCounter++)*rows+r1] = XMLStringUtil::XML2Dbl(valsXCh[m1]);
						}
					}
					else {
						colCounter += valsXCh.size();
					}
				}
			}
			if (colCounter != columns) {
				CErrorHandler::PrepareError("Wrong number of values in <" + XMLStringUtil::XML2Str(rowTag) + "> element.",errorNode,eHandler);
			}
		}
	}
}

} //end unnamed namespace

#endif //CORINET_DOMHELPERFUNCTIONS
