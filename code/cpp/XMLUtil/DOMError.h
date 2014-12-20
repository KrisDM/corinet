/*********************************************************************************************
 * Name      :  DOMError.h
 *
 * Purpose   :  Error handling classes, all comforming to xerces-c interface classes.
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

#ifndef CORINET_DOMERROR
#define CORINET_DOMERROR

#include <Platform/Platform.h>
#include <xercesc/dom/DOM.hpp>
#include <string>

namespace CORINET {

////////////////////////////////////////////////////////////////////////////////////////////////////
//the local implementation of the DOMLocator interface
////////////////////////////////////////////////////////////////////////////////////////////////////

class CErrorLocator : public XERCES_CPP_NAMESPACE::DOMLocator {
	XERCES_CPP_NAMESPACE::DOMNode* pErrorNode;
public:
	CErrorLocator();
	virtual ~CErrorLocator();
	 
	//implemented functions
	XERCES_CPP_NAMESPACE::DOMNode* getErrorNode() const; 
	void setErrorNode(XERCES_CPP_NAMESPACE::DOMNode* const);

	//unused functions
	XMLSSize_t getLineNumber() const; 
	XMLSSize_t getColumnNumber() const; 
	XMLSSize_t getOffset() const;
	const XMLCh* getURI() const;
	void setLineNumber(const XMLSSize_t); 
	void setColumnNumber(const XMLSSize_t);
	void setOffset(const XMLSSize_t);
	void setURI(const XMLCh* const);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//the local implementation of the DOMError interface
////////////////////////////////////////////////////////////////////////////////////////////////////

class CError : public XERCES_CPP_NAMESPACE::DOMError {
	mutable CErrorLocator mLocator;
	XMLCh mMessage[512]; 
public:
	CError(const std::string&);
	virtual ~CError();
	 
	//implemented functions
	const XMLCh* getMessage() const;
	XERCES_CPP_NAMESPACE::DOMLocator* getLocation() const;
	 
	//unused functions
	short getSeverity() const;
	void* getRelatedException() const;
	const XMLCh* getType() const;
	void* getRelatedData() const;
	void setSeverity(const short);
	void setRelatedException(void*) const;
	void setType(const XMLCh*);
	void setRelatedData(void*);
	void setMessage(const XMLCh* const);
	void setLocation(XERCES_CPP_NAMESPACE::DOMLocator* const);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//interface class, specific ErrorHandlers are derived from here
////////////////////////////////////////////////////////////////////////////////////////////////////

class CErrorHandler : public XERCES_CPP_NAMESPACE::DOMErrorHandler {
public:
	virtual ~CErrorHandler() {}
	virtual bool handleError(const XERCES_CPP_NAMESPACE::DOMError&) =0;
	virtual void handleMessage(const std::string& mes) =0;
	static void PrepareError(const std::string& mes,const XERCES_CPP_NAMESPACE::DOMElement* errorNode,
							 XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler) {
		CError thisError(mes);
		thisError.getLocation()->setErrorNode(const_cast<XERCES_CPP_NAMESPACE::DOMElement*>(errorNode));
		eHandler->handleError(thisError);
	}
	static void NonFatalMessage(const std::string& mes,XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler) {
		static_cast<CErrorHandler*>(eHandler)->handleMessage(mes);
	}
};

} //end namespace CORINET

#endif //CORINET_DOMERROR


