/*********************************************************************************************
 * Name      :  DOMTaskImpl.cpp
 *
 * Purpose   :  Implementation class handling tasks and child elements.
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
#include <DOMSetup/DOMDefaults.h>
#include <DOMSetup/DOMCommon.h>
#include <DOMSetup/Misc/DOMHelperFunctions.h>
#include <XMLUtil/XMLSchemaDefs.h>
#include "DOMTaskImpl.h"
#include <valarray>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

CDOMTaskImpl::CDOMTaskImpl() : mPatternSets(),mDataMakers(),mTaskMakers(),pDefaultsHandler(0),pCommonHandler(0)
{

}

CDOMTaskImpl::~CDOMTaskImpl()
{
	ReleaseAll();
}

void CDOMTaskImpl::SetDefaultsHandler(CDOMDefaults* pdef)
{
	pDefaultsHandler = pdef;
}
	
void CDOMTaskImpl::SetCommonHandler(CDOMCommon* pcom)
{
	pCommonHandler = pcom;
}

void CDOMTaskImpl::Handle(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create)
{
	//handle all <patternSet> elements
	const DOMNodeList* pDOMsetList = GetElementList(setupDoc,XMLStrDefs::patternSet);
	for(XMLSize_t s1=0,ss1=pDOMsetList->getLength();s1<ss1;++s1) {
		const DOMElement* pDOMset = GetElement(pDOMsetList,s1);
		size_t numcols = XMLStringUtil::XML2Int(pDOMset->getAttribute(XMLStrDefs::columns));
		size_t numrows = XMLStringUtil::XML2Int(pDOMset->getAttribute(XMLStrDefs::rows));
		std::vector<const std::valarray<double>*>* patterns = 0;
		if (create) {
			patterns = new std::vector<const std::valarray<double>*>;
			mPatternSets.insert(LPatternSets::value_type(pDOMset,patterns));
		}
		//get the values
		const DOMNodeList* pDOMpList = GetElementList(pDOMset,XMLStrDefs::p);
		for(XMLSize_t p1=0,ps1=pDOMpList->getLength();p1<ps1;++p1) {
			const DOMElement* pDOMp = GetElement(pDOMpList,p1);
			std::valarray<double>* tempVals = 0;
			if (create) {
				tempVals = new std::valarray<double>(numcols*numrows);
				patterns->push_back(tempVals);
			}
			Get2DVals(pDOMp,numrows,numcols,XMLStrDefs::r,XMLStrDefs::c,pDOMset,eHandler,tempVals);
		}
	}

	//handle all <dataSource> elements
	const DOMNodeList* pDOMdataSourceList = GetElementList(setupDoc,XMLStrDefs::dataSource);
	for(XMLSize_t d1=0,ds1=pDOMdataSourceList->getLength();d1<ds1;++d1) {
		const DOMElement* pDOMsource = GetElement(pDOMdataSourceList,d1);
		size_t numcols = XMLStringUtil::XML2Int(pDOMsource->getAttribute(XMLStrDefs::columns));
		size_t numrows = XMLStringUtil::XML2Int(pDOMsource->getAttribute(XMLStrDefs::rows));
		size_t numpatterns = XMLStringUtil::XML2Int(pDOMsource->getAttribute(XMLStrDefs::patterns));

		const DOMElement* pDOMsourceParams = GetElement(pDOMsource,XMLStrDefs::sourceParams,0);
		const XMLCh* typeXCh = pDOMsource->getAttribute(XMLStrDefs::type);
		std::string typestr = XMLStringUtil::XML2Str(typeXCh);
		//check its type
		const DOMElement* pDOMvalSource = GetType(pDOMsource,valDoc,eHandler);

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalSource,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMsourceParams,pDOMvalSource,eHandler,pDOMsource);
		if (create) {
			SDataSourceMaker* dataMaker = new SDataSourceMaker(typestr);
			mDataMakers.insert(LDataMakers::value_type(pDOMsource,dataMaker));
			for(size_t i=0,is=vals.size();i<is;++i) {
				dataMaker->sourceParams[i] = vals[i];
			}
			dataMaker->columns = numcols;
			dataMaker->rows = numrows;
			dataMaker->patterns = numpatterns;
		}
	}

	//handle all <task> elements
	const DOMNodeList* pDOMtaskList = GetElementList(setupDoc,XMLStrDefs::task);
	for(XMLSize_t t1=0,ts1=pDOMtaskList->getLength();t1<ts1;++t1) {
		//get the current element
		const DOMElement* pDOMtask = GetElement(pDOMtaskList,t1);
		
		const DOMElement* pDOMtaskParams = GetElement(pDOMtask,XMLStrDefs::taskParams,0);
		const XMLCh* typeXCh = pDOMtask->getAttribute(XMLStrDefs::type);
		std::string typestr = XMLStringUtil::XML2Str(typeXCh);
		//check its type
		const DOMElement* pDOMvalTask = GetType(pDOMtask,valDoc,eHandler);

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalTask,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMtaskParams,pDOMvalTask,eHandler,pDOMtask,
			pDefaultsHandler->GetParams(pDOMtask),pDefaultsHandler->GetParams(typeXCh));
		
		size_t taskcols = XMLStringUtil::XML2Int(pDOMtask->getAttribute(XMLStrDefs::columns));
		size_t taskrows = XMLStringUtil::XML2Int(pDOMtask->getAttribute(XMLStrDefs::rows));

		//see if there is a patternset defined locally
		const DOMElement* pDOMset = GetElement(pDOMtask,XMLStrDefs::patternSet,0);
		//see if there is a patternset in the defaults
		if (!pDOMset)
			pDOMset = pDefaultsHandler->GetObject(pDOMtask,XMLStrDefs::patternSet);
		//see if there is a local datasource
		const DOMElement* pDOMsource = GetElement(pDOMtask,XMLStrDefs::dataSource,0);
		//see if there is a datasource in the defaults
		if (!pDOMsource)
			pDOMsource = pDefaultsHandler->GetObject(pDOMtask,XMLStrDefs::dataSource);

		if (pDOMset || pDOMsource) {
			if (XMLStringUtil::Equals(pDOMvalTask->getAttribute(XMLStrDefs::patternSet),XMLStrDefs::prohibited)) {
				CErrorHandler::PrepareError("<patternSet> or <dataSource> prohibited for this type.",pDOMtask,eHandler);
			}
			if (pDOMset && pDOMsource) {
				CErrorHandler::PrepareError("Please specify either a <patternSet> or a <dataSource>.",pDOMtask,eHandler);
			}
		}
		else if (XMLStringUtil::Equals(pDOMvalTask->getAttribute(XMLStrDefs::patternSet),XMLStrDefs::required)) {
			CErrorHandler::PrepareError("<patternSet> or <dataSource> required for this type.",pDOMtask,eHandler);
		}
		if (pDOMset) {//check the size of the <patternSet>
			size_t setcols = XMLStringUtil::XML2Int(pDOMset->getAttribute(XMLStrDefs::columns));
			size_t setrows = XMLStringUtil::XML2Int(pDOMset->getAttribute(XMLStrDefs::rows));
			if (setcols>taskcols || setrows>taskrows) {
				CErrorHandler::PrepareError("Dimensions of <patternSet> too large.",pDOMtask,eHandler);
			}
		}

		if (pDOMsource) {//check the size of the <dataSource>
			size_t srccols = XMLStringUtil::XML2Int(pDOMsource->getAttribute(XMLStrDefs::columns));
			size_t srcrows = XMLStringUtil::XML2Int(pDOMsource->getAttribute(XMLStrDefs::rows));
			if (srccols>taskcols || srcrows>taskrows) {
				CErrorHandler::PrepareError("Dimensions of <dataSource> too large.",pDOMtask,eHandler);
			}
		}
		if (create) {
			std::string idstr = XMLStringUtil::XML2Str(pDOMtask->getAttribute(XMLStrDefs::id));
			STaskMaker* taskMaker = new STaskMaker(typestr,idstr);
			mTaskMakers.insert(LTaskMakers::value_type(pDOMtask,taskMaker));
			//set the parameters
			for(size_t i=0,is=vals.size();i<is;++i) {
				taskMaker->taskParams[i] = vals[i];
			}
			//set various attributes
			taskMaker->columns = taskcols;
			taskMaker->rows = taskrows;
			if (pDOMtask->hasAttribute(XMLStrDefs::store)) {
				taskMaker->store = XMLStringUtil::XML2Int(pDOMtask->getAttribute(XMLStrDefs::store));
			}
			if (pDOMtask->hasAttribute(XMLStrDefs::sampleMethod)) {
				taskMaker->sampleMethod = XMLStringUtil::XML2Str(pDOMtask->getAttribute(XMLStrDefs::sampleMethod));
			}
			else {
				taskMaker->sampleMethod = "withoutReplacement";
			}
			if (pDOMtask->hasAttribute(XMLStrDefs::seed)) {
				taskMaker->seed = XMLStringUtil::XML2Int(pDOMtask->getAttribute(XMLStrDefs::seed));
			}

			//set the attenuation if there's one
			const DOMElement* pDOMattenuation = GetElement(pDOMtask,XMLStrDefs::attenuation,0);
				if (!pDOMattenuation) {//look in <targetDefaults>
				pDOMattenuation = pDefaultsHandler->GetObject(pDOMtask,XMLStrDefs::attenuation);
			}
			if (!pDOMattenuation) {//look in <typeDefaults>
				pDOMattenuation = pDefaultsHandler->GetObject(typeXCh,XMLStrDefs::attenuation);
			}
			if (pDOMattenuation) {
				taskMaker->attenuationMaker = pCommonHandler->GetAttenuationMaker(pDOMattenuation);
			}
			//set the noise function if there's one
			const DOMElement* pDOMnoise = GetElement(pDOMtask,XMLStrDefs::noiseFunction,0);
			if (!pDOMnoise) {//look in <targetDefaults>
				pDOMnoise = pDefaultsHandler->GetObject(pDOMtask,XMLStrDefs::noiseFunction);
			}
			if (!pDOMnoise) {//look in <typeDefaults>
				pDOMnoise = pDefaultsHandler->GetObject(typeXCh,XMLStrDefs::noiseFunction);
			}
			if (pDOMnoise) {
				taskMaker->noiseMaker = pCommonHandler->GetNoiseMaker(pDOMnoise);
			}
			//set the patternset
			if (pDOMset) {
				taskMaker->patterns = mPatternSets[pDOMset];
			}
			//set the datasource
			if (pDOMsource) {
				taskMaker->dataMaker = mDataMakers[pDOMsource];
			}
		}
	}

	//handle all <insert> elements
	const DOMNodeList* pDOMinsertList = GetElementList(setupDoc,XMLStrDefs::insert);
	for(XMLSize_t i1=0,is1=pDOMinsertList->getLength();i1<is1;++i1) {
		//get the current element
		const DOMElement* pDOMinsert = GetElement(pDOMinsertList,i1);
		
		const DOMElement* pDOMinsertParams = GetElement(pDOMinsert,XMLStrDefs::insertParams,0);
		const XMLCh* typeXCh = pDOMinsert->getAttribute(XMLStrDefs::type);
		std::string typestr = XMLStringUtil::XML2Str(typeXCh);
		//check its type
		const DOMElement* pDOMvalInsert = GetType(pDOMinsert,valDoc,eHandler);

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalInsert,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMinsertParams,pDOMvalInsert,eHandler,pDOMinsert,
			pDefaultsHandler->GetParams(pDOMinsert),pDefaultsHandler->GetParams(typeXCh));

		if (create) {
			SInsertMaker* insertMaker = new SInsertMaker(typestr);
			mInsertMakers.insert(LInsertMakers::value_type(pDOMinsert,insertMaker));
			for(size_t i=0,is=vals.size();i<is;++i) {
				insertMaker->insertParams[i] = vals[i];
			}
			//get attribute values
			insertMaker->inColumn = XMLStringUtil::XML2Int(pDOMinsert->getAttribute(XMLStrDefs::inColumn));
			insertMaker->inRow = XMLStringUtil::XML2Int(pDOMinsert->getAttribute(XMLStrDefs::inRow));

			//add all the tasks
			const DOMNodeList* pDOMtaskList = GetElementList(pDOMinsert,XMLStrDefs::task);
			for(size_t t2=0,ts2=pDOMtaskList->getLength();t2<ts2;++t2) {
				const DOMElement* pDOMtask = GetElement(pDOMtaskList,t2);
				insertMaker->taskMakers.push_back(mTaskMakers[pDOMtask]);
			}
		}
	}

	//handle all <compositeTask> elements
	const DOMNodeList* pDOMcompositeTaskList = GetElementList(setupDoc,XMLStrDefs::compositeTask);
	for(XMLSize_t ct1=0,cts1=pDOMcompositeTaskList->getLength();ct1<cts1;++ct1) {
		//get the current element
		const DOMElement* pDOMcompositeTask = GetElement(pDOMcompositeTaskList,ct1);
		
		const DOMElement* pDOMtaskParams = GetElement(pDOMcompositeTask,XMLStrDefs::taskParams,0);
		//check if this is a direct child of the composite task, if not it belongs to a child task
		if (pDOMtaskParams) {
			const DOMElement* pDOMparent = static_cast<DOMElement*>(pDOMtaskParams->getParentNode());
			if (pDOMparent != pDOMcompositeTask) {
				pDOMtaskParams = 0;
			}
		}
		const XMLCh* typeXCh = pDOMcompositeTask->getAttribute(XMLStrDefs::type);
		std::string typestr = XMLStringUtil::XML2Str(typeXCh);
		//check its type
		const DOMElement* pDOMvalTask = GetType(pDOMcompositeTask,valDoc,eHandler);

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalTask,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMtaskParams,pDOMvalTask,eHandler,pDOMcompositeTask,
			pDefaultsHandler->GetParams(pDOMcompositeTask),pDefaultsHandler->GetParams(typeXCh));
		
		size_t ctcols = XMLStringUtil::XML2Int(pDOMcompositeTask->getAttribute(XMLStrDefs::columns));
		size_t ctrows = XMLStringUtil::XML2Int(pDOMcompositeTask->getAttribute(XMLStrDefs::rows));

		//check the sizes of all inserts + child task size
		//two options: ctrows > 1, then inserts have to be smaller in two dimensension
		//ctrows == 1 (1D composite pattern), then inserts just have to be smaller in overall size
		const DOMNodeList* pDOMinsertList = GetElementList(pDOMcompositeTask,XMLStrDefs::insert);
		for(XMLSize_t i2=0,is2=pDOMinsertList->getLength();i2<is2;++i2) {
			//get the current element
			const DOMElement* pDOMinsert = GetElement(pDOMinsertList,i2);
			size_t insertincol = XMLStringUtil::XML2Int(pDOMinsert->getAttribute(XMLStrDefs::inColumn));
			size_t insertinrow = XMLStringUtil::XML2Int(pDOMinsert->getAttribute(XMLStrDefs::inRow));
			//first check if inColumn and inRow are not larger than enclosing task size
			if (insertincol>=ctcols || insertinrow>=ctrows) {
				CErrorHandler::PrepareError("Indices of <insert> too large.",pDOMcompositeTask,eHandler);
			}
			//now go through all child simple tasks and see if we can safely write all their values into the composite task
			//this means that the overall size of the composite task must be large enough, not the two dimensions separately
			const DOMNodeList* pDOMsimpleTaskList = GetElementList(pDOMinsert,XMLStrDefs::task);
			for(XMLSize_t st1=0,sst1=pDOMsimpleTaskList->getLength();st1<sst1;++st1) {
				const DOMElement* pDOMsimpleTask = GetElement(pDOMsimpleTaskList,st1);
				size_t stcols = XMLStringUtil::XML2Int(pDOMsimpleTask->getAttribute(XMLStrDefs::columns));
				size_t strows = XMLStringUtil::XML2Int(pDOMsimpleTask->getAttribute(XMLStrDefs::rows));
				if (ctrows > 1) {
					if (ctrows < strows + insertinrow || ctcols < stcols + insertincol) {
						CErrorHandler::PrepareError("Dimensions of child <task> too large",pDOMcompositeTask,eHandler);
					}
				}
				else {
					size_t stsize = stcols*strows;
					if (ctcols < stsize + insertincol) {
						CErrorHandler::PrepareError("Child <task> does not fit 1D <compositeTask>",pDOMcompositeTask,eHandler);
					}
				}
			}
		}
		if (create) {
			std::string idstr = XMLStringUtil::XML2Str(pDOMcompositeTask->getAttribute(XMLStrDefs::id));
			STaskMaker* taskMaker = new STaskMaker(typestr,idstr);
			mTaskMakers.insert(LTaskMakers::value_type(pDOMcompositeTask,taskMaker));
			//set the parameters
			for(size_t i=0,is=vals.size();i<is;++i) {
				taskMaker->taskParams[i] = vals[i];
			}
			//set various attributes
			taskMaker->columns = ctcols;
			taskMaker->rows = ctrows;
			if (pDOMcompositeTask->hasAttribute(XMLStrDefs::store)) {
				taskMaker->store = XMLStringUtil::XML2Int(pDOMcompositeTask->getAttribute(XMLStrDefs::store));
			}
			if (pDOMcompositeTask->hasAttribute(XMLStrDefs::sampleMethod)) {
				taskMaker->sampleMethod = XMLStringUtil::XML2Str(pDOMcompositeTask->getAttribute(XMLStrDefs::sampleMethod));
			}
			else {
				taskMaker->sampleMethod = "withoutReplacement";
			}
			if (pDOMcompositeTask->hasAttribute(XMLStrDefs::seed)) {
				taskMaker->seed = XMLStringUtil::XML2Int(pDOMcompositeTask->getAttribute(XMLStrDefs::seed));
			}

			//set the attenuation if there's one
			const DOMNodeList* pDOMattenuationList = GetElementList(pDOMcompositeTask,XMLStrDefs::attenuation);
			//get the last one from the list and see if it is a direct child of <compositeTask>
			const DOMElement* pDOMattenuation = 0;
			if (pDOMattenuationList->getLength()) {
				pDOMattenuation = GetElement(pDOMattenuationList,pDOMattenuationList->getLength()-1);
				if (static_cast<DOMElement*>(pDOMattenuation->getParentNode()) != pDOMcompositeTask) {
					pDOMattenuation = 0;
				}
			}
			if (!pDOMattenuation) {//look in <targetDefaults>
				pDOMattenuation = pDefaultsHandler->GetObject(pDOMcompositeTask,XMLStrDefs::attenuation);
			}
			if (!pDOMattenuation) {//look in <typeDefaults>
				pDOMattenuation = pDefaultsHandler->GetObject(typeXCh,XMLStrDefs::attenuation);
			}
			if (pDOMattenuation) {
				taskMaker->attenuationMaker = pCommonHandler->GetAttenuationMaker(pDOMattenuation);
			}
			//set the noise function if there's one
			const DOMNodeList* pDOMnoiseList = GetElementList(pDOMcompositeTask,XMLStrDefs::noiseFunction);
			//get the last one from the list and see if it is a direct child of <compositeTask>
			const DOMElement* pDOMnoise = 0;
			if (pDOMnoiseList->getLength()) {
				pDOMnoise = GetElement(pDOMnoiseList,pDOMnoiseList->getLength()-1);
				if (static_cast<DOMElement*>(pDOMnoise->getParentNode()) != pDOMcompositeTask) {
					pDOMnoise = 0;
				}
			}
			if (!pDOMnoise) {//look in <targetDefaults>
				pDOMnoise = pDefaultsHandler->GetObject(pDOMcompositeTask,XMLStrDefs::noiseFunction);
			}
			if (!pDOMnoise) {//look in <typeDefaults>
				pDOMnoise = pDefaultsHandler->GetObject(typeXCh,XMLStrDefs::noiseFunction);
			}
			if (pDOMnoise) {
				taskMaker->noiseMaker = pCommonHandler->GetNoiseMaker(pDOMnoise);
			}
			//add all the inserts
			for(XMLSize_t i3=0,is3=pDOMinsertList->getLength();i3<is3;++i3) {
				//get the current element
				const DOMElement* pDOMinsert = GetElement(pDOMinsertList,i3);
				taskMaker->insertMakers.push_back(mInsertMakers[pDOMinsert]);
			}
		}
	}
}

STaskMaker* CDOMTaskImpl::GetTaskMaker(const DOMElement* el)
{
	if (mTaskMakers.find(el) != mTaskMakers.end())
		return mTaskMakers[el];
	else
		return 0;
}
	
SMaker* CDOMTaskImpl::GetMaker(const DOMElement* el)
{
	if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::task) || 
		XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::compositeTask)) {
		if (mTaskMakers.find(el) != mTaskMakers.end())
			return mTaskMakers[el];
	}
	else if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::insert)) {
		if (mInsertMakers.find(el) != mInsertMakers.end())
			return mInsertMakers[el];
	}
	else if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::dataSource)) {
		if (mDataMakers.find(el) != mDataMakers.end())
			return mDataMakers[el];
	}
	return 0;
}

void CDOMTaskImpl::ReleaseAll()
{
	for(LPatternSets::iterator it0=mPatternSets.begin(),ite0=mPatternSets.end();it0 != ite0;++it0) {
		std::vector<const std::valarray<double>*>* patterns = it0->second;
		for(size_t p1=0,ps1=patterns->size();p1<ps1;++p1) {
			delete (*patterns)[p1];
			(*patterns)[p1] = 0;
		}
		patterns->clear();
		delete patterns;
		it0->second = 0;
	}
	mPatternSets.clear();
	for(LDataMakers::iterator it1=mDataMakers.begin(),ite1=mDataMakers.end();it1 != ite1;++it1) {
		delete it1->second;
		it1->second = 0;
	}
	mDataMakers.clear();
	for(LInsertMakers::iterator it2=mInsertMakers.begin(),ite2=mInsertMakers.end();it2 != ite2;++it2) {
		delete it2->second;
		it2->second = 0;
	}
	mInsertMakers.clear();
	for(LTaskMakers::iterator it3=mTaskMakers.begin(),ite3=mTaskMakers.end();it3 != ite3;++it3) {
		delete it3->second;
		it3->second = 0;
	}
	mTaskMakers.clear();
}

} //end namespace CORINET



