/*********************************************************************************************
 * Name      :  DOMExecutionImpl.cpp
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

#include <Setup/Makers.h>
#include <DOMSetup/DOMCommon.h>
#include <DOMSetup/DOMNet.h>
#include <DOMSetup/DOMTask.h>
#include <DOMSetup/DOMEvent.h>
#include <DOMSetup/Misc/DOMHelperFunctions.h>
#include "DOMExecutionImpl.h"
#include <vector>
#include <list>
#include <algorithm>

namespace CORINET {

CDOMExecutionImpl::CDOMExecutionImpl() : mPartParams(),mEx2Net(),mEx2Task(),
										 mLoopValues(),mLoopElMakers(),mLoopMakers(),mLoopsMakers(),
										 mExElMakers(),mExecutionMakers(),
										 pCommonHandler(0),pNetHandler(0),pTaskHandler(0),pEventHandler(0)
{

}
	
CDOMExecutionImpl::~CDOMExecutionImpl()
{
	ReleaseAll();
}

void CDOMExecutionImpl::SetCommonHandler(CDOMCommon* ph)
{
	pCommonHandler = ph;
}
	
void CDOMExecutionImpl::SetNetHandler(CDOMNet* ph)
{
	pNetHandler = ph;
}
	
void CDOMExecutionImpl::SetTaskHandler(CDOMTask* ph)
{
	pTaskHandler = ph;
}
	
void CDOMExecutionImpl::SetEventHandler(CDOMEvent* ph)
{
	pEventHandler = ph;
}

bool CDOMExecutionImpl::CheckLoopTarget(const DOMElement* parentEl,const DOMElement* executionEl)
{
	bool belongs = false;
	const XMLCh* tagName = parentEl->getTagName();
	if (XMLStringUtil::Equals(tagName,XMLStrDefs::execution)) {
		if (parentEl == executionEl) {
			belongs = true;
		}
	}
	else if (XMLStringUtil::Equals(tagName,XMLStrDefs::network)) {
		std::vector<const DOMElement*>& exNets = mEx2Net[executionEl];
		if (std::find(exNets.begin(),exNets.end(),parentEl) != exNets.end()) {
			belongs = true;
		}
	}
	else if (XMLStringUtil::Equals(tagName,XMLStrDefs::task) || XMLStringUtil::Equals(tagName,XMLStrDefs::compositeTask)) {
		std::vector<const DOMElement*>& exTasks = mEx2Task[executionEl];
		if (std::find(exTasks.begin(),exTasks.end(),parentEl) != exTasks.end()) {
			belongs = true;
		}
	}
	return belongs;	
}

void CDOMExecutionImpl::HandleLoopParam(const DOMElement* targetEl,const DOMDocument* valDoc,
										SLoopElementMaker* loopElMaker,size_t index,const XMLCh* paramName)
{
	const DOMElement* pDOMvalTarget;
	if (XMLStringUtil::Equals(targetEl->getTagName(),XMLStrDefs::part)) {
		pDOMvalTarget = GetElement(valDoc,XMLStrDefs::part,0);
	}
	else {
		pDOMvalTarget = valDoc->getElementById(targetEl->getAttribute(XMLStrDefs::type));
	}
	loopElMaker->paramNums->operator[](index) = GetParamNum(paramName,pDOMvalTarget);
	SMaker* targetMaker = pCommonHandler->GetMaker(targetEl);
	if (!targetMaker)
		targetMaker = pNetHandler->GetMaker(targetEl);
	if (!targetMaker)
		targetMaker = pTaskHandler->GetMaker(targetEl);
	if (!targetMaker)
		targetMaker = this->GetMaker(targetEl);
	loopElMaker->targets.push_back(targetMaker);
}

void CDOMExecutionImpl::Handle(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create)
{
	//get the "required" status of the two part parameters for all <part> definitions in valDoc
	const DOMNodeList* pDOMvalPartList = GetElementList(valDoc,XMLStrDefs::part);
	for(XMLSize_t vp1=0,vps1=pDOMvalPartList->getLength();vp1<vps1;++vp1) {
		const DOMElement* pDOMvalPart = GetElement(pDOMvalPartList,vp1);
		std::string typestr = XMLStringUtil::XML2Str(pDOMvalPart->getAttribute(XMLStrDefs::type));
		const DOMElement* pDOMtimePerPattern = GetElement(pDOMvalPart,XMLStrDefs::param,0);
		const DOMElement* pDOMzeroTime = GetElement(pDOMvalPart,XMLStrDefs::param,1);
		mPartParams.insert(LPartParams::value_type(typestr,std::make_pair<bool,bool>(false,false)));
		if (XMLStringUtil::Equals(pDOMtimePerPattern->getAttribute(XMLStrDefs::use),XMLStrDefs::required)) {
			mPartParams[typestr].first = true;
		}
		if (XMLStringUtil::Equals(pDOMzeroTime->getAttribute(XMLStrDefs::use),XMLStrDefs::required)) {
			mPartParams[typestr].second = true;
		}
	}

	//get all networks and tasks belonging to a certain execution and check as much as possible
	const DOMNodeList* pDOMexecutionList = GetElementList(setupDoc,XMLStrDefs::execution);
	for(XMLSize_t e1=0,es1=pDOMexecutionList->getLength();e1<es1;++e1) {
		std::list<const DOMElement*> allTasks;
		const DOMElement* pDOMexecution = GetElement(pDOMexecutionList,e1);
		CheckDupl(pDOMexecution,setupDoc,eHandler,XMLStrDefs::networks);
		CheckIDREFS(pDOMexecution,setupDoc,eHandler,XMLStrDefs::networks,XMLStrDefs::network);
		std::vector<XMLCh*> networks = XMLStringUtil::Tokenise(pDOMexecution->getAttribute(XMLStrDefs::networks));
		XMLJanitor jan(networks);
		size_t minInputSize = std::numeric_limits<size_t>::max();
		bool timePerPattern = false;
		bool zeroTime = false;
		for(size_t n1=0,ns1=networks.size();n1<ns1;++n1) {
			const DOMElement* pDOMnetwork = setupDoc->getElementById(networks[n1]);
			mEx2Net[pDOMexecution].push_back(pDOMnetwork);
			size_t inputSize = XMLStringUtil::XML2Int(pDOMnetwork->getAttribute(XMLStrDefs::inputs)); 
			if (inputSize < minInputSize) {
				minInputSize = inputSize;
			}
			std::string typestr = XMLStringUtil::XML2Str(pDOMnetwork->getAttribute(XMLStrDefs::type));
			timePerPattern |= mPartParams[typestr].first;
			zeroTime |= mPartParams[typestr].second;
		}
		//check parts within this execution
		const DOMNodeList* pDOMpartList = GetElementList(pDOMexecution,XMLStrDefs::part);
		for(XMLSize_t p1=0,ps1=pDOMpartList->getLength();p1<ps1;++p1) {
			const DOMElement* pDOMpart = GetElement(pDOMpartList,p1);
			CheckIDREFS(pDOMpart,setupDoc,eHandler,XMLStrDefs::tasks,XMLStrDefs::task,XMLStrDefs::compositeTask);
			std::vector<XMLCh*> tasks = XMLStringUtil::Tokenise(pDOMpart->getAttribute(XMLStrDefs::tasks));
			XMLJanitor jan2(tasks);
			size_t partTaskSize = 0;
			for(size_t t1=0,ts1=tasks.size();t1<ts1;++t1) {
				const DOMElement* pDOMtask = setupDoc->getElementById(tasks[t1]);
				if (XMLStringUtil::Equals(pDOMtask->getTagName(),XMLStrDefs::task)) {
					if (XMLStringUtil::Equals(static_cast<DOMElement*>(pDOMtask->getParentNode())->getTagName(),XMLStrDefs::insert)) {
						CErrorHandler::PrepareError("Subtask of <compositeTask> cannot be used separately in <execution>.",pDOMpart,eHandler);
					}
				}
				allTasks.push_back(pDOMtask);
				partTaskSize += (XMLStringUtil::XML2Int(pDOMtask->getAttribute(XMLStrDefs::columns))*
					XMLStringUtil::XML2Int(pDOMtask->getAttribute(XMLStrDefs::rows)));
			}
			if (partTaskSize > minInputSize) {
				CErrorHandler::PrepareError("Task dimensions too large for network input.",pDOMpart,eHandler);
			}
			const DOMNodeList* pDOMchildList = pDOMpart->getChildNodes();
			for(XMLSize_t h1=0,hs1=pDOMchildList->getLength();h1<hs1;++h1) {
				DOMNode* thisChild = pDOMchildList->item(h1);
				if (thisChild->getNodeType() == DOMNode::ELEMENT_NODE) {
					DOMElement* thisParam = static_cast<DOMElement*>(thisChild);
					std::string namestr = XMLStringUtil::XML2Str(thisParam->getAttribute(XMLStrDefs::name));
					if (namestr == "timePerPattern")
						timePerPattern = false;
					else if (namestr == "zeroTime")
						zeroTime = false;
					else
						CErrorHandler::PrepareError("Unknown parameter name \"" + namestr + "\".",pDOMpart,eHandler);
				}
			}
			if (timePerPattern) {
				CErrorHandler::PrepareError("Missing parameter \"timePerPattern\".",pDOMpart,eHandler);
			}
			if (zeroTime) {
				CErrorHandler::PrepareError("Missing parameter \"zeroTime\".",pDOMpart,eHandler);
			}
		}
		allTasks.sort();
		allTasks.unique();
		for(std::list<const DOMElement*>::iterator it1=allTasks.begin(),ite1=allTasks.end();it1 != ite1;++it1) {
			mEx2Task[pDOMexecution].push_back(*it1);
		}
		//check if the loops contain references that don't belong to this execution
		const DOMNodeList* pDOMloopList = GetElementList(pDOMexecution,XMLStrDefs::loop);
		for(XMLSize_t l1=0,ls1=pDOMloopList->getLength();l1<ls1;++l1) {
			const DOMElement* pDOMloop = GetElement(pDOMloopList,l1);
			CheckDupl(pDOMloop,setupDoc,eHandler,XMLStrDefs::targets);
			CheckIDREFS(pDOMloop,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::loopParam,XMLStrDefs::initialisation);
			std::vector<XMLCh*> targets = XMLStringUtil::Tokenise(pDOMloop->getAttribute(XMLStrDefs::targets));
			XMLJanitor jan0(targets);
			for(size_t m1=0,ms1=targets.size();m1<ms1;++m1) {
				const DOMElement* pDOMtarget = setupDoc->getElementById(targets[m1]);
				const DOMElement* pDOMparent = BelongsToElement(pDOMtarget,setupDoc);
				if (!XMLStringUtil::Equals(pDOMparent->getTagName(),XMLStrDefs::xmldefault)) {
					if (!CheckLoopTarget(pDOMparent,pDOMexecution)) {
						CErrorHandler::PrepareError("Loop element \"" + XMLStringUtil::XML2Str(targets[m1]) + "\" does not exist in this <execution>.",pDOMloop,eHandler);
					}
				}
				else {
					std::vector<XMLCh*> deftargets = XMLStringUtil::Tokenise(pDOMparent->getAttribute(XMLStrDefs::targets));
					XMLJanitor jan3(deftargets);
					bool belongs = false;
					for(size_t m2=0,ms2=deftargets.size();m2<ms2;++m2) {
						const DOMElement* pDOMdeftarget = setupDoc->getElementById(deftargets[m2]);
						const DOMElement* pDOMdefparent = BelongsToElement(pDOMdeftarget,setupDoc);
						belongs |= CheckLoopTarget(pDOMdefparent,pDOMexecution);
					}
					if (!belongs) {
						CErrorHandler::PrepareError("Loop element \"" + XMLStringUtil::XML2Str(targets[m1]) + "\" does not exist in this <execution>.",pDOMloop,eHandler);
					}
				}
			}
		}	
	}
	//make all <part> elements
	if (create) {
		const DOMNodeList* pDOMpartList = GetElementList(setupDoc,XMLStrDefs::part);
		for(XMLSize_t p0=0,ps0=pDOMpartList->getLength();p0<ps0;++p0) {
			const DOMElement* pDOMpart = GetElement(pDOMpartList,p0);
			SExecutionElementMaker* partMaker = new SExecutionElementMaker("partV1");
			mExElMakers.insert(LExElMakers::value_type(pDOMpart,partMaker));
			std::string phasestr = XMLStringUtil::XML2Str(pDOMpart->getAttribute(XMLStrDefs::phase));
			if (phasestr == "train") {
				partMaker->random = true;
				partMaker->learn = true;
				partMaker->learnDuringReset = true;
				partMaker->generate = false;
			}
			else if (phasestr == "test") {
				partMaker->random = false;
				partMaker->learn = false;
				partMaker->learnDuringReset = false;
				partMaker->generate = false;
			}
			else if (phasestr == "generate") {
				partMaker->random = false;
				partMaker->learn = false;
				partMaker->learnDuringReset = false;
				partMaker->generate = true;
			}
			if (pDOMpart->hasAttribute(XMLStrDefs::random)) {
				partMaker->random = GetBool(pDOMpart,XMLStrDefs::random);
			}
			if (pDOMpart->hasAttribute(XMLStrDefs::learnDuringReset)) {
				partMaker->learnDuringReset = GetBool(pDOMpart,XMLStrDefs::learnDuringReset);
			}
			partMaker->timeValues = GetAttrInd(pDOMpart,XMLStrDefs::iterations);
			//add the tasks
			std::vector<XMLCh*> parttasks = XMLStringUtil::Tokenise(pDOMpart->getAttribute(XMLStrDefs::tasks));
			XMLJanitor jan4(parttasks);
			for(size_t t2=0,ts2=parttasks.size();t2<ts2;++t2) {
				const DOMElement* pDOMpartTask = setupDoc->getElementById(parttasks[t2]);
				partMaker->taskMakers.push_back(pTaskHandler->GetTaskMaker(pDOMpartTask));
			}
			//add the parameters
			const DOMNodeList* pDOMchildList = pDOMpart->getChildNodes();
			for(XMLSize_t h1=0,hs1=pDOMchildList->getLength();h1<hs1;++h1) {
				DOMNode* thisChild = pDOMchildList->item(h1);
				if (thisChild->getNodeType() == DOMNode::ELEMENT_NODE) {
					DOMElement* thisParam = static_cast<DOMElement*>(thisChild);
					double paramval = 0.0;
					if (thisParam->hasAttribute(XMLStrDefs::value)) {
						paramval = XMLStringUtil::XML2Dbl(thisParam->getAttribute(XMLStrDefs::value));
					}
					else {//loopParam
						std::vector<XMLCh*> values = XMLStringUtil::Tokenise(pDOMpart->getAttribute(XMLStrDefs::values));
						XMLJanitor jan5(values);
						paramval = XMLStringUtil::XML2Dbl(values[0]);
					}
					std::string namestr = XMLStringUtil::XML2Str(thisParam->getAttribute(XMLStrDefs::name));
					if (namestr == "timePerPattern")
						partMaker->executeParams[0] = paramval;
					else if (namestr == "zeroTime")
						partMaker->executeParams[1] = paramval;
				}
			}

		}
	}
	//make all <sequence> elements
	if (create) {
		const DOMNodeList* pDOMsequenceList = GetElementList(setupDoc,XMLStrDefs::sequence);
		for(XMLSize_t s0=0,ss0=pDOMsequenceList->getLength();s0<ss0;++s0) {
			const DOMElement* pDOMsequence = GetElement(pDOMsequenceList,s0);
			SExecutionElementMaker* sequenceMaker = new SExecutionElementMaker("sequenceV1");
			mExElMakers.insert(LExElMakers::value_type(pDOMsequence,sequenceMaker));
			sequenceMaker->timeValues = GetAttrInd(pDOMsequence,XMLStrDefs::repeat);
		}
		for(XMLSize_t s1=0,ss1=pDOMsequenceList->getLength();s1<ss1;++s1) {
			const DOMElement* pDOMsequence = GetElement(pDOMsequenceList,s1);
			const DOMNodeList* pDOMchildList = pDOMsequence->getChildNodes();
			for(XMLSize_t h1=0,hs1=pDOMchildList->getLength();h1<hs1;++h1) {
				DOMNode* thisChild = pDOMchildList->item(h1);
				if (thisChild->getNodeType() == DOMNode::ELEMENT_NODE) {
					DOMElement* pDOMel = static_cast<DOMElement*>(thisChild);
					if (XMLStringUtil::Equals(pDOMel->getTagName(),XMLStrDefs::part) || 
						XMLStringUtil::Equals(pDOMel->getTagName(),XMLStrDefs::sequence)) {
						if (static_cast<DOMElement*>(pDOMel->getParentNode()) == pDOMsequence) {
							mExElMakers[pDOMsequence]->partMakers.push_back(mExElMakers[pDOMel]);
						}
					}
				}
			}
		}
	}
	
	//handle all <loopParam> elements
	const DOMNodeList* pDOMloopParamList = GetElementList(setupDoc,XMLStrDefs::loopParam);
	for(XMLSize_t p1=0,ps1=pDOMloopParamList->getLength();p1<ps1;++p1) {
		const DOMElement* pDOMloopParam = GetElement(pDOMloopParamList,p1);
		const XMLCh* paramXCh = pDOMloopParam->getAttribute(XMLStrDefs::name);
		mLoopValues.insert(LLoopValues::value_type(pDOMloopParam,GetAttrVals(pDOMloopParam,XMLStrDefs::values)));
		const DOMElement* pDOMtarget = static_cast<DOMElement*>(pDOMloopParam->getParentNode());
		if (XMLStringUtil::EndsWith(pDOMtarget->getTagName(),XMLStrDefs::Params)) {//go one higher to get to the real target
			pDOMtarget = static_cast<DOMElement*>(pDOMtarget->getParentNode());
		}
		if (create) {
			SLoopElementMaker* loopElMaker = new SLoopElementMaker("loopVarV1");
			mLoopElMakers.insert(LLoopElMakers::value_type(pDOMloopParam,loopElMaker));
			loopElMaker->values.push_back(mLoopValues[pDOMloopParam]);
			if (XMLStringUtil::Equals(pDOMtarget->getTagName(),XMLStrDefs::xmldefault)) {//param part of <default>
				std::vector<XMLCh*> targets = XMLStringUtil::Tokenise(pDOMtarget->getAttribute(XMLStrDefs::targets));
				XMLJanitor jan6(targets);
				loopElMaker->paramNums = new std::valarray<size_t>(targets.size());
				for(size_t t0=0,ts0=targets.size();t0<ts0;++t0) {
					const DOMElement* pDOMrealTarget = setupDoc->getElementById(targets[t0]);
					HandleLoopParam(pDOMrealTarget,valDoc,loopElMaker,t0,paramXCh);
				}

			}
			else {//param part of an object, there's only one target and paramNum
				loopElMaker->paramNums = new std::valarray<size_t>(1);
				HandleLoopParam(pDOMtarget,valDoc,loopElMaker,0,paramXCh);
			}
		}
	}

	//handle all <initialisation> elements with more than 1 explicit <w>
	const DOMNodeList* pDOMinitList = GetElementList(setupDoc,XMLStrDefs::initialisation);
	for(XMLSize_t i1=0,is1=pDOMinitList->getLength();i1<is1;++i1) {
		const DOMElement* pDOMinit = GetElement(pDOMinitList,i1);
		const DOMNodeList* pDOMwList = GetElementList(pDOMinit,XMLStrDefs::w);
		if (create && (pDOMwList->getLength() > 1)) {
			SLoopElementMaker* loopElMaker = new SLoopElementMaker("loopWeightsV1");
			mLoopElMakers.insert(LLoopElMakers::value_type(pDOMinit,loopElMaker));
			loopElMaker->targets.push_back(pNetHandler->GetMaker(pDOMinit));
			for(XMLSize_t w1=0,ws1=pDOMwList->getLength();w1<ws1;++w1) {
				const DOMElement* pDOMw = GetElement(pDOMwList,w1);
				loopElMaker->values.push_back(pNetHandler->GetWeightVals(pDOMw));
			}
		}
	}
	//handle all <loop> elements
	const DOMNodeList* pDOMloopList = GetElementList(setupDoc,XMLStrDefs::loop);
	for(XMLSize_t m1=0,ms1=pDOMloopList->getLength();m1<ms1;++m1) {
		const DOMElement* pDOMloop = GetElement(pDOMloopList,m1);
		//check the number of elements
		size_t numValues = XMLStringUtil::XML2Int(pDOMloop->getAttribute(XMLStrDefs::numValues));
		std::vector<XMLCh*> targets = XMLStringUtil::Tokenise(pDOMloop->getAttribute(XMLStrDefs::targets));
		XMLJanitor jan7(targets);
		for(size_t n1=0,ns1=targets.size();n1<ns1;++n1) {
			const DOMElement* pDOMtarget = setupDoc->getElementById(targets[n1]);
			if (XMLStringUtil::Equals(pDOMtarget->getTagName(),XMLStrDefs::initialisation)) {
				if (numValues != GetElementList(pDOMtarget,XMLStrDefs::w)->getLength()) {
					CErrorHandler::PrepareError("Wrong number of values in loop element \"" + XMLStringUtil::XML2Str(targets[n1]) + "\".",pDOMloop,eHandler);
				}
				if (numValues == 1) {
					CErrorHandler::PrepareError("<initialisation> with only 1 <w> not allowed in <loop>.",pDOMtarget,eHandler);
				}
			}
			else {
				if (numValues != mLoopValues[pDOMtarget]->size()) {
					CErrorHandler::PrepareError("Wrong number of values in loop element \"" + XMLStringUtil::XML2Str(targets[n1]) + "\".",pDOMloop,eHandler);
				}
			}
		}
		if (create) {
			SLoopMaker* loopMaker = new SLoopMaker("loopV1");
			mLoopMakers.insert(LLoopMakers::value_type(pDOMloop,loopMaker));
			loopMaker->numConfigs = numValues;
			for(size_t n2=0,ns2=targets.size();n2<ns2;++n2) {
				const DOMElement* pDOMtarget = setupDoc->getElementById(targets[n2]);
				loopMaker->elemMakers.push_back(mLoopElMakers[pDOMtarget]);
			}
		}
	}

	//handle all <execution> elements
	for(XMLSize_t e2=0,es2=pDOMexecutionList->getLength();e2<es2;++e2) {
		const DOMElement* pDOMexecution = GetElement(pDOMexecutionList,e2);
		if (create) {
			SLoopsMaker* loopsMaker = new SLoopsMaker("loopsV1");
			mLoopsMakers.insert(LLoopsMakers::value_type(pDOMexecution,loopsMaker));
			const DOMNodeList* pDOMlocalLoopList = GetElementList(pDOMexecution,XMLStrDefs::loop);
			for(XMLSize_t l1=0,ls1=pDOMlocalLoopList->getLength();l1<ls1;++l1) {
				const DOMElement* pDOMlocalLoop = GetElement(pDOMlocalLoopList,l1);
				loopsMaker->loopMakers.push_back(mLoopMakers[pDOMlocalLoop]);
			}
			SExecutionMaker* executionMaker = new SExecutionMaker("executionV1");
			mExecutionMakers.insert(LExecutionMakers::value_type(pDOMexecution,executionMaker));
			executionMaker->numRuns = XMLStringUtil::XML2Int(pDOMexecution->getAttribute(XMLStrDefs::runs));
			executionMaker->sequenceMaker = mExElMakers[GetElement(pDOMexecution,XMLStrDefs::sequence,0)];
			std::vector<const DOMElement*>& exNets = mEx2Net[pDOMexecution];
			for(size_t n=0,ns=exNets.size();n<ns;++n) {
				executionMaker->netMakers.push_back(pNetHandler->GetNetMaker(exNets[n]));
			}
			std::vector<const DOMElement*>& exTasks = mEx2Task[pDOMexecution];
			for(size_t t=0,ts=exTasks.size();t<ts;++t) {
				executionMaker->taskMakers.push_back(pTaskHandler->GetTaskMaker(exTasks[t]));
			}
			executionMaker->loopsMaker = mLoopsMakers[pDOMexecution];
		}
	}
}
	
void CDOMExecutionImpl::AddEvents(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create)
{
	if (create) {
		const DOMNodeList* pDOMexecutionList = GetElementList(setupDoc,XMLStrDefs::execution);
		for(XMLSize_t e1=0,es1=pDOMexecutionList->getLength();e1<es1;++e1) {
			const DOMElement* pDOMexecution = GetElement(pDOMexecutionList,e1);
			SExecutionMaker* executionMaker = mExecutionMakers[pDOMexecution];
			std::list<SEventMaker*> allEvents;
			const DOMNodeList* pDOMpartList = GetElementList(pDOMexecution,XMLStrDefs::part);
			for(XMLSize_t p1=0,ps1=pDOMpartList->getLength();p1<ps1;++p1) {
				const DOMElement* pDOMpart = GetElement(pDOMpartList,p1);
				SExecutionElementMaker* partMaker = mExElMakers[pDOMpart];
				const std::vector<const DOMElement*>* pDOMpartEvents = pEventHandler->GetPartEvents(pDOMpart);
				if (pDOMpartEvents) {
					for(size_t v1=0,vs1=pDOMpartEvents->size();v1<vs1;++v1) {
						const DOMElement* pDOMevent = (*pDOMpartEvents)[v1];
						std::string eventtimestr = XMLStringUtil::XML2Str(pDOMevent->getAttribute(XMLStrDefs::eventTime));
						SEventMaker* eventMaker = pEventHandler->GetEventMaker(pDOMevent);
						if (partMaker->eventMakers.find(eventtimestr) == partMaker->eventMakers.end()) {
							partMaker->eventMakers[eventtimestr] = std::vector<SEventMaker*>();
						}
						partMaker->eventMakers[eventtimestr].push_back(eventMaker);
						allEvents.push_back(eventMaker);
					}
				}
			}
			allEvents.sort();
			allEvents.unique();
			for(std::list<SEventMaker*>::iterator it1=allEvents.begin(),ite1=allEvents.end();it1 != ite1;++it1) {
				executionMaker->eventMakers.push_back(*it1);
			}
		}
	}
}

SExecutionMaker* CDOMExecutionImpl::GetExecutionMaker(const DOMElement* el)
{
	if (mExecutionMakers.find(el) != mExecutionMakers.end())
		return mExecutionMakers[el];
	else
		return 0;
}
	
SMaker* CDOMExecutionImpl::GetMaker(const DOMElement* el)
{
	if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::execution)) {
		if (mExecutionMakers.find(el) != mExecutionMakers.end())
			return mExecutionMakers[el];
	}
	else if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::part)) {
		if (mExElMakers.find(el) != mExElMakers.end())
			return mExElMakers[el];
	}
	return 0;
}

void CDOMExecutionImpl::ReleaseAll()
{
	mPartParams.clear();
	mEx2Net.clear();
	mEx2Task.clear();
	for(LLoopValues::iterator it0=mLoopValues.begin(),ite0=mLoopValues.end();it0 != ite0;++it0) {
		delete it0->second;
		it0->second = 0;
	}
	mLoopValues.clear();
	for(LLoopElMakers::iterator it1=mLoopElMakers.begin(),ite1=mLoopElMakers.end();it1 != ite1;++it1) {
		SLoopElementMaker* loopElMaker = it1->second;
		delete loopElMaker->paramNums;
		delete loopElMaker;
		it1->second = 0;
	}
	mLoopElMakers.clear();
	for(LLoopMakers::iterator it2=mLoopMakers.begin(),ite2=mLoopMakers.end();it2 != ite2;++it2) {
		delete it2->second;
		it2->second = 0;
	}
	mLoopMakers.clear();
	for(LLoopsMakers::iterator it3=mLoopsMakers.begin(),ite3=mLoopsMakers.end();it3 != ite3;++it3) {
		delete it3->second;
		it3->second = 0;
	}
	mLoopsMakers.clear();
	for(LExElMakers::iterator it4=mExElMakers.begin(),ite4=mExElMakers.end();it4 != ite4;++it4) {
		SExecutionElementMaker* exElMaker = it4->second;
		delete exElMaker->timeValues;
		delete exElMaker;
		it4->second = 0;
	}
	mExElMakers.clear();
	for(LExecutionMakers::iterator it5=mExecutionMakers.begin(),ite5=mExecutionMakers.end();it5 != ite5;++it5) {
		delete it5->second;
		it5->second = 0;
	}
	mExecutionMakers.clear();
}

} //end namespace CORINET





