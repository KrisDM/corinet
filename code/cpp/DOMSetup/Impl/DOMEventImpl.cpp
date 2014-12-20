/*********************************************************************************************
 * Name      :  DOMEventImpl.cpp
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

#include <Setup/Makers.h>
#include <DOMSetup/DOMCommon.h>
#include <DOMSetup/DOMNet.h>
#include <DOMSetup/DOMTask.h>
#include <DOMSetup/DOMExecution.h>
#include <DOMSetup/Misc/DOMHelperFunctions.h>
#include "DOMEventImpl.h"
#include <XMLUtil/XMLFileUtil.h>
#include <valarray>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cctype>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

CDOMEventImpl::CDOMEventImpl() : mReportLocations(),mReportMakers(),mOperationMakers(),mConditionMakers(),
								 mActionMakers(),mEventMakers(),mPart2Events(),
								 pCommonHandler(0),pNetHandler(0),pTaskHandler(0),pExecutionHandler(0)
{

}

CDOMEventImpl::~CDOMEventImpl()
{
	ReleaseAll();
}

void CDOMEventImpl::SetCommonHandler(CDOMCommon* ph)
{
	pCommonHandler = ph;
}
	
void CDOMEventImpl::SetNetHandler(CDOMNet* ph)
{
	pNetHandler = ph;
}
	
void CDOMEventImpl::SetTaskHandler(CDOMTask* ph)
{
	pTaskHandler = ph;
}
	
void CDOMEventImpl::SetExecutionHandler(CDOMExecution* ph)
{
	pExecutionHandler = ph;
}

void CDOMEventImpl::HandleReport(const DOMElement* reportEl,const DOMDocument* setupDoc,DOMErrorHandler* eHandler,bool create)
{
	//first, get the location and check if it is unique
	const XMLCh* locXCh = reportEl->getAttribute(XMLStrDefs::location);
	std::string fullpathstr;
	if (XMLStringUtil::Equals(locXCh,XMLStrDefs::xmlstdout)) {
		fullpathstr = "stdout";
	}
	else {
		fullpathstr = XMLFileUtil::GetFullPath(locXCh);
	}
	if (mReportLocations.find(fullpathstr) != mReportLocations.end()) {
		CErrorHandler::PrepareError("\"location\" is not unique.",reportEl,eHandler); 
	}
	else {
		mReportLocations.insert(LReportLocations::value_type(fullpathstr,reportEl));
	}

	//get the type
	const XMLCh* typeXCh = reportEl->getAttribute(XMLStrDefs::type);
	std::string typestr = XMLStringUtil::XML2Str(typeXCh);
	
	//create the reportMaker
	if (create) {
		SReportMaker* reportMaker = new SReportMaker(typestr,fullpathstr);
		mReportMakers.insert(LReportMakers::value_type(reportEl,reportMaker));
		//create the sink, i.e. the file where results will be written
		if (typestr == "txt") {
			if (fullpathstr == "stdout") {
				reportMaker->sink = &(std::cout);
			}
			else {
				std::ofstream* ofstr = new std::ofstream(fullpathstr.c_str());
				if (ofstr->fail()) {
					CErrorHandler::PrepareError("Error opening report file",reportEl,eHandler);
				}
				reportMaker->sink = ofstr;
			}
		}
		else if (typestr == "xml") {
			XMLFormatTarget* pout = 0;
			if (fullpathstr == "stdout") {
				pout = new StdOutFormatTarget();
			}
			else {
				try {
					pout = new LocalFileFormatTarget(fullpathstr.c_str());
				}
				catch(...) {
					CErrorHandler::PrepareError("Error opening report file",reportEl,eHandler);
				}
			}
			reportMaker->sink = pout;
			XMLFileUtil::WriteToTarget("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",39,pout);
			XMLFileUtil::WriteToTarget("<results xmlns=\"http://www.corinet.org/namespaces/CORINETResults\">\n",67,pout);
		}
	}
}

void CDOMEventImpl::Handle(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create)
{
	//handle the <condition> elements
	const DOMNodeList* pDOMconditionList = GetElementList(setupDoc,XMLStrDefs::condition);
	for(XMLSize_t i1=0,is1=pDOMconditionList->getLength();i1<is1;++i1) {
		//get the current element
		const DOMElement* pDOMcondition = GetElement(pDOMconditionList,i1);
		const XMLCh* typeXCh = pDOMcondition->getAttribute(XMLStrDefs::type);

		//create the conditionMaker if needed
		if (create) {
			SConditionMaker* conditionMaker = new SConditionMaker(XMLStringUtil::XML2Str(typeXCh));
			mConditionMakers.insert(LConditionMakers::value_type(pDOMcondition,conditionMaker));
			conditionMaker->conditionVals = GetAttrVals(pDOMcondition,XMLStrDefs::values);
		}
	}
	//handle the <operation> elements
	const DOMNodeList* pDOMoperationList = GetElementList(setupDoc,XMLStrDefs::operation);
	for(XMLSize_t i2=0,is2=pDOMoperationList->getLength();i2<is2;++i2) {
		//get the current element
		const DOMElement* pDOMoperation = GetElement(pDOMoperationList,i2);
		const XMLCh* typeXCh = pDOMoperation->getAttribute(XMLStrDefs::type);

		//create the operationMaker if needed
		if (create) {
			SOperationMaker* operationMaker = new SOperationMaker(XMLStringUtil::XML2Str(typeXCh));
			mOperationMakers.insert(LOperationMakers::value_type(pDOMoperation,operationMaker));
			operationMaker->modifyVals = GetAttrVals(pDOMoperation,XMLStrDefs::values);
			if (operationMaker->type == "divide") {//check for divide-by-zero)
				for(size_t s1=0,ss1=operationMaker->modifyVals->size();s1<ss1;++s1) {
					if ((*(operationMaker->modifyVals))[s1] == 0.0) {
						CErrorHandler::PrepareError("Divide-by-zero error.",pDOMoperation,eHandler);
					}
				}
			}
		}
	}

	//handle the <report> elements
	const DOMNodeList* pDOMreportList = GetElementList(setupDoc,XMLStrDefs::report);
	for(XMLSize_t i3=0,is3=pDOMreportList->getLength();i3<is3;++i3) {
		const DOMElement* pDOMreport = GetElement(pDOMreportList,i3);
		HandleReport(pDOMreport,setupDoc,eHandler,create);
	}

	//handle all actions (<record>,<modify> and <modifyParam> elements)
	const DOMNodeList* pDOMrecordList = GetElementList(setupDoc,XMLStrDefs::record);
	for(XMLSize_t i4=0,is4=pDOMrecordList->getLength();i4<is4;++i4) {
		const DOMElement* pDOMrecord = GetElement(pDOMrecordList,i4);
		const XMLCh* typeXCh = pDOMrecord->getAttribute(XMLStrDefs::type);
		std::string typestr = XMLStringUtil::XML2Str(typeXCh);
		//check the targets
		CheckDupl(pDOMrecord,setupDoc,eHandler,XMLStrDefs::targets);
		if (typestr.substr(0,3) == "net") {
			CheckIDREFS(pDOMrecord,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::network);
		}
		else if (typestr.substr(0,4) == "task") {
			CheckIDREFS(pDOMrecord,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::task,XMLStrDefs::compositeTask);
		}
		else if (typestr.substr(0,5) == "block") {
			CheckIDREFS(pDOMrecord,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::block);
		}
		else {
			CheckIDREFS(pDOMrecord,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::integrationSite);
		}
		//check the report IDREF
		CheckIDREFS(pDOMrecord,setupDoc,eHandler,XMLStrDefs::report,XMLStrDefs::report);

		//create the actionMaker if necessary
		if (create) {
			std::string fulltypestr = "record";
			fulltypestr.append(1,static_cast<char>(toupper(typestr[0])));
			fulltypestr += typestr.substr(1);
			SActionMaker* actionMaker = new SActionMaker(fulltypestr);
			mActionMakers.insert(LActionMakers::value_type(pDOMrecord,actionMaker));
			//set attributes
			actionMaker->precision = XMLStringUtil::XML2Int(pDOMrecord->getAttribute(XMLStrDefs::precision));
			//set the reportMaker
			actionMaker->reportMaker = mReportMakers[setupDoc->getElementById(pDOMrecord->getAttribute(XMLStrDefs::report))];

			//add the targets
			std::vector<XMLCh*> targets = XMLStringUtil::Tokenise(pDOMrecord->getAttribute(XMLStrDefs::targets));
			XMLJanitor jan(targets);
			for(size_t t1=0,ts1=targets.size();t1<ts1;++t1) {
				const DOMElement* pDOMtarget = setupDoc->getElementById(targets[t1]);
				SMaker* targetMaker = 0;
				if (XMLStringUtil::Equals(pDOMtarget->getTagName(),XMLStrDefs::task) || 
					XMLStringUtil::Equals(pDOMtarget->getTagName(),XMLStrDefs::compositeTask))
					targetMaker = pTaskHandler->GetMaker(pDOMtarget);
				else 
					targetMaker = pNetHandler->GetMaker(pDOMtarget);
				actionMaker->targets.push_back(targetMaker);
			}
		}
	}
	const DOMNodeList* pDOMmodifyList = GetElementList(setupDoc,XMLStrDefs::modify);
	for(XMLSize_t i5=0,is5=pDOMmodifyList->getLength();i5<is5;++i5) {
		const DOMElement* pDOMmodify = GetElement(pDOMmodifyList,i5);
		const XMLCh* typeXCh = pDOMmodify->getAttribute(XMLStrDefs::type);
		std::string typestr = XMLStringUtil::XML2Str(typeXCh);
		//check the targets
		CheckDupl(pDOMmodify,setupDoc,eHandler,XMLStrDefs::targets);
		if (typestr.substr(0,3) == "net") {
			CheckIDREFS(pDOMmodify,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::network);
		}
		else if (typestr.substr(0,5) == "block") {
			CheckIDREFS(pDOMmodify,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::block);
		}
		else {
			CheckIDREFS(pDOMmodify,setupDoc,eHandler,XMLStrDefs::targets,XMLStrDefs::integrationSite);
		}
		//check the presence of attributes
		if (typestr == "weights") {
			if (!pDOMmodify->hasAttribute(XMLStrDefs::nodeIndices) && !pDOMmodify->hasAttribute(XMLStrDefs::inputIndices))
				CErrorHandler::PrepareError("Missing indices attributes.",pDOMmodify,eHandler);
		}
		else if (typestr == "integrationInput") {
			ExOrAttr(XMLStrDefs::inputIndices,XMLStrDefs::nodeIndices,pDOMmodify,eHandler);
		}
		else {
			ExOrAttr(XMLStrDefs::nodeIndices,XMLStrDefs::inputIndices,pDOMmodify,eHandler);
		}
		//create the actionMaker if necessary
		if (create) {
			std::string fulltypestr = "modify";
			fulltypestr.append(1,static_cast<char>(toupper(typestr[0])));
			fulltypestr += typestr.substr(1);
			SActionMaker* actionMaker = new SActionMaker(fulltypestr);
			mActionMakers.insert(LActionMakers::value_type(pDOMmodify,actionMaker));
			size_t maxNode = 0;
			size_t maxInput = 0;
			if (pDOMmodify->hasAttribute(XMLStrDefs::nodeIndices)) {
				actionMaker->nodeIndices = GetAttrInd(pDOMmodify,XMLStrDefs::nodeIndices);
				maxNode = actionMaker->nodeIndices->max();
			}
			if (pDOMmodify->hasAttribute(XMLStrDefs::inputIndices)) {
				actionMaker->inputIndices = GetAttrInd(pDOMmodify,XMLStrDefs::inputIndices);
				maxInput = actionMaker->inputIndices->max();
			}
			//add the targets
			std::vector<XMLCh*> targets = XMLStringUtil::Tokenise(pDOMmodify->getAttribute(XMLStrDefs::targets));
			XMLJanitor jan(targets);
			for(size_t t1=0,ts1=targets.size();t1<ts1;++t1) {
				const DOMElement* pDOMtarget = setupDoc->getElementById(targets[t1]);
				SMaker* targetMaker = 0;
				targetMaker = pNetHandler->GetMaker(pDOMtarget);
				actionMaker->targets.push_back(targetMaker);
				//for each target, check the indices
				if (targetMaker->makerType == "network") {
					SNetworkMaker* netMaker = static_cast<SNetworkMaker*>(targetMaker);
					if (maxNode > (netMaker->numInputs + netMaker->numNodes)) {
						CErrorHandler::PrepareError("Node index too large for target \"" + netMaker->idStr + "\".",pDOMmodify,eHandler);
					}
				}
				else if (targetMaker->makerType == "block") {
					SBlockMaker* blockMaker = static_cast<SBlockMaker*>(targetMaker);
					if (maxNode > (blockMaker->numNodes)) {
						CErrorHandler::PrepareError("Node index too large for target \"" + blockMaker->idStr + "\".",pDOMmodify,eHandler);
					}
				}
				else if (targetMaker->makerType == "integrationSite") {
					SIntegrationSiteMaker* siteMaker = static_cast<SIntegrationSiteMaker*>(targetMaker);
					if (maxInput > siteMaker->inputIndex->size()) {
						CErrorHandler::PrepareError("Input index too large for target \"" + siteMaker->idStr + "\".",pDOMmodify,eHandler);
					}
					if (maxNode) {
						const DOMElement* pDOMblock = static_cast<DOMElement*>(pDOMtarget->getParentNode());
						SBlockMaker* blockMaker = static_cast<SBlockMaker*>(pNetHandler->GetMaker(pDOMblock));
						if (maxNode > (blockMaker->numNodes)) {
							CErrorHandler::PrepareError("Node index too large for target \"" + siteMaker->idStr + "\".",pDOMmodify,eHandler);
						}
					}
				}
			}
			//add the operations
			const DOMNodeList* pDOMopList = GetElementList(pDOMmodify,XMLStrDefs::operation);
			for(XMLSize_t o1=0,os1=pDOMopList->getLength();o1<os1;++o1) {
				actionMaker->opMakers.push_back(mOperationMakers[GetElement(pDOMopList,o1)]);
			}
		}
	}
	const DOMNodeList* pDOMmodifyParamList = GetElementList(setupDoc,XMLStrDefs::modifyParam);
	for(XMLSize_t i6=0,is6=pDOMmodifyParamList->getLength();i6<is6;++i6) {
		const DOMElement* pDOMmodifyParam = GetElement(pDOMmodifyParamList,i6);
		const XMLCh* typeXCh = pDOMmodifyParam->getAttribute(XMLStrDefs::type);
		const XMLCh* paramXCh = pDOMmodifyParam->getAttribute(XMLStrDefs::paramName);
		std::string typestr = XMLStringUtil::XML2Str(typeXCh);
		
		//check the targets
		CheckDupl(pDOMmodifyParam,setupDoc,eHandler,XMLStrDefs::targets);
		std::vector<XMLCh*> targets = XMLStringUtil::Tokenise(pDOMmodifyParam->getAttribute(XMLStrDefs::targets));
		XMLJanitor jan(targets);
		for(size_t p0=0,ps0=targets.size();p0<ps0;++p0) {
			const XMLCh* thisref = targets[p0];
			const DOMElement* pDOMtarget = setupDoc->getElementById(thisref);
			const DOMElement* pDOMparent = BelongsToElementType(pDOMtarget,setupDoc);
			const XMLCh* parentTypeXCh = pDOMparent->getTagName();
			if (typestr == "network" && !XMLStringUtil::Equals(parentTypeXCh,XMLStrDefs::network)) {
				CErrorHandler::PrepareError("IDREF \"" + XMLStringUtil::XML2Str(thisref) + "\" refers to wrong type of element.",pDOMmodifyParam,eHandler);
			}
			if (typestr == "execution" && !XMLStringUtil::Equals(parentTypeXCh,XMLStrDefs::execution)) {
				CErrorHandler::PrepareError("IDREF \"" + XMLStringUtil::XML2Str(thisref) + "\" refers to wrong type of element.",pDOMmodifyParam,eHandler);
			}
			if (typestr == "task" && !(XMLStringUtil::Equals(parentTypeXCh,XMLStrDefs::task) ||
				XMLStringUtil::Equals(parentTypeXCh,XMLStrDefs::compositeTask))) {
				CErrorHandler::PrepareError("IDREF \"" + XMLStringUtil::XML2Str(thisref) + "\" refers to wrong type of element.",pDOMmodifyParam,eHandler);
			}
		}
		if (create) {
			std::string fulltypestr = "modifyParam";
			fulltypestr.append(1,static_cast<char>(toupper(typestr[0])));
			fulltypestr += typestr.substr(1);
			SActionMaker* actionMaker = new SActionMaker(fulltypestr);
			mActionMakers.insert(LActionMakers::value_type(pDOMmodifyParam,actionMaker));
			//get the targets and param numbers
			actionMaker->paramNums = new std::valarray<size_t>(targets.size());
			for(size_t p1=0,ps1=targets.size();p1<ps1;++p1) {
				const XMLCh* thisref = targets[p1];
				const DOMElement* pDOMtarget = setupDoc->getElementById(thisref);
				const DOMElement* pDOMvalTarget = 0;
				
				//get the param number
				if (typestr == "execution")
					pDOMvalTarget = GetElement(valDoc,XMLStrDefs::part,0);	
				else
					pDOMvalTarget = GetType(pDOMtarget,valDoc,eHandler);
				size_t paramnum = GetParamNum(paramXCh,pDOMvalTarget);
				if (paramnum == std::numeric_limits<size_t>::max()) {
					CErrorHandler::PrepareError("Unknown \"paramName\" for IDREF \"" + XMLStringUtil::XML2Str(thisref) + "\".",pDOMmodifyParam,eHandler);
				}
				(*(actionMaker->paramNums))[p1] = paramnum;
				
				//add the target
				SMaker* targetMaker = pExecutionHandler->GetMaker(pDOMtarget);
				if (!targetMaker) 
					targetMaker = pTaskHandler->GetMaker(pDOMtarget);
				if (!targetMaker)
					targetMaker = pNetHandler->GetMaker(pDOMtarget);
				if (!targetMaker)
					targetMaker = pCommonHandler->GetMaker(pDOMtarget);
				actionMaker->targets.push_back(targetMaker);
			}
			//add the operations
			const DOMNodeList* pDOMopList = GetElementList(pDOMmodifyParam,XMLStrDefs::operation);
			for(XMLSize_t o1=0,os1=pDOMopList->getLength();o1<os1;++o1) {
				actionMaker->opMakers.push_back(mOperationMakers[GetElement(pDOMopList,o1)]);
			}
		}
	}
	//handle all <event> elements
	const DOMNodeList* pDOMeventList = GetElementList(setupDoc,XMLStrDefs::event);
	for(XMLSize_t i7=0,is7=pDOMeventList->getLength();i7<is7;++i7) {
		const DOMElement* pDOMevent = GetElement(pDOMeventList,i7);
		CheckDupl(pDOMevent,setupDoc,eHandler,XMLStrDefs::parts);
		CheckIDREFS(pDOMevent,setupDoc,eHandler,XMLStrDefs::parts,XMLStrDefs::part);
		std::vector<XMLCh*> parts = XMLStringUtil::Tokenise(pDOMevent->getAttribute(XMLStrDefs::parts));
		XMLJanitor jan(parts);
		for(XMLSize_t j=0,js=parts.size();j<js;++j) {
			const DOMElement* pDOMpart = setupDoc->getElementById(parts[j]);
			mPart2Events[pDOMpart].push_back(pDOMevent);
		}
		if (create) {
			SEventMaker* eventMaker = new SEventMaker("eventModelV1");
			mEventMakers.insert(LEventMakers::value_type(pDOMevent,eventMaker));
			//add the conditions
			const DOMNodeList* condList = GetElementList(pDOMevent,XMLStrDefs::condition);
			for(XMLSize_t c1=0,cs1=condList->getLength();c1<cs1;++c1) {
				const DOMElement* thiscond = GetElement(condList,c1);
				eventMaker->condMakers.insert(std::multimap<const std::string,SConditionMaker*>::value_type(
					XMLStringUtil::XML2Str(thiscond->getAttribute(XMLStrDefs::variable)),mConditionMakers[thiscond]));
			}
			//add the actions
			const DOMNodeList* actionList = pDOMevent->getChildNodes();
			for(XMLSize_t c2=0,cs2=actionList->getLength();c2<cs2;++c2) {
				if (actionList->item(c2)->getNodeType() == DOMNode::ELEMENT_NODE) {
					const DOMElement* thisaction = GetElement(actionList,c2);
					const XMLCh* tagName = thisaction->getTagName();
					if (XMLStringUtil::Equals(tagName,XMLStrDefs::record) || XMLStringUtil::Equals(tagName,XMLStrDefs::modify) ||
						XMLStringUtil::Equals(tagName,XMLStrDefs::modifyParam)) {
						eventMaker->actionMakers.push_back(mActionMakers[thisaction]);
					}
				}
			}
		}
	}
}

SEventMaker* CDOMEventImpl::GetEventMaker(const XERCES_CPP_NAMESPACE::DOMElement* el)
{
	if (mEventMakers.find(el) != mEventMakers.end())
		return mEventMakers[el];
	else
		return 0;
}
	
SMaker* CDOMEventImpl::GetMaker(const XERCES_CPP_NAMESPACE::DOMElement* el)
{
	if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::event)) {
		if (mEventMakers.find(el) != mEventMakers.end())
			return mEventMakers[el];
	}
	return 0;
}

const std::vector<const DOMElement*>* CDOMEventImpl::GetPartEvents(const DOMElement* partEl)
{
	if (XMLStringUtil::Equals(partEl->getTagName(),XMLStrDefs::part)) {
		if (mPart2Events.find(partEl) != mPart2Events.end())
			return &(mPart2Events[partEl]);
	}
	return 0;
}

bool CDOMEventImpl::HasLocation(const std::string& locstr)
{
	if (mReportLocations.find(locstr) != mReportLocations.end())
		return true;
	return false;
}


void CDOMEventImpl::ReleaseAll()
{
	mPart2Events.clear();
	for(LConditionMakers::iterator it1=mConditionMakers.begin(),ite1=mConditionMakers.end();it1 != ite1;++it1) {
		delete it1->second->conditionVals;
		delete it1->second;
		it1->second = 0;
	}
	mConditionMakers.clear();
	for(LOperationMakers::iterator it2=mOperationMakers.begin(),ite2=mOperationMakers.end();it2 != ite2;++it2) {
		delete it2->second->modifyVals;
		delete it2->second;
		it2->second = 0;
	}
	mOperationMakers.clear();
	mReportLocations.clear();
	for(LReportMakers::iterator it3=mReportMakers.begin(),ite3=mReportMakers.end();it3 != ite3;++it3) {
		SReportMaker* reportMaker = it3->second;
		if (reportMaker->type == "xml") {
			XMLFormatTarget* pout = static_cast<XMLFormatTarget*>(reportMaker->sink);
			if (pout) {
				XMLFileUtil::WriteToTarget("\n\n</results>\n\n",14,pout);
				delete pout;
			}
		}
		else if (reportMaker->type == "txt") {
			std::ostream* pout = static_cast<std::ostream*>(reportMaker->sink);
			if (pout) {
				pout->flush();
				if (reportMaker->location != "stdout") {
					delete pout;
				}
			}
		}
		delete reportMaker;
		it3->second = 0;
	}
	mReportMakers.clear();
	for(LActionMakers::iterator it4=mActionMakers.begin(),ite4=mActionMakers.end();it4 != ite4;++it4) {
		SActionMaker* actionMaker = it4->second;
		delete actionMaker->nodeIndices;
		delete actionMaker->inputIndices;
		delete actionMaker->paramNums;
		delete actionMaker;
		it4->second = 0;
	}
	mActionMakers.clear();
	for(LEventMakers::iterator it5=mEventMakers.begin(),ite5=mEventMakers.end();it5 != ite5;++it5) {
		delete it5->second;
		it5->second = 0;
	}
	mEventMakers.clear();
}

} //end namespace CORINET






