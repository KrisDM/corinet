/*********************************************************************************************
 * Name      :  ConcreteReports.h
 *
 * Purpose   :  Functionality for writing results in a certain format, currently either text
 *				or XML. 
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

#include <Event/Impl/ReportImpl.h>
#include <vector>
#include <map>
#include <ostream>
#include <sstream>
#include <xercesc/util/XercesDefs.hpp>

#ifndef CORINET_REPORTCONCR
#define CORINET_REPORTCONCR

namespace XERCES_CPP_NAMESPACE {
	class DOMElement;
	class DOMDocument;
	class XMLFormatTarget;
}

namespace CORINET {

class CTextReport : public CReportImpl {//writing results to a text file
	std::ostream* pOut;
public:
	CTextReport();
	virtual ~CTextReport();
	void Initialise(void*,CExTimeInfo*);
	void Write(size_t,SubArrayIteratorConst*,CExTimeInfo*);
	void Write(size_t,SliceIteratorConst*,CExTimeInfo*);
	void Write(size_t,IndirectIteratorConst*,CExTimeInfo*);
	void Write(size_t,MultipleSubArrayIteratorConst*,CExTimeInfo*);
	void Write(size_t,MatrixIteratorConst*,CExTimeInfo*,size_t =0);
	void Write(size_t,SynapseWrapper*,CExTimeInfo*);
	void Finalise(void*,CExTimeInfo*);
	void SetSink(void*);
};

class CXMLReport : public CReportImpl {//writing results to an XML DOM tree
	typedef std::map<void*,XERCES_CPP_NAMESPACE::DOMElement*> LDOMElements;
	XERCES_CPP_NAMESPACE::XMLFormatTarget* pOut;
	XERCES_CPP_NAMESPACE::DOMDocument* pResultsDoc;
	LDOMElements mDOMTargetNodes;
	LDOMElements mDOMCycleNodes;
	std::ostringstream ost;
public:
	CXMLReport();
	virtual ~CXMLReport();
	void Initialise(void*,CExTimeInfo*);
	void Write(size_t,SubArrayIteratorConst*,CExTimeInfo*);
	void Write(size_t,SliceIteratorConst*,CExTimeInfo*);
	void Write(size_t,IndirectIteratorConst*,CExTimeInfo*);
	void Write(size_t,MultipleSubArrayIteratorConst*,CExTimeInfo*);
	void Write(size_t,MatrixIteratorConst*,CExTimeInfo*,size_t =0);
	void Write(size_t,SynapseWrapper*,CExTimeInfo*);
	void Finalise(void*,CExTimeInfo*);
	void SetSink(void*);

	void MakeTopLevelNode(const std::string&,const std::string&);
	void MakeTargetNode(void*,const std::string&,const std::string&,const std::string&);	
};

class CPatternSetReport : public CReportImpl {//writing a patternSet to an XML DOM tree
	XERCES_CPP_NAMESPACE::XMLFormatTarget* pOut;
	XERCES_CPP_NAMESPACE::DOMDocument* pPatternSet;
	std::ostringstream ost;
public:
	CPatternSetReport();
	virtual ~CPatternSetReport();
	void Write(size_t,MatrixIteratorConst*,CExTimeInfo*,size_t =0);
	void SetSink(void*);

	void Initialise(void*,CExTimeInfo*) {}
	void Write(size_t,SubArrayIteratorConst*,CExTimeInfo*) {}
	void Write(size_t,SliceIteratorConst*,CExTimeInfo*) {}
	void Write(size_t,IndirectIteratorConst*,CExTimeInfo*) {}
	void Write(size_t,MultipleSubArrayIteratorConst*,CExTimeInfo*) {}
	void Write(size_t,SynapseWrapper*,CExTimeInfo*) {}
	void Finalise(void*,CExTimeInfo*) {}
};
	

} //end namespace CORINET

#endif //CORINET_REPORTCONCR
