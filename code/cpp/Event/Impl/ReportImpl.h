/*********************************************************************************************
 * Name      :  ReportImpl.h
 *
 * Purpose   :  Implementation class for report writers.
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

#ifndef CORINET_REPORTIMPL
#define CORINET_REPORTIMPL

#include <Event/Report.h>

namespace CORINET {

class CReportImpl : public CReport {
public:
	virtual ~CReportImpl();
	virtual void SetSink(void*);
	virtual void MakeTopLevelNode(const std::string&,const std::string&);
	virtual void MakeTargetNode(void*,const std::string&,const std::string&,const std::string&);
};

} //end namespace CORINET
	
#endif //CORINET_REPORTIMPL
