/*********************************************************************************************
 * Name      :  ClientImpl.cpp
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

#include "ClientImpl.h"
#include <Client/MessageHandler.h>
#include <Util/Util.h>
#include <XMLUtil/XMLSchemaDefs.h>
#include <XMLUtil/XMLStrDefs.h>
#include <XMLUtil/XMLRegister.h>
#include <XMLUtil/XMLStringUtil.h>
#include <XMLUtil/XMLFileUtil.h>
#include <XMLUtil/DOMMerge.h>
#include <DOMSetup/DOMRegister.h>
#include <Setup/BuilderRegister.h>
#include <Setup/Makers.h>
#include <Engine/Engine.h>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

CClientXML::CClientXML(CMessageHandler* pmes) : pMessageHandler(pmes),pParser(0),pErrorHandler(0),mDOMInputSources(),
												mDOMDocuments(),pSetupHandler(0),pDefHandler(0),pBuilder(0)
{
	try {
		XMLPlatformUtils::Initialize();
    }
    catch(const XMLException& eInit) {
		pMessageHandler->Handle("Error during initialization: " + XMLStringUtil::XML2Str(eInit.getMessage()),true);
        throw;
    }
}
	
CClientXML::~CClientXML()
{
	Release();
	XMLPlatformUtils::Terminate();
}

void CClientXML::Release()
{
	if (pBuilder) {
		delete pBuilder;
		pBuilder = 0;
	}
	if (pSetupHandler) {
		delete pSetupHandler;
		pSetupHandler = 0;
	}
	if (pDefHandler) {
		delete pDefHandler;
		pDefHandler = 0;
	}
	while(mDOMDocuments.size()) {
		DOMDocument* doc = mDOMDocuments.back();
		doc->release();
		mDOMDocuments.pop_back();
	}
	if (pErrorHandler) {
		delete pErrorHandler;
		pErrorHandler = 0;
	}
	if (pParser) {
		pParser->release();
		pParser = 0;
	}
	while(mDOMInputSources.size()) {
		DOMInputSource* inputSource = mDOMInputSources.back();
		inputSource->release();
		mDOMInputSources.pop_back();
	}
	if (pMessageHandler) {
		delete pMessageHandler;
		pMessageHandler = 0;
	}
}


	
void CClientXML::Handle(const std::string& fileName,bool create)
{
	////////////////////////////////////////////////////////////////////////////
	//Get file names and schema file names in right format
	////////////////////////////////////////////////////////////////////////////
	XMLCh XMLChFullFileName[512];
	XMLCh XMLChFullExp[512];
	XMLCh XMLChFullList[512];
	XMLCh XMLChFullDef[512];
	XMLCh XMLChFullGen[512];
	XMLCh XMLChSchemaList[2048];
	////////////////////////////////////////////////////////////////////////////
	XMLFileUtil::GetFullPath(XMLChFullFileName,fileName);
	XMLFileUtil::GetFullPath(XMLChFullExp,XMLSchemaLocations::CORINETSetup);
	XMLStringUtil::FixURI(XMLChFullExp);
	XMLFileUtil::GetFullPath(XMLChFullList,XMLSchemaLocations::CORINETSetupList);
	XMLStringUtil::FixURI(XMLChFullList);
	XMLFileUtil::GetFullPath(XMLChFullDef,XMLSchemaLocations::CORINETDefinition);
	XMLStringUtil::FixURI(XMLChFullDef);
	XMLFileUtil::GetFullPath(XMLChFullGen,XMLSchemaLocations::CORINETGenerator);
	XMLStringUtil::FixURI(XMLChFullGen);
	////////////////////////////////////////////////////////////////////
	XMLStringUtil::Copy(XMLChSchemaList,XMLSchemaNames::CORINETSetup);
	XMLStringUtil::AppendWSpace(XMLChSchemaList,XMLChFullExp);
	XMLStringUtil::AppendWSpace(XMLChSchemaList,XMLSchemaNames::CORINETSetupList);
	XMLStringUtil::AppendWSpace(XMLChSchemaList,XMLChFullList);
	XMLStringUtil::AppendWSpace(XMLChSchemaList,XMLSchemaNames::CORINETDefinition);
	XMLStringUtil::AppendWSpace(XMLChSchemaList,XMLChFullDef);
	XMLStringUtil::AppendWSpace(XMLChSchemaList,XMLSchemaNames::CORINETGenerator);
	XMLStringUtil::AppendWSpace(XMLChSchemaList,XMLChFullGen);
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//Get a DOMBuilder (parser)
	/////////////////////////////////////////////////////////////////////////////
	//get the implementation
	DOMImplementationLS* pDOMimpl = DOMImplementationRegistry::getDOMImplementation(XMLStrDefs::LS);
	/////////////////////////////////////////////////////////////////////////////
	//get the parser
	pParser = pDOMimpl->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS,0);
	/////////////////////////////////////////////////////////////////////////////
	//set all necessary parser features and properties
	pParser->setFeature(XMLUni::fgDOMComments,false);
	pParser->setFeature(XMLUni::fgDOMEntities,false);
	pParser->setFeature(XMLUni::fgDOMNamespaces,true);
	pParser->setFeature(XMLUni::fgDOMValidation,true);
	pParser->setFeature(XMLUni::fgDOMDatatypeNormalization,true);
	pParser->setFeature(XMLUni::fgDOMWhitespaceInElementContent,false);
	pParser->setFeature(XMLUni::fgXercesSchema,true);
	pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal,true);
	pParser->setFeature(XMLUni::fgXercesIdentityConstraintChecking,true);
	pParser->setFeature(XMLUni::fgXercesUserAdoptsDOMDocument,true);
	pParser->setProperty(XMLUni::fgXercesSchemaExternalSchemaLocation,XMLChSchemaList);	
	/////////////////////////////////////////////////////////////////////////////
	//set error handling for application environment
	pErrorHandler = CXMLRegister::CreateErrorHandler(pMessageHandler);
	pParser->setErrorHandler(pErrorHandler);
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//Get a DOMInputSource from the file with fileName
	/////////////////////////////////////////////////////////////////////////////
	DOMInputSource* pInputSource = GetInputSource(XMLChFullFileName);
	if (!pInputSource) {
		throw SClientException();
	}
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//Parse the primary file
	/////////////////////////////////////////////////////////////////////////////
	DOMDocument* pPrimaryDocument = GetDocument(pInputSource);
	if (!pPrimaryDocument) {
		throw SClientException();
	}
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//Get the namespace
	/////////////////////////////////////////////////////////////////////////////
	const XMLCh* XMLChnamespace = GetNameSpace(pPrimaryDocument);
	if (!XMLChnamespace) {
		throw SClientException();
	}
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//Call a specific function per namespace
	/////////////////////////////////////////////////////////////////////////////
	if (XMLStringUtil::Equals(XMLChnamespace,XMLSchemaNames::CORINETSetup))
		HandleNSSetup(pPrimaryDocument,create);	
	else if (XMLStringUtil::Equals(XMLChnamespace,XMLSchemaNames::CORINETSetupList))
		HandleNSList(pPrimaryDocument,create);
	else if (XMLStringUtil::Equals(XMLChnamespace,XMLSchemaNames::CORINETDefinition))
		HandleNSDefinition(pPrimaryDocument,create);
	else if (XMLStringUtil::Equals(XMLChnamespace,XMLSchemaNames::CORINETGenerator))
		HandleNSGenerator(pPrimaryDocument,create);
	else {
		pMessageHandler->Handle("Unknown target namespace " + XMLStringUtil::XML2Str(XMLChnamespace),true);
		pMessageHandler->Handle("Error occurred in: " + XMLStringUtil::XML2Str(XMLChFullFileName),true);
		throw SClientException();
	}
}

void CClientXML::HandleNSSetup(DOMDocument* setupDoc,bool create)
{
	DOMElement* rootEl = setupDoc->getDocumentElement();
	DOMDocument* pValidationDocument = 0;
	if (rootEl->hasAttribute(XMLStrDefs::definitionFile)) {
		//get the main language definition file
		const XMLCh* defFile = rootEl->getAttribute(XMLStrDefs::definitionFile);
		DOMInputSource* pValSource = GetInputSource(defFile);
		if (!pValSource) {
			throw SClientException();
		}
		
		//parse the main language definition file
		pValidationDocument = GetDocument(pValSource);
		if (!pValidationDocument) {
			throw SClientException();
		}
		
		//get the namespace
		const XMLCh* XMLChnamespace = GetNameSpace(pValidationDocument);
		if (!XMLChnamespace) {
			throw SClientException();
		}

		//first handle this file in its own right
		if (XMLStringUtil::Equals(XMLChnamespace,XMLSchemaNames::CORINETDefinition))
			HandleNSDefinition(pValidationDocument,false);
		else {
			pMessageHandler->Handle("Unknown target namespace " + XMLStringUtil::XML2Str(XMLChnamespace),true);
			pMessageHandler->Handle("Error occurred in: " + XMLStringUtil::XML2Str(defFile),true);
			throw SClientException();
		}

		//parse the additional sandbox files
		if (rootEl->hasAttribute(XMLStrDefs::sandBoxFiles)) {
			std::vector<XMLCh*> sandBoxFiles = XMLStringUtil::Tokenise(rootEl->getAttribute(XMLStrDefs::sandBoxFiles));
			for(size_t s1=0,ss1=sandBoxFiles.size();s1<ss1;++s1) {
				//get the sandbox file
				DOMInputSource* pSandBoxSource = GetInputSource(sandBoxFiles[s1]);
				if (!pSandBoxSource) {
					XMLStringUtil::Release(sandBoxFiles);
					throw SClientException();
				}

				//parse the sandbox file
				DOMDocument* pSandBoxDocument = GetDocument(pSandBoxSource);
				if (!pSandBoxDocument) {
					XMLStringUtil::Release(sandBoxFiles);
					throw SClientException();
				}

				//get the namespace
				const XMLCh* XMLChnamespaceSand = GetNameSpace(pSandBoxDocument);
				if (!XMLChnamespaceSand) {
					XMLStringUtil::Release(sandBoxFiles);
					throw SClientException();
				}

				//first handle this file in its own right
				if (XMLStringUtil::Equals(XMLChnamespaceSand,XMLSchemaNames::CORINETDefinition))
					HandleNSDefinition(pSandBoxDocument,false);
				else {
					pMessageHandler->Handle("Unknown target namespace " + XMLStringUtil::XML2Str(XMLChnamespaceSand),true);
					pMessageHandler->Handle("Error occurred in: " + XMLStringUtil::XML2Str(sandBoxFiles[s1]),true);
					XMLStringUtil::Release(sandBoxFiles);
					throw SClientException();
				}

				//merge this file with the main validation file
				CDOMMerge::Merge(pValidationDocument,pSandBoxDocument,pErrorHandler);
				ReleaseDocument(pSandBoxDocument);
				ReleaseInputSource(pSandBoxSource);
			}
			XMLStringUtil::Release(sandBoxFiles);
		}
	}

	//now get a handler for this setup file
	try {
		pSetupHandler = CDOMRegister::CreateHandler(setupDoc);
		if (pSetupHandler) {
			pSetupHandler->Handle(setupDoc,pValidationDocument,pErrorHandler,create);
		}
		else {
			pMessageHandler->Handle("Cannot handle document <" + XMLStringUtil::XML2Str(rootEl->getTagName()) + ">.",true);
			throw SClientException();
		}
	}
	catch (...) {
		pMessageHandler->Handle("Error during handling of document <" + XMLStringUtil::XML2Str(rootEl->getTagName()) + ">.",true);
		throw SClientException();
	}

	//now see if we have an engineMaker and need to do something more
	if (create) {
		SEngineMaker* engineMaker = pSetupHandler->GetEngineMaker();
		CEngine* theEngine = 0;
		if (engineMaker) {
			try {
				//see if we can get a suitable builder
				pBuilder = CBuilderRegister::GetBuilder(engineMaker);
				if (pBuilder) {
					theEngine = pBuilder->CreateEngine(pMessageHandler);
				}
				else {
					pMessageHandler->Handle("Unknown type of engine \"" + engineMaker->type + "\".",true);
					throw SClientException();
				}
			}
			catch (...) {
				pMessageHandler->Handle("Error during experiment setup.",true);
				throw SClientException();
			}
			if (theEngine) {
				pMessageHandler->Handle("Performing experiment...");
				theEngine->Execute(pBuilder);
				pMessageHandler->Handle("...done!");
			}
		}
	}
	if (pBuilder) {
		delete pBuilder;
		pBuilder = 0;
	}
	if (pSetupHandler) {
		delete pSetupHandler;
		pSetupHandler = 0;
	}
}

void CClientXML::HandleNSList(DOMDocument* listDoc,bool create)
{
	const XMLCh* rootTagXCh = listDoc->getDocumentElement()->getTagName();
	if (XMLStringUtil::Equals(rootTagXCh,XMLStrDefs::experimentList)) {
		DOMNodeList* pDOMFileList = listDoc->getElementsByTagName(XMLStrDefs::file);
		for(XMLSize_t i1=0,is1=pDOMFileList->getLength();i1<is1;++i1) {
			const DOMElement* pDOMFile = static_cast<DOMElement*>(pDOMFileList->item(i1));
			const XMLCh* fileName = pDOMFile->getAttribute(XMLStrDefs::location);
			//get the file
			DOMInputSource* pFileSource = GetInputSource(fileName);
			if (!pFileSource)
				throw SClientException();
		
			//parse the file
			DOMDocument* pFileDoc = GetDocument(pFileSource);
			if (!pFileDoc)
				throw SClientException();
			
			//get the namespace
			const XMLCh* XMLChnamespace = GetNameSpace(pFileDoc);
			if (!XMLChnamespace)
				throw SClientException();
	
			//call the right function for this file
			if (XMLStringUtil::Equals(XMLChnamespace,XMLSchemaNames::CORINETSetup))
				HandleNSSetup(pFileDoc,create);	
			else if (XMLStringUtil::Equals(XMLChnamespace,XMLSchemaNames::CORINETDefinition))
				HandleNSDefinition(pFileDoc,create);
			else if (XMLStringUtil::Equals(XMLChnamespace,XMLSchemaNames::CORINETSetupList)) {
				pMessageHandler->Handle("File with target namespace " + XMLStringUtil::XML2Str(XMLChnamespace) + " not allowed in <experimentList>",true);
				throw SClientException();
			}
			else {
				pMessageHandler->Handle("Unknown target namespace " + XMLStringUtil::XML2Str(XMLChnamespace),true);
				pMessageHandler->Handle("Error occurred in: " + XMLStringUtil::XML2Str(fileName),true);
				throw SClientException();
			}
			ReleaseDocument(pFileDoc);
			ReleaseInputSource(pFileSource);
		}
	}
	else {
		pMessageHandler->Handle("Unknown root element " + XMLStringUtil::XML2Str(rootTagXCh) + " in list file.",true);
		throw SClientException();
	}
}

void CClientXML::HandleNSDefinition(DOMDocument* defDoc,bool create)
{
	
	DOMDocument* pCodeDocument = 0;
	if (create) {
		if (defDoc->getDocumentElement()->hasAttribute(XMLStrDefs::codeFile)) {
			const XMLCh* codeFile = defDoc->getDocumentElement()->getAttribute(XMLStrDefs::codeFile);
			DOMInputSource* pCodeSource = GetInputSource(codeFile);
			if (!pCodeSource)
				throw SClientException();

			pCodeDocument = GetDocument(pCodeSource);
			if (!pCodeDocument)
				throw SClientException();

			//get the namespace
			const XMLCh* XMLChnamespace = GetNameSpace(pCodeDocument);
			if (!XMLChnamespace) {
				throw SClientException();
			}

			//first handle this file in its own right
			if (!XMLStringUtil::Equals(XMLChnamespace,XMLSchemaNames::CORINETGenerator)) {
				pMessageHandler->Handle("Unknown target namespace " + XMLStringUtil::XML2Str(XMLChnamespace),true);
				pMessageHandler->Handle("Error occurred in: " + XMLStringUtil::XML2Str(codeFile),true);
				throw SClientException();
			}
		}
		else {
			pMessageHandler->Handle("Attribute \"codeFile\" not specified. If you do not want to generate code, run with -v flag",true);
			throw SClientException();
		}
	}

	//get a handler for this definition file
	try {
		pDefHandler = CDOMRegister::CreateHandler(defDoc);
		if (pDefHandler) {
			if (create) 
				pMessageHandler->Handle("Generating C++ code...");
			pDefHandler->Handle(defDoc,pCodeDocument,pErrorHandler,create);
			if (create)
				pMessageHandler->Handle("...done.");
		}
		else {
			pMessageHandler->Handle("Cannot handle document <" + XMLStringUtil::XML2Str(defDoc->getDocumentElement()->getTagName()) + ">.",true);
			throw SClientException();
		}
	}
	catch (...) {
		pMessageHandler->Handle("Error during handling of document <" + XMLStringUtil::XML2Str(defDoc->getDocumentElement()->getTagName()) + ">.",true);
		throw SClientException();
	}

	if (pDefHandler) {
		delete pDefHandler;
		pDefHandler = 0;
	}
}

void CClientXML::HandleNSGenerator(DOMDocument* codeDoc,bool create)
{
	const XMLCh* tagName = codeDoc->getDocumentElement()->getTagName();
	if (XMLStringUtil::Equals(XMLStrDefs::codeGenerator,tagName)) {
		pMessageHandler->Handle("<codeGenerator> file validated.");
	}
	else if (XMLStringUtil::Equals(XMLStrDefs::hFile,tagName)) {
		pMessageHandler->Handle("<codeGenerator> fragment <hFile> validated.");
	}
	else if (XMLStringUtil::Equals(XMLStrDefs::cppFile,tagName)) {
		pMessageHandler->Handle("<codeGenerator> fragment <cppFile> validated.");
	}
	else {
		pMessageHandler->Handle("Cannot handle document <" + XMLStringUtil::XML2Str(tagName) + ">.",true);
		throw SClientException();
	}
}

void CClientXML::JanitorDocument(DOMDocument* doc)
{
	mDOMDocuments.push_back(doc);
}

void CClientXML::ReleaseDocument(DOMDocument* doc)
{
	mDOMDocuments.remove(doc);
	doc->release();
}

void CClientXML::JanitorInputSource(DOMInputSource* src)
{
	mDOMInputSources.push_back(src);
}

void CClientXML::ReleaseInputSource(DOMInputSource* src)
{
	mDOMInputSources.remove(src);
	src->release();
}

DOMInputSource* CClientXML::GetInputSource(const XMLCh* const fileName)
{
	XMLCh fileNameFull[512];
	XMLFileUtil::GetFullPath(fileNameFull,fileName);
	DOMInputSource* pInputSource = 0;
	try {
		pInputSource = new Wrapper4InputSource(new LocalFileInputSource(fileNameFull));
		pInputSource->setIssueFatalErrorIfNotFound(true);
		JanitorInputSource(pInputSource);
	}
	catch (XMLException& eFnF) {
		pMessageHandler->Handle("Error during opening of file " + XMLStringUtil::XML2Str(fileNameFull),true);
		pMessageHandler->Handle(XMLStringUtil::XML2Str(eFnF.getMessage()),true);
		return 0;
	}
	return pInputSource;
}

DOMDocument* CClientXML::GetDocument(const DOMInputSource* const inputSource)
{
	DOMDocument* pDocument = 0;
	try {
		pDocument = pParser->parse(*inputSource);
		JanitorDocument(pDocument);
	}
	catch(const XMLException& eXML2) {
		pMessageHandler->Handle("Error during parsing of input file: " + XMLStringUtil::XML2Str(eXML2.getMessage()),true);
    }
	catch(const DOMException& eDOM2) {
		pMessageHandler->Handle("Error during parsing of input file: " + XMLStringUtil::XML2Str(eDOM2.getMessage()),true);
    }
	catch(...) {
		pMessageHandler->Handle("Unknown error during parsing of file",true);
	}
	return pDocument;
}

const XMLCh* CClientXML::GetNameSpace(const DOMDocument* const doc)
{
	const XMLCh* XMLChnamespace = 0;
	if (doc->getDocumentElement()->hasAttribute(XMLSchemaNames::xmlns))
		XMLChnamespace = doc->getDocumentElement()->getAttribute(XMLSchemaNames::xmlns);
	else {
		pMessageHandler->Handle("Specify target namespace in \"xmlns\" attribute of root element.",true);
	}
	return XMLChnamespace;
}

} //end namespace CORINET


