/*********************************************************************************************
 * Name      :  DOMRegister.cpp
 *
 * Purpose   :  Find a suitable CDOMSetupHandler.
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

#include <xercesc/dom/DOM.hpp>
#include <DOMSetup/DOMRegister.h>
#include <DOMSetup/Misc/DOMHelperFunctions.h>
#include "DOMHandlerImpl.h"
#include "DOMDefinitionImpl.h"
#include <XMLUtil/XMLStrDefs.h>
#include <XMLUtil/XMLSchemaDefs.h>
#include <XMLUtil/XMLStringUtil.h>

XERCES_CPP_NAMESPACE_USE

namespace CORINET {

CDOMRegister::~CDOMRegister()
{

}

CDOMHandler* CDOMRegister::CreateHandler(const DOMDocument* doc)
{
	CDOMHandler* theHandler = 0;
	const DOMElement* docElement = doc->getDocumentElement();
	const XMLCh* docTag = docElement->getTagName();
	if (XMLStringUtil::Equals(docTag,XMLStrDefs::experiment)) {
		const DOMElement* esEl = GetElement(docElement,XMLStrDefs::executionSection,0);
		if (esEl->hasAttributeNS(XMLSchemaNames::XSI,XMLStrDefs::type)) {
			std::string typeStr = XMLStringUtil::XML2Str(esEl->getAttributeNS(XMLSchemaNames::XSI,XMLStrDefs::type));
			if (typeStr == "engineV1") {
				theHandler = new CDOMEngineV1();
			}
		}
	}
	else if (XMLStringUtil::Equals(docTag,XMLStrDefs::typeDefaults) ||
		XMLStringUtil::Equals(docTag,XMLStrDefs::w)) {
		theHandler = new CDOMDummyHandler();
	}
	else if (XMLStringUtil::Equals(docTag,XMLStrDefs::patternSet)) {
		theHandler = new CDOMPatternSet();
	}
	else if (XMLStringUtil::Equals(docTag,XMLStrDefs::patternGenerator)) {
		theHandler = new CDOMPatternGenerator();
	}
	else if (XMLStringUtil::Equals(docTag,XMLStrDefs::randTest)) {
		theHandler = new CDOMRandTest();
	}
	else if (XMLStringUtil::Equals(docTag,XMLStrDefs::languageDefinition)) {
		theHandler = new CDOMDefinitionImpl();
	}
	return theHandler;
}

} //end namespace CORINET


