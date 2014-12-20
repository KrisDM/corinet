/*********************************************************************************************
 * Name      :  EventImpl.h
 *
 * Purpose   :  Implementation class of events.
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


#ifndef CORINET_EVENTIMPL
#define CORINET_EVENTIMPL

#include <Event/Event.h>
#include <vector>
#include <string>

namespace CORINET {
	class FCondition;
	class CAction;

enum ConditionVar {
	COND_CONFIG,
	COND_RUN,
	COND_ENTRY,
	COND_ITERATION,
	COND_INTEGRATION
};

class CEventImpl : public CEvent {
public:
	virtual ~CEventImpl();

	virtual void AddCondition(const std::string&,FCondition*);
	virtual void AddAction(CAction*);
};

} //end namespace CORINET	

#endif //CORINET_EVENTIMPL

