/*********************************************************************************************
 * Name      :  DOMDefinitionImpl.h
 *
 * Purpose   :  Implementation classes handling <languageDefinition> DOM.
 *
 * Notes	 :	
 *
 * Info     :	http://www.corinet.org
 *
 * Copyright:	2006, King's College London
 *		
 * License  :   This program is free software; you can redistribute it and/or modify
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

#ifndef CORINET_DOMDEFINITIONIMPL
#define CORINET_DOMDEFINITIONIMPL

#include <DOMSetup/DOMHandler.h>
#include <xercesc/dom/DOM.hpp>
#include <ostream>

namespace CORINET {

class CDOMDefinitionImpl : public CDOMHandler {
	void CheckParamNames(const XERCES_CPP_NAMESPACE::DOMDocument*,const XMLCh*,XERCES_CPP_NAMESPACE::DOMErrorHandler*);
	void HandleType(const XERCES_CPP_NAMESPACE::DOMDocument*,const XERCES_CPP_NAMESPACE::DOMDocument*,
		XERCES_CPP_NAMESPACE::DOMErrorHandler*,const XMLCh*,const std::string&);
	void WriteIntro(std::ostream&,const XERCES_CPP_NAMESPACE::DOMDocument*,const std::string&);
public:
	CDOMDefinitionImpl();
	virtual ~CDOMDefinitionImpl();

	void Handle(XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create);

	//access functions
	SEngineMaker* GetEngineMaker();

	//cleanup
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_DOMDEFINITIONIMPL




