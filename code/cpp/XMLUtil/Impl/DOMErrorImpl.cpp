/*********************************************************************************************
 * Name      :  ErrorImpl.cpp
 *
 * Purpose   :  Implementation classes for CErrorHandler interface (derived from DOMErrorHandler).
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

#include "DOMErrorImpl.h"
#include <XMLUtil/XMLStrDefs.h>
#include <XMLUtil/XMLStringUtil.h>
#include <Client/MessageHandler.h>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

CErrorHandlerImpl::CErrorHandlerImpl(CMessageHandler* pmes) : pMessageHandler(pmes),ost()
{
	
}

CErrorHandlerImpl::~CErrorHandlerImpl()
{
	
}

bool CErrorHandlerImpl::handleError(const DOMError& e)
{
	//get the error message
	pMessageHandler->Handle(XMLStringUtil::XML2Str(e.getMessage()),true);
	
	//get the location in the file or DOM where the error occurred
	DOMLocator* ploc = e.getLocation();
	if (ploc) {
		XMLSize_t linenum = ploc->getLineNumber();
		if (linenum != -1) {
			ost << "Error occurred ";
			const XMLCh* uriXCh = ploc->getURI();
			if (uriXCh && *uriXCh) {
				ost <<  "in file " << XMLStringUtil::XML2Str(uriXCh);
			}
			ost << " on line " << linenum;
		}
		else {
			DOMElement* pErrorElement = static_cast<DOMElement*>(ploc->getErrorNode());
			if (pErrorElement) {
				//get the element tag name
				ost << "Error occured in <" << XMLStringUtil::XML2Str(pErrorElement->getTagName());
				if (pErrorElement->hasAttribute(XMLStrDefs::type)) {
					ost << " type=\"" << XMLStringUtil::XML2Str(pErrorElement->getAttribute(XMLStrDefs::type)) << "\"";
				}
				if (pErrorElement->hasAttribute(XMLStrDefs::name)) {
					ost << " name=\"" << XMLStringUtil::XML2Str(pErrorElement->getAttribute(XMLStrDefs::name)) << "\"";
				}
				if (pErrorElement->hasAttribute(XMLStrDefs::id)) {
					ost << " id=\"" << XMLStringUtil::XML2Str(pErrorElement->getAttribute(XMLStrDefs::id)) << "\"";
				}
				ost << ">\0";
			}
		}
		pMessageHandler->Handle(ost.str(),true);
	}
	ost.seekp(0);
	throw DOMException(DOMException::VALIDATION_ERR,0);
	return false;
}

void CErrorHandlerImpl::handleMessage(const std::string& mes)
{
	pMessageHandler->Handle(mes,true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CErrorLocator::CErrorLocator() : pErrorNode(0)
{
}

CErrorLocator::~CErrorLocator()
{

}
	 
DOMNode* CErrorLocator::getErrorNode() const
{
	return pErrorNode;
}
	
void CErrorLocator::setErrorNode(XERCES_CPP_NAMESPACE::DOMNode* const node)
{
	pErrorNode = node;
}

XMLSSize_t CErrorLocator::getLineNumber() const
{
	return -1;	
}
	
XMLSSize_t CErrorLocator::getColumnNumber() const
{
	return -1;	
}
	
XMLSSize_t CErrorLocator::getOffset() const
{
	return -1;
}
	
const XMLCh* CErrorLocator::getURI() const
{
	return 0;
}
	
void CErrorLocator::setLineNumber(const XMLSSize_t)
{

}
	
void CErrorLocator::setColumnNumber(const XMLSSize_t)
{

}
	
void CErrorLocator::setOffset(const XMLSSize_t)
{

}
	
void CErrorLocator::setURI(const XMLCh* const)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

CError::CError(const std::string& mes) : mLocator()
{
	XMLStringUtil::Str2XML(mes,mMessage,512);
}
	
CError::~CError()
{

}
	 
const XMLCh* CError::getMessage() const
{
	return mMessage;
}
	
DOMLocator* CError::getLocation() const
{
	return &mLocator;
}
	 
short CError::getSeverity() const
{
	return -1;
}
	
void* CError::getRelatedException() const
{
	return 0;
}
	
const XMLCh* CError::getType() const
{
	return 0;
}
	
void* CError::getRelatedData() const
{
	return 0;
}
	
void CError::setSeverity(const short)
{

}
	
void CError::setRelatedException(void*) const
{

}
	
void CError::setType(const XMLCh*)
{

}
	
void CError::setRelatedData(void*)
{

}
	
void CError::setMessage(const XMLCh* const)
{

}
	
void CError::setLocation(XERCES_CPP_NAMESPACE::DOMLocator* const)
{

}

} //end namespace CORINET



