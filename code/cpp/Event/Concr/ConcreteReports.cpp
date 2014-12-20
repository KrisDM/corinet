/*********************************************************************************************
 * Name      :  ConcreteReports.cpp
 *
 * Purpose   :  Functionality for writing results in a certain format, currently either text
 *				or XML. CReport objects should be combined with event handlers.
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

#include <Util/Iterator.h>
#include <Util/Output.h>
#include <Model/SynapseWrapper.h>
#include <Engine/ExTimeInfo.h>
#include "ConcreteReports.h"
#include <XMLUtil/XMLStringUtil.h>
#include <XMLUtil/XMLResultsDefs.h>
#include <XMLUtil/XMLStrDefs.h>
#include <XMLUtil/XMLSchemaDefs.h>
#include <xercesc/dom/DOM.hpp>
#include <limits>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CTextReport::CTextReport()
{

}

CTextReport::~CTextReport()
{
	
}

void CTextReport::Initialise(void*,CExTimeInfo*)
{

}

void CTextReport::Write(size_t prec,SubArrayIteratorConst* v,CExTimeInfo*)
{
	pOut->precision(prec);
	(*pOut) << *v << '\n' << std::flush;	
}

void CTextReport::Write(size_t prec,SliceIteratorConst* v,CExTimeInfo*)
{
	pOut->precision(prec);
	(*pOut) << *v << '\n' << std::flush;	
}

void CTextReport::Write(size_t prec,IndirectIteratorConst* v,CExTimeInfo*)
{
	pOut->precision(prec);
	(*pOut) << *v << '\n' << std::flush;	
}

void CTextReport::Write(size_t prec,MultipleSubArrayIteratorConst* v,CExTimeInfo*)
{
	pOut->precision(prec);
	(*pOut) << *v << '\n' << std::flush;	
}

void CTextReport::Write(size_t prec,MatrixIteratorConst* v,CExTimeInfo*,size_t)
{
	pOut->precision(prec);
	(*pOut) << *v << '\n' << std::flush;
}

void CTextReport::Write(size_t prec,SynapseWrapper* v,CExTimeInfo*)
{
	pOut->precision(prec);
	double mult = pow(10.0,static_cast<int>(prec));
	for(size_t j=0,nodes=v->nodes();j<nodes;++j) {
		for(size_t i=0,inputs=v->inputs();i<inputs;++i) {
			(*pOut) << std::setw(prec + 4) << static_cast<int>(((*v)(i,j))*mult)/mult;
		}
		(*pOut) << '\n';
	}
	(*pOut) << '\n' << std::flush;
}

void CTextReport::Finalise(void*,CExTimeInfo*)
{

}

void CTextReport::SetSink(void* ps)
{
	pOut = static_cast<std::ostream*>(ps);
	pOut->setf(std::ios_base::left);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CXMLReport::CXMLReport() : pOut(0),pResultsDoc(0),mDOMTargetNodes(),mDOMCycleNodes(),ost()
{
	XMLPlatformUtils::Initialize();
	ost.setf(std::ios_base::left);
	//construct a DOM document that will hold the data for this particular reporter
	//get the implementation
	DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(XMLResultsDefs::LS);
	//create the document
	pResultsDoc = impl->createDocument(0,XMLResultsDefs::results,0);
	//create <execution> element
	DOMElement* newExec = pResultsDoc->createElement(XMLResultsDefs::execution);
	pResultsDoc->getDocumentElement()->appendChild(newExec);
}

CXMLReport::~CXMLReport() 
{
	//construct the DOMWriter
	DOMImplementationLS* impl = DOMImplementationRegistry::getDOMImplementation(XMLResultsDefs::LS);
	DOMWriter* writer = impl->createDOMWriter();
	writer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint,true);
	DOMNode* pDOMExecution = pResultsDoc->getElementsByTagName(XMLResultsDefs::execution)->item(0);
	//write the <execution> element and all its children to the file
	writer->writeNode(pOut,*pDOMExecution);
	writer->release();
	pResultsDoc->release();
	XMLPlatformUtils::Terminate();
}

void CXMLReport::MakeTopLevelNode(const std::string& typeStr,const std::string& idStr)
{
	//create a network or task element
	std::string newType = typeStr;
	if (newType == "compositeTask") {//make sure that compositeTasks appear as tasks in the result file
		newType = "task";
	}
	XMLCh* tagXCh = XMLStringUtil::Str2XML(newType);
	DOMElement* newNode = pResultsDoc->createElement(tagXCh);
	XMLStringUtil::Release(tagXCh);
	//set the ID argument
	XMLCh* idXCh = XMLStringUtil::Str2XML(idStr);
	newNode->setAttribute(XMLResultsDefs::id,idXCh);
	XMLStringUtil::Release(idXCh);
	newNode->setIdAttribute(XMLResultsDefs::id);
	//add the node to the DOM
	pResultsDoc->getElementsByTagName(XMLResultsDefs::execution)->item(0)->appendChild(newNode);
}

void CXMLReport::MakeTargetNode(void* target,const std::string& idStr,const std::string& type,const std::string& parent)
{
	if (mDOMTargetNodes.find(target) == mDOMTargetNodes.end()) {
		XMLCh* parentXCh = XMLStringUtil::Str2XML(parent);
		DOMElement* parentNode = pResultsDoc->getElementById(parentXCh);
		XMLStringUtil::Release(parentXCh);
		if (type == "taskPatterns") {
			if (parent == idStr)
				mDOMTargetNodes.insert(LDOMElements::value_type(target,parentNode));
			else {
				DOMElement* newTask = pResultsDoc->createElement(XMLResultsDefs::task);
				//set the ID attribute
				XMLCh* idXCh = XMLStringUtil::Str2XML(idStr);
				newTask->setAttribute(XMLResultsDefs::id,idXCh);
				XMLStringUtil::Release(idXCh);
				parentNode->appendChild(newTask);
				mDOMTargetNodes.insert(LDOMElements::value_type(target,newTask));
			}
		}
		else if (type == "weights") {
			DOMElement* newWeights = pResultsDoc->createElement(XMLResultsDefs::weights);
			//set the ID attribute
			XMLCh* idXCh = XMLStringUtil::Str2XML(idStr);
			newWeights->setAttribute(XMLResultsDefs::id,idXCh);
			XMLStringUtil::Release(idXCh);
			//add the node to the DOM
			parentNode->appendChild(newWeights);
			mDOMTargetNodes.insert(LDOMElements::value_type(target,newWeights));
		}
		else if (type == "synapses") {
			DOMElement* newSynapses = pResultsDoc->createElement(XMLResultsDefs::synapses);
			//set the ID attribute
			XMLCh* idXCh = XMLStringUtil::Str2XML(idStr);
			newSynapses->setAttribute(XMLResultsDefs::id,idXCh);
			XMLStringUtil::Release(idXCh);
			//add the node to the DOM
			parentNode->appendChild(newSynapses);
			mDOMTargetNodes.insert(LDOMElements::value_type(target,newSynapses));
		}
		else {
			DOMElement* newValues = pResultsDoc->createElement(XMLResultsDefs::values);
			//set the type attribute
			XMLCh* typeXCh = XMLStringUtil::Str2XML(type);
			newValues->setAttribute(XMLResultsDefs::type,typeXCh);
			XMLStringUtil::Release(typeXCh);
			//set the ID attribute (if there is one)
			if (!idStr.empty()) {
				XMLCh* idXCh = XMLStringUtil::Str2XML(idStr);
				newValues->setAttribute(XMLResultsDefs::id,idXCh);
				XMLStringUtil::Release(idXCh);
			}
			//add the node to the DOM
			parentNode->appendChild(newValues);
			mDOMTargetNodes.insert(LDOMElements::value_type(target,newValues));
		}
	}
}

void CXMLReport::Initialise(void* target,CExTimeInfo* eTI)
{	
	if (mDOMCycleNodes.find(target) == mDOMCycleNodes.end()) {
		DOMElement* newCycle = pResultsDoc->createElement(XMLResultsDefs::cycle);
		mDOMTargetNodes[target]->appendChild(newCycle);
		XMLCh buf[10];
		XMLStringUtil::Int2XML(eTI->GetConfig(),buf,10);
		newCycle->setAttribute(XMLResultsDefs::config,buf);
		XMLStringUtil::Int2XML(eTI->GetRun(),buf,10);
		newCycle->setAttribute(XMLResultsDefs::run,buf);
		mDOMCycleNodes.insert(LDOMElements::value_type(target,newCycle));
	}
}

void CXMLReport::Write(size_t prec,SubArrayIteratorConst* v,CExTimeInfo* eTI)
{
	ost.precision(prec);
	const size_t iteration = eTI->GetGlobalIteration();
	const size_t step = eTI->GetIntegration();
	XMLCh buf[10];
	DOMElement* newNode = pResultsDoc->createElement(XMLResultsDefs::v);
	mDOMCycleNodes[v]->appendChild(newNode);
	XMLStringUtil::Int2XML(iteration,buf,10);
	newNode->setAttribute(XMLResultsDefs::i,buf);
	if (step < std::numeric_limits<size_t>::max()) {
		XMLStringUtil::Int2XML(step,buf,10);
		newNode->setAttribute(XMLResultsDefs::s,buf);
	}
	ost << *v << '\0';
	XMLCh* tempXCh = XMLStringUtil::Str2XML(ost.str());
	newNode->setTextContent(tempXCh);
	XMLStringUtil::Release(tempXCh);
	ost.seekp(0);
}

void CXMLReport::Write(size_t prec,SliceIteratorConst* v,CExTimeInfo* eTI)
{
	ost.precision(prec);
	const size_t iteration = eTI->GetGlobalIteration();
	const size_t step = eTI->GetIntegration();
	XMLCh buf[10];
	DOMElement* newV = pResultsDoc->createElement(XMLResultsDefs::v);
	mDOMCycleNodes[v]->appendChild(newV);
	XMLStringUtil::Int2XML(iteration,buf,10);
	newV->setAttribute(XMLResultsDefs::i,buf);
	if (step < std::numeric_limits<size_t>::max()) {
		XMLStringUtil::Int2XML(step,buf,10);
		newV->setAttribute(XMLResultsDefs::s,buf);
	}
	ost << *v << '\0';
	XMLCh* tempXCh = XMLStringUtil::Str2XML(ost.str());
	newV->setTextContent(tempXCh);
	XMLStringUtil::Release(tempXCh);
	ost.seekp(0);
}

void CXMLReport::Write(size_t prec,IndirectIteratorConst* v,CExTimeInfo* eTI)
{
	ost.precision(prec);
	const size_t iteration = eTI->GetGlobalIteration();
	const size_t step = eTI->GetIntegration();
	XMLCh buf[10];
	DOMElement* newV = pResultsDoc->createElement(XMLResultsDefs::v);
	mDOMCycleNodes[v]->appendChild(newV);
	XMLStringUtil::Int2XML(iteration,buf,10);
	newV->setAttribute(XMLResultsDefs::i,buf);
	if (step < std::numeric_limits<size_t>::max()) {
		XMLStringUtil::Int2XML(step,buf,10);
		newV->setAttribute(XMLResultsDefs::s,buf);
	}
	ost << *v << '\0';
	XMLCh* tempXCh = XMLStringUtil::Str2XML(ost.str());
	newV->setTextContent(tempXCh);
	XMLStringUtil::Release(tempXCh);
	ost.seekp(0);
}

void CXMLReport::Write(size_t prec,MultipleSubArrayIteratorConst* v,CExTimeInfo* eTI)
{
	ost.precision(prec);
	const size_t iteration = eTI->GetGlobalIteration();
	const size_t step = eTI->GetIntegration();
	XMLCh buf[10];
	DOMElement* newV = pResultsDoc->createElement(XMLResultsDefs::v);
	mDOMCycleNodes[v]->appendChild(newV);
	XMLStringUtil::Int2XML(iteration,buf,10);
	newV->setAttribute(XMLResultsDefs::i,buf);
	if (step < std::numeric_limits<size_t>::max()) {
		XMLStringUtil::Int2XML(step,buf,10);
		newV->setAttribute(XMLResultsDefs::s,buf);
	}
	ost << *v << '\0';
	XMLCh* tempXCh = XMLStringUtil::Str2XML(ost.str());
	newV->setTextContent(tempXCh);
	XMLStringUtil::Release(tempXCh);
	ost.seekp(0);
}

void CXMLReport::Write(size_t prec,MatrixIteratorConst* v,CExTimeInfo* eTI,size_t type)
{
	ost.precision(prec);
	const size_t iteration = eTI->GetGlobalIteration();
	const size_t step = eTI->GetIntegration();
	XMLCh buf[10];
	DOMElement* newEl = 0;
	if (type == 0) {
		newEl = pResultsDoc->createElement(XMLResultsDefs::w);
		size_t nodes = v->columns();
		for(size_t j=0;j<nodes;++j) {
			DOMElement* newN = pResultsDoc->createElement(XMLResultsDefs::n);
			newEl->appendChild(newN);
			SubArrayIteratorConst colit = v->GetCol(j);
			ost << colit << '\0';
			XMLCh* tempXCh = XMLStringUtil::Str2XML(ost.str());
			newN->setTextContent(tempXCh);
			XMLStringUtil::Release(tempXCh);
			ost.seekp(0);
		}
	}
	else if (type == 1) {
		newEl = pResultsDoc->createElement(XMLResultsDefs::p);
		size_t rows = v->rows();
		for(size_t r=0;r<rows;++r) {
			DOMElement* newR = pResultsDoc->createElement(XMLResultsDefs::r);
			newEl->appendChild(newR);
			SliceIteratorConst rowit = v->GetRow(r);
			ost << rowit << '\0';
			XMLCh* tempXCh = XMLStringUtil::Str2XML(ost.str());
			newR->setTextContent(tempXCh);
			XMLStringUtil::Release(tempXCh);
			ost.seekp(0);
		}
	}
	mDOMCycleNodes[v]->appendChild(newEl);
	XMLStringUtil::Int2XML(iteration,buf,10);
	newEl->setAttribute(XMLResultsDefs::i,buf);
	if (step < std::numeric_limits<size_t>::max()) {
		XMLStringUtil::Int2XML(step,buf,10);
		newEl->setAttribute(XMLResultsDefs::s,buf);
	}
}

void CXMLReport::Write(size_t prec,SynapseWrapper* v,CExTimeInfo* eTI)
{
	ost.precision(prec);
	double mult = pow(10.0,static_cast<int>(prec));
	const size_t iteration = eTI->GetGlobalIteration();
	const size_t step = eTI->GetIntegration();
	XMLCh buf[10];
	DOMElement* newV = pResultsDoc->createElement(XMLResultsDefs::v);
	for(size_t j=0,nodes=v->nodes();j<nodes;++j) {
		DOMElement* newN = pResultsDoc->createElement(XMLResultsDefs::n);
		newV->appendChild(newN);
		for(size_t i=0,inputs=v->inputs();i<inputs;++i) {
			ost << std::setw(prec + 4) << static_cast<long>(((*v)(i,j))*mult)/mult;
		}
		ost << '\0';
		XMLCh* tempXCh = XMLStringUtil::Str2XML(ost.str());
		newN->setTextContent(tempXCh);
		XMLStringUtil::Release(tempXCh);
		ost.seekp(0);
	}
	mDOMCycleNodes[v]->appendChild(newV);
	XMLStringUtil::Int2XML(iteration,buf,10);
	newV->setAttribute(XMLResultsDefs::i,buf);
	if (step < std::numeric_limits<size_t>::max()) {
		XMLStringUtil::Int2XML(step,buf,10);
		newV->setAttribute(XMLResultsDefs::s,buf);
	}
}

void CXMLReport::Finalise(void*,CExTimeInfo*)
{
	for(LDOMElements::iterator it = mDOMCycleNodes.begin(),ite = mDOMCycleNodes.end();it != ite;++it) {
		DOMElement* thisEl = (*it).second;
		if (thisEl) {
			DOMNodeList* pDOMList = thisEl->getElementsByTagName(XMLResultsDefs::v);
			if (!pDOMList->getLength()) 
				pDOMList = thisEl->getElementsByTagName(XMLResultsDefs::w);
			if (!pDOMList->getLength()) 
				pDOMList = thisEl->getElementsByTagName(XMLResultsDefs::p);
			if (!pDOMList->getLength()) {
				DOMNode* emptyNode = mDOMTargetNodes[(*it).first]->removeChild(thisEl);
				emptyNode->release();
				(*it).second = 0;
			}
		}
	}
	mDOMCycleNodes.clear();
}

void CXMLReport::SetSink(void* ps)
{
	pOut = static_cast<XERCES_CPP_NAMESPACE::XMLFormatTarget*>(ps);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CPatternSetReport::CPatternSetReport() : pOut(0),pPatternSet(0),ost()
{
	XMLPlatformUtils::Initialize();
	ost.setf(std::ios_base::left);
	//construct a DOM document that will hold the data for this particular reporter
	//get the implementation
	DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(XMLResultsDefs::LS);
	//create the document
	pPatternSet = impl->createDocument(0,XMLStrDefs::patternSet,0);
	DOMElement* docEl = pPatternSet->getDocumentElement();
	docEl->setAttribute(XMLSchemaNames::xmlns,XMLSchemaNames::CORINETSetup);
	docEl->setAttribute(XMLSchemaNames::xsi,XMLSchemaNames::XSI);
}
	
CPatternSetReport::~CPatternSetReport()
{
	//construct the DOMWriter
	DOMImplementationLS* impl = DOMImplementationRegistry::getDOMImplementation(XMLResultsDefs::LS);
	DOMWriter* writer = impl->createDOMWriter();
	writer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint,true);
	writer->writeNode(pOut,*(pPatternSet->getDocumentElement()));
	writer->release();
	pPatternSet->release();
	XMLPlatformUtils::Terminate();
}
	
void CPatternSetReport::Write(size_t prec,MatrixIteratorConst* v,CExTimeInfo* eTI,size_t type)
{
	ost.precision(prec);
	const size_t pattern = eTI->GetRun();
	XMLCh buf[10];
	if (pattern == 0) {	
		XMLStringUtil::Int2XML(v->columns(),buf,10);
		pPatternSet->getDocumentElement()->setAttribute(XMLStrDefs::columns,buf);
		XMLStringUtil::Int2XML(v->rows(),buf,10);
		pPatternSet->getDocumentElement()->setAttribute(XMLStrDefs::rows,buf);
	}
	DOMElement* newEl = 0;
	if (type == 1) {
		newEl = pPatternSet->createElement(XMLStrDefs::p);
		size_t rows = v->rows();
		for(size_t r=0;r<rows;++r) {
			DOMElement* newR = pPatternSet->createElement(XMLResultsDefs::r);
			newEl->appendChild(newR);
			SliceIteratorConst rowit = v->GetRow(r);
			ost << rowit << '\0';
			XMLCh* tempXCh = XMLStringUtil::Str2XML(ost.str());
			newR->setTextContent(tempXCh);
			XMLStringUtil::Release(tempXCh);
			ost.seekp(0);
		}
	}
	pPatternSet->getDocumentElement()->appendChild(newEl);
}
	
void CPatternSetReport::SetSink(void* ps)
{
	pOut = static_cast<XERCES_CPP_NAMESPACE::XMLFormatTarget*>(ps);
}

} //end namespace CORINET
