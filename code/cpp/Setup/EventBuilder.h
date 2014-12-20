/*********************************************************************************************
 * Name      :  EventBuilder.h
 *
 * Purpose   :  Create events and cleanup after use.
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

#ifndef CORINET_EVENTBUILDER
#define CORINET_EVENTBUILDER

#include <Platform/Platform.h>

namespace CORINET {
	class CEvent;
	class CReport;
	struct SEventMaker;
	struct SReportMaker;

class CEventBuilder {
public:
	virtual ~CEventBuilder() {}

	//create function
	virtual CEvent* Create(SEventMaker*) =0;
	virtual CReport* Create(SReportMaker*) =0;

	//access function
	virtual CEvent* Get(SEventMaker*) =0;
	virtual CReport* Get(SReportMaker*) =0;
	
	//cleanup function
	virtual void ReleaseAll() =0;
};

} //end namespace CORINET

#endif //CORINET_EVENTBUILDER

