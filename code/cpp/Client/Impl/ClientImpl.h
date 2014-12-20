/*********************************************************************************************
 * Name      :  ClientImpl.h
 *
 * Purpose   :  Implementation classes for client applications.
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

#ifndef CORINET_CLIENTIMPL
#define CORINET_CLIENTIMPL

#include <Client/Client.h>
#include <DOMSetup/DOMHandler.h>
#include <Setup/Builder.h>
#include <xercesc/dom/DOM.hpp>
#include <list>

namespace CORINET {

struct SClientException {};
	
class CClientXML : public CClient {
	CMessageHandler* pMessageHandler;
	XERCES_CPP_NAMESPACE::DOMBuilder* pParser;
	XERCES_CPP_NAMESPACE::DOMErrorHandler* pErrorHandler;
	std::list<XERCES_CPP_NAMESPACE::DOMInputSource*> mDOMInputSources;
	std::list<XERCES_CPP_NAMESPACE::DOMDocument*> mDOMDocuments;
	CDOMHandler* pSetupHandler;
	CDOMHandler* pDefHandler;
	CBuilder* pBuilder;
	void JanitorInputSource(XERCES_CPP_NAMESPACE::DOMInputSource*);
	void ReleaseInputSource(XERCES_CPP_NAMESPACE::DOMInputSource*);
	void JanitorDocument(XERCES_CPP_NAMESPACE::DOMDocument*);
	void ReleaseDocument(XERCES_CPP_NAMESPACE::DOMDocument*);
	XERCES_CPP_NAMESPACE::DOMInputSource* GetInputSource(const XMLCh* const);
	XERCES_CPP_NAMESPACE::DOMDocument* GetDocument(const XERCES_CPP_NAMESPACE::DOMInputSource* const);
	const XMLCh* GetNameSpace(const XERCES_CPP_NAMESPACE::DOMDocument* const);
	void HandleNSSetup(XERCES_CPP_NAMESPACE::DOMDocument*,bool);
	void HandleNSList(XERCES_CPP_NAMESPACE::DOMDocument*,bool);
	void HandleNSDefinition(XERCES_CPP_NAMESPACE::DOMDocument*,bool);
	void HandleNSGenerator(XERCES_CPP_NAMESPACE::DOMDocument*,bool);
public:
	CClientXML(CMessageHandler*);
	virtual ~CClientXML();
	void Handle(const std::string& fileName,bool create);
	void Release();
};

} //end namespace CORINET

#endif //CORINET_CLIENTIMPL

