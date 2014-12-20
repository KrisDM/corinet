/*********************************************************************************************
 * Name      :  DOMEventImpl.h
 *
 * Purpose   :  Implementation class handling event handlers and child elements.
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

#ifndef CORINET_DOMEVENTIMPL
#define CORINET_DOMEVENTIMPL

#include <DOMSetup/DOMEvent.h>

namespace CORINET {
	struct SActionMaker;
	struct SConditionMaker;
	struct SOperationMaker;
	struct SReportMaker;
	class CDOMCommon;
	class CDOMNet;
	class CDOMTask;
	class CDOMExecution;

class CDOMEventImpl : public CDOMEvent {
	typedef std::map<std::string,const DOMElement*> LReportLocations;
	typedef std::map<const DOMElement*,SReportMaker*> LReportMakers;
	typedef std::map<const DOMElement*,SOperationMaker*> LOperationMakers;
	typedef std::map<const DOMElement*,SConditionMaker*> LConditionMakers;
	typedef std::map<const DOMElement*,SActionMaker*> LActionMakers;
	typedef std::map<const DOMElement*,SEventMaker*> LEventMakers;
	typedef std::map<const DOMElement*,std::vector<const DOMElement*> > LPart2Events;
	LReportLocations mReportLocations;
	LReportMakers mReportMakers;
	LOperationMakers mOperationMakers;
	LConditionMakers mConditionMakers;
	LActionMakers mActionMakers;
	LEventMakers mEventMakers;
	LPart2Events mPart2Events;
	CDOMCommon* pCommonHandler;
	CDOMNet* pNetHandler;
	CDOMTask* pTaskHandler;
	CDOMExecution* pExecutionHandler;

	void HandleReport(const XERCES_CPP_NAMESPACE::DOMElement* reportEl,const XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,
					  XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create);
public:
	CDOMEventImpl();
	virtual ~CDOMEventImpl();

	//initialise functions
	void SetCommonHandler(CDOMCommon*);
	void SetNetHandler(CDOMNet*);
	void SetTaskHandler(CDOMTask*);
	void SetExecutionHandler(CDOMExecution*);

	void Handle(const XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create);

	//access functions
	SEventMaker* GetEventMaker(const XERCES_CPP_NAMESPACE::DOMElement*);
	SMaker* GetMaker(const XERCES_CPP_NAMESPACE::DOMElement*);
	const std::vector<const XERCES_CPP_NAMESPACE::DOMElement*>* GetPartEvents(const XERCES_CPP_NAMESPACE::DOMElement*);
	bool HasLocation(const std::string&);

	//cleanup
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_DOMEVENTIMPL




