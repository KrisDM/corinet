/*********************************************************************************************
 * Name      :  DOMHandlerImpl.cpp
 *
 * Purpose   :  Implementation classes handling DOM.
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

#include <Setup/Makers.h>
#include <XMLUtil/XMLFileUtil.h>
#include <DOMSetup/Impl/DOMDefaultsImpl.h>
#include <DOMSetup/Impl/DOMCommonImpl.h>
#include <DOMSetup/Impl/DOMNetImpl.h>
#include <DOMSetup/Impl/DOMTaskImpl.h>
#include <DOMSetup/Impl/DOMEventImpl.h>
#include <DOMSetup/Impl/DOMExecutionImpl.h>
#include <DOMSetup/Misc/DOMHelperFunctions.h>
#include "DOMHandlerImpl.h"
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <fstream>

namespace CORINET {
	
CDOMEngineV1::CDOMEngineV1() : theEngineMaker(0),theStatusMaker(0)
{
	pDefaultsHandler = new CDOMDefaultsImpl();
	pCommonHandler = new CDOMCommonImpl();
	pNetHandler = new CDOMNetImpl();
	pTaskHandler = new CDOMTaskImpl();
	pEventHandler = new CDOMEventImpl();
	pExecutionHandler = new CDOMExecutionImpl();
	static_cast<CDOMNetImpl*>(pNetHandler)->SetDefaultsHandler(pDefaultsHandler);
	static_cast<CDOMNetImpl*>(pNetHandler)->SetCommonHandler(pCommonHandler);
	static_cast<CDOMTaskImpl*>(pTaskHandler)->SetDefaultsHandler(pDefaultsHandler);
	static_cast<CDOMTaskImpl*>(pTaskHandler)->SetCommonHandler(pCommonHandler);
	static_cast<CDOMEventImpl*>(pEventHandler)->SetCommonHandler(pCommonHandler);
	static_cast<CDOMEventImpl*>(pEventHandler)->SetNetHandler(pNetHandler);
	static_cast<CDOMEventImpl*>(pEventHandler)->SetTaskHandler(pTaskHandler);
	static_cast<CDOMEventImpl*>(pEventHandler)->SetExecutionHandler(pExecutionHandler);
	static_cast<CDOMExecutionImpl*>(pExecutionHandler)->SetCommonHandler(pCommonHandler);
	static_cast<CDOMExecutionImpl*>(pExecutionHandler)->SetNetHandler(pNetHandler);
	static_cast<CDOMExecutionImpl*>(pExecutionHandler)->SetTaskHandler(pTaskHandler);
	static_cast<CDOMExecutionImpl*>(pExecutionHandler)->SetEventHandler(pEventHandler);
}

CDOMEngineV1::~CDOMEngineV1()
{
	ReleaseAll();
	delete pExecutionHandler;
	delete pEventHandler;
	delete pTaskHandler;
	delete pNetHandler;
	delete pCommonHandler;
	delete pDefaultsHandler;
}

void CDOMEngineV1::Handle(DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create)
{
	pDefaultsHandler->Handle(setupDoc,valDoc,eHandler);
	pCommonHandler->Handle(setupDoc,valDoc,eHandler,create);
	pNetHandler->Handle(setupDoc,valDoc,eHandler,create);
	pTaskHandler->Handle(setupDoc,valDoc,eHandler,create);
	pExecutionHandler->Handle(setupDoc,valDoc,eHandler,create);
	pEventHandler->Handle(setupDoc,valDoc,eHandler,create);
	pExecutionHandler->AddEvents(setupDoc,valDoc,eHandler,create);
	if (create) {
		theEngineMaker = new SEngineMaker("engineV1");
		const DOMNodeList* pDOMexecutionList = GetElementList(setupDoc,XMLStrDefs::execution);
		for(XMLSize_t e1=0,es1=pDOMexecutionList->getLength();e1<es1;++e1) {
			const DOMElement* pDOMexecution = GetElement(pDOMexecutionList,e1);
			theEngineMaker->executionMakers.push_back(pExecutionHandler->GetExecutionMaker(pDOMexecution));
		}
		if (!pEventHandler->HasLocation("stdout")) {
			theStatusMaker = new SStatusMaker("engineV1");
			theStatusMaker->numExecutions = theEngineMaker->executionMakers.size();
			theEngineMaker->statusMaker = theStatusMaker;
		}
	}
}

SEngineMaker* CDOMEngineV1::GetEngineMaker()
{
	return theEngineMaker;
}

void CDOMEngineV1::ReleaseAll()
{
	pExecutionHandler->ReleaseAll();
	pCommonHandler->ReleaseAll();
	pNetHandler->ReleaseAll();
	pTaskHandler->ReleaseAll();
	pEventHandler->ReleaseAll();
	pExecutionHandler->ReleaseAll();
	delete theStatusMaker;
	theStatusMaker = 0;
	delete theEngineMaker;
	theEngineMaker = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

CDOMDummyHandler::CDOMDummyHandler() 
{

}
	
CDOMDummyHandler::~CDOMDummyHandler()
{

}

void CDOMDummyHandler::Handle(DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create)
{
	CErrorHandler::NonFatalMessage("Document <" + XMLStringUtil::XML2Str(setupDoc->getDocumentElement()->getTagName()) +
		"> conforms to schema file experimentSetup.xsd, but that is really all I can tell you at the moment. Sorry about that.",eHandler);
}

SEngineMaker* CDOMDummyHandler::GetEngineMaker()
{
	return 0;
}

void CDOMDummyHandler::ReleaseAll()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////

CDOMPatternSet::CDOMPatternSet() 
{

}
	
CDOMPatternSet::~CDOMPatternSet()
{

}

void CDOMPatternSet::Handle(DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create)
{
	const DOMElement* pDOMpatternSet = setupDoc->getDocumentElement();
	size_t numcols = XMLStringUtil::XML2Int(pDOMpatternSet->getAttribute(XMLStrDefs::columns));
	size_t numrows = XMLStringUtil::XML2Int(pDOMpatternSet->getAttribute(XMLStrDefs::rows));
	const DOMNodeList* pDOMpList = GetElementList(pDOMpatternSet,XMLStrDefs::p);
	for(XMLSize_t p1=0,ps1=pDOMpList->getLength();p1<ps1;++p1) {
		const DOMElement* pDOMp = GetElement(pDOMpList,p1);
		Get2DVals(pDOMp,numrows,numcols,XMLStrDefs::r,XMLStrDefs::c,pDOMpatternSet,eHandler,0);
	}
	CErrorHandler::NonFatalMessage("<patternSet> validated!",eHandler);
}

SEngineMaker* CDOMPatternSet::GetEngineMaker()
{
	return 0;
}

void CDOMPatternSet::ReleaseAll()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

CDOMPatternGenerator::CDOMPatternGenerator() : theEngineMaker(0),theExecutionMaker(0),theEventMaker(0),
											   theActionMaker(0),theReportMaker(0)
{
	pDefaultsHandler = new CDOMDefaultsImpl(); //it won't do anything but it is needed in pTaskHandler
	pCommonHandler = new CDOMCommonImpl();
	pTaskHandler = new CDOMTaskImpl();
	static_cast<CDOMTaskImpl*>(pTaskHandler)->SetDefaultsHandler(pDefaultsHandler);
	static_cast<CDOMTaskImpl*>(pTaskHandler)->SetCommonHandler(pCommonHandler);
}

CDOMPatternGenerator::~CDOMPatternGenerator()
{
	ReleaseAll();
	delete pTaskHandler; pTaskHandler = 0;
	delete pCommonHandler; pCommonHandler = 0;
	delete pDefaultsHandler; pDefaultsHandler = 0;
}

void CDOMPatternGenerator::Handle(DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create)
{
	//create or validate the task
	pCommonHandler->Handle(setupDoc,valDoc,eHandler,create);
	pTaskHandler->Handle(setupDoc,valDoc,eHandler,create);
	
	if (create) {
		//get the document element
		DOMElement* pDOMgenerator = setupDoc->getDocumentElement();
		const XMLCh* locXCh = pDOMgenerator->getAttribute(XMLStrDefs::location);
		size_t numpat = XMLStringUtil::XML2Int(pDOMgenerator->getAttribute(XMLStrDefs::patterns));
		std::string fullpathstr = XMLFileUtil::GetFullPath(locXCh);

		//get the task element
		const DOMElement* pDOMtask = GetElement(setupDoc,XMLStrDefs::compositeTask,0);
		if (!pDOMtask) {
			pDOMtask = GetElement(setupDoc,XMLStrDefs::task,0);
		}

		//make the reportmaker
		theReportMaker = new SReportMaker("patternSet",fullpathstr.c_str());
		XMLFormatTarget* pout = 0;
		try {
			pout = new LocalFileFormatTarget(fullpathstr.c_str());
		}
		catch(...) {
			CErrorHandler::PrepareError("Error opening <patternSet> target file",pDOMgenerator,eHandler);
		}
		XMLFileUtil::WriteToTarget("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",39,pout);
		theReportMaker->sink = pout;

		//make the actionmaker
		theActionMaker = new SActionMaker("recordTaskPatterns");
		theActionMaker->reportMaker = theReportMaker;
		theActionMaker->targets.push_back(pTaskHandler->GetMaker(pDOMtask));
		if (pDOMgenerator->hasAttribute(XMLStrDefs::precision)) {
			theActionMaker->precision = XMLStringUtil::XML2Int(pDOMgenerator->getAttribute(XMLStrDefs::precision));
		}

		//make the eventmaker
		theEventMaker = new SEventMaker("eventModelV1");
		theEventMaker->actionMakers.push_back(theActionMaker);
				
		//make the executionmaker
		theExecutionMaker = new SExecutionMaker("patternGenerator");
		theExecutionMaker->eventMakers.push_back(theEventMaker);
		theExecutionMaker->taskMakers.push_back(pTaskHandler->GetTaskMaker(pDOMtask));
		theExecutionMaker->numRuns = numpat;
		
		//make the enginemaker
		theEngineMaker = new SEngineMaker("engineV1");
		theEngineMaker->executionMakers.push_back(theExecutionMaker);
	}
}

SEngineMaker* CDOMPatternGenerator::GetEngineMaker()
{
	return theEngineMaker;
}

void CDOMPatternGenerator::ReleaseAll()
{
	pCommonHandler->ReleaseAll();
	pTaskHandler->ReleaseAll();
	if (theReportMaker) {
		XMLFormatTarget* pout = static_cast<XMLFormatTarget*>(theReportMaker->sink);
		delete pout;
		delete theReportMaker;
		theReportMaker = 0;
	}
	delete theActionMaker;
	theActionMaker = 0;
	delete theEventMaker;
	theEventMaker = 0;
	delete theExecutionMaker;
	theExecutionMaker = 0;
	delete theEngineMaker;
	theEngineMaker = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

CDOMRandTest::CDOMRandTest() : theEngineMaker(0),theExecutionMaker(0),theReportMaker(0)
{
	pCommonHandler = new CDOMCommonImpl();
}

CDOMRandTest::~CDOMRandTest()
{
	ReleaseAll();
	delete pCommonHandler; pCommonHandler = 0;
}

void CDOMRandTest::Handle(DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create)
{
	//create or validate the task
	pCommonHandler->Handle(setupDoc,valDoc,eHandler,create);
	
	if (create) {
		//get the document element
		DOMElement* pDOMrandTest = setupDoc->getDocumentElement();
		const XMLCh* locXCh = pDOMrandTest->getAttribute(XMLStrDefs::location);
		size_t numvals = XMLStringUtil::XML2Int(pDOMrandTest->getAttribute(XMLStrDefs::values));
		std::string fullpathstr = XMLFileUtil::GetFullPath(locXCh);

		//get the randgen element
		const DOMElement* pDOMrandGen = GetElement(setupDoc,XMLStrDefs::randGen,0);

		//make the reportmaker
		theReportMaker = new SReportMaker("txt",fullpathstr.c_str());
		std::ofstream* ofstr = new std::ofstream(fullpathstr.c_str());
		if (ofstr->fail()) {
			CErrorHandler::PrepareError("Error opening randTest results file",pDOMrandTest,eHandler);
		}
		theReportMaker->sink = ofstr;

		//make the executionmaker
		theExecutionMaker = new SExecutionMaker("randTest");
		theExecutionMaker->numRuns = numvals;
		theExecutionMaker->randMaker = pCommonHandler->GetRandMaker(pDOMrandGen);
		theExecutionMaker->reportMaker = theReportMaker;
		if (pDOMrandTest->hasAttribute(XMLStrDefs::precision)) {
			theExecutionMaker->precision = XMLStringUtil::XML2Int(pDOMrandTest->getAttribute(XMLStrDefs::precision));
		}
		
		//make the enginemaker
		theEngineMaker = new SEngineMaker("engineV1");
		theEngineMaker->executionMakers.push_back(theExecutionMaker);
	}
}

SEngineMaker* CDOMRandTest::GetEngineMaker()
{
	return theEngineMaker;
}

void CDOMRandTest::ReleaseAll()
{
	pCommonHandler->ReleaseAll();
	if (theReportMaker) {
		std::ostream* pout = static_cast<std::ostream*>(theReportMaker->sink);
		pout->flush();
		delete pout;
		delete theReportMaker;
		theReportMaker = 0;
	}
	delete theExecutionMaker;
	theExecutionMaker = 0;
	delete theEngineMaker;
	theEngineMaker = 0;
}

} //end namespace CORINET





