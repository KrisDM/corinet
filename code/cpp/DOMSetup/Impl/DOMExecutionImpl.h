/*********************************************************************************************
 * Name      :  DOMExecutionImpl.h
 *
 * Purpose   :  Implementation class handling execution makers and child elements.
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

#ifndef CORINET_DOMEXECUTIONIMPL
#define CORINET_DOMEXECUTIONIMPL

#include <DOMSetup/DOMExecution.h>
#include <map>
#include <valarray>

namespace CORINET {
	struct SLoopElementMaker;
	struct SLoopMaker;
	struct SLoopsMaker;
	struct SExecutionElementMaker;
	struct SMaker;
	class CDOMCommon;
	class CDOMNet;
	class CDOMTask;
	class CDOMEvent;

class CDOMExecutionImpl : public CDOMExecution {
	typedef std::map<const std::string,std::pair<bool,bool> > LPartParams;
	typedef std::map<const DOMElement*,std::vector<const DOMElement*> > LEx2Net;
	typedef std::map<const DOMElement*,std::vector<const DOMElement*> > LEx2Task;
	typedef std::map<const DOMElement*,std::valarray<double>*> LLoopValues;
	typedef std::map<const DOMElement*,SLoopElementMaker*> LLoopElMakers;
	typedef std::map<const DOMElement*,SLoopMaker*> LLoopMakers;
	typedef std::map<const DOMElement*,SLoopsMaker*> LLoopsMakers;
	typedef std::map<const DOMElement*,SExecutionElementMaker*> LExElMakers;
	typedef std::map<const DOMElement*,SExecutionMaker*> LExecutionMakers;
	LPartParams mPartParams;
	LEx2Net mEx2Net;
	LEx2Task mEx2Task;
	LLoopValues mLoopValues;
	LLoopElMakers mLoopElMakers;
	LLoopMakers mLoopMakers;
	LLoopsMakers mLoopsMakers;
	LExElMakers mExElMakers;
	LExecutionMakers mExecutionMakers;
	CDOMCommon* pCommonHandler;
	CDOMNet* pNetHandler;
	CDOMTask* pTaskHandler;
	CDOMEvent* pEventHandler;

	bool CheckLoopTarget(const XERCES_CPP_NAMESPACE::DOMElement* parentEl,const XERCES_CPP_NAMESPACE::DOMElement* executionEl);
	void HandleLoopParam(const XERCES_CPP_NAMESPACE::DOMElement* targetEl,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		SLoopElementMaker* loopElMaker,size_t index,const XMLCh* paramName);
public:
	CDOMExecutionImpl();
	virtual ~CDOMExecutionImpl();

	//initialise functions
	void SetCommonHandler(CDOMCommon*);
	void SetNetHandler(CDOMNet*);
	void SetTaskHandler(CDOMTask*);
	void SetEventHandler(CDOMEvent*);

	void Handle(const XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create);
	void AddEvents(const XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create);

	//access functions
	SExecutionMaker* GetExecutionMaker(const XERCES_CPP_NAMESPACE::DOMElement*);
	SMaker* GetMaker(const XERCES_CPP_NAMESPACE::DOMElement*);

	//cleanup
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_DOMEXECUTIONIMPL




