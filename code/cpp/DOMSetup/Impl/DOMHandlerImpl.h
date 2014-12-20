/*********************************************************************************************
 * Name      :  DOMHandlerImpl.h
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

#ifndef CORINET_DOMHANDLERIMPL
#define CORINET_DOMHANDLERIMPL

#include <DOMSetup/DOMHandler.h>
#include <xercesc/dom/DOM.hpp>

namespace CORINET {
	class CDOMDefaults;
	class CDOMCommon;
	class CDOMNet;
	class CDOMTask;
	class CDOMEvent;
	class CDOMExecution;
	class CDOMExperiment;
	struct SStatusMaker;
	struct SReportMaker;
	struct SActionMaker;
	struct SEventMaker;
	struct SExecutionMaker;

class CDOMEngineV1 : public CDOMHandler {
	SEngineMaker* theEngineMaker;
	SStatusMaker* theStatusMaker;
	CDOMDefaults* pDefaultsHandler;
	CDOMCommon* pCommonHandler;
	CDOMNet* pNetHandler;
	CDOMTask* pTaskHandler;
	CDOMEvent* pEventHandler;
	CDOMExecution* pExecutionHandler;
public:
	CDOMEngineV1();
	virtual ~CDOMEngineV1();

	void Handle(XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create);

	//access functions
	SEngineMaker* GetEngineMaker();

	//cleanup
	void ReleaseAll();
};

class CDOMDummyHandler : public CDOMHandler {
public:
	CDOMDummyHandler();
	virtual ~CDOMDummyHandler();

	void Handle(XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create);

	//access functions
	SEngineMaker* GetEngineMaker();

	//cleanup
	void ReleaseAll();
};

class CDOMPatternSet : public CDOMHandler {
public:
	CDOMPatternSet();
	virtual ~CDOMPatternSet();

	void Handle(XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create);

	//access functions
	SEngineMaker* GetEngineMaker();

	//cleanup
	void ReleaseAll();
};

class CDOMPatternGenerator : public CDOMHandler {
	SEngineMaker* theEngineMaker;
	SExecutionMaker* theExecutionMaker;
	SEventMaker* theEventMaker;
	SActionMaker* theActionMaker;
	SReportMaker* theReportMaker;
	CDOMDefaults* pDefaultsHandler;
	CDOMCommon* pCommonHandler;
	CDOMTask* pTaskHandler;
public:
	CDOMPatternGenerator();
	virtual ~CDOMPatternGenerator();

	void Handle(XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create);

	//access functions
	SEngineMaker* GetEngineMaker();

	//cleanup
	void ReleaseAll();
};

class CDOMRandTest : public CDOMHandler {
	SEngineMaker* theEngineMaker;
	SExecutionMaker* theExecutionMaker;
	SReportMaker* theReportMaker;
	CDOMCommon* pCommonHandler;
public:
	CDOMRandTest();
	virtual ~CDOMRandTest();

	void Handle(XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create);

	//access functions
	SEngineMaker* GetEngineMaker();

	//cleanup
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_DOMHANDLERIMPL




