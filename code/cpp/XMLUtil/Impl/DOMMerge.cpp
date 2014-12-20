/*********************************************************************************************
 * Name      :  DOMMerge.cpp
 *
 * Purpose   :  Merges a DOM for validation with additional sandbox DOM definitions.
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

#include <XMLUtil/XMLStrDefs.h>
#include <XMLUtil/XMLStringUtil.h>
#include <XMLUtil/DOMMerge.h>
#include <XMLUtil/DOMError.h>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

void CDOMMerge::MergeType(DOMDocument* destDoc,const DOMDocument* toMerge,DOMErrorHandler* eHandler,const XMLCh* typeXCh)
{
	XMLCh tempXCh[128] = {chNull};
	XMLStringUtil::Append(tempXCh,typeXCh);
	XMLStringUtil::Append(tempXCh,XMLStrDefs::Section);
	DOMElement* pDOMSection = static_cast<DOMElement*>(destDoc->getElementsByTagName(tempXCh)->item(0));

	DOMNodeList* pDOMelemList = toMerge->getElementsByTagName(typeXCh);
	for(XMLSize_t i=0,is=pDOMelemList->getLength();i<is;++i) {
		DOMElement* pDOMelem = static_cast<DOMElement*>(pDOMelemList->item(i));

		if (XMLStringUtil::Equals(XMLStrDefs::part,pDOMelem->getTagName())) {
			DOMNode* pDOMnewNode = destDoc->importNode(pDOMelem,true);
			pDOMSection->appendChild(pDOMnewNode);
		}
		else if (!destDoc->getElementById(pDOMelem->getAttribute(XMLStrDefs::type))) {
			DOMNode* pDOMnewNode = destDoc->importNode(pDOMelem,true);
			pDOMSection->appendChild(pDOMnewNode);
			static_cast<DOMElement*>(pDOMnewNode)->setIdAttribute(XMLStrDefs::type);
		}
		else {
			CErrorHandler::PrepareError("Type defined multiple times across different language definition files.\n",pDOMelem,eHandler);
		}
	}
}

void CDOMMerge::Merge(DOMDocument* destDoc,const DOMDocument* toMerge,DOMErrorHandler* eHandler)
{
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::randGen);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::attenuation);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::noiseFunction);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::initialisation);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::normalisation);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::outputFunction);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::location);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::integrationSite);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::block);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::network);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::dataSource);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::task);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::compositeTask);
	CDOMMerge::MergeType(destDoc,toMerge,eHandler,XMLStrDefs::execution);
}

} //end namespace CORINET
