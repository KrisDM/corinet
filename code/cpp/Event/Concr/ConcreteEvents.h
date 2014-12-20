/*********************************************************************************************
 * Name      :  ConcreteEvents.h
 *
 * Purpose   :  Concrete types of event handlers.
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

#ifndef CORINET_EVENTCONCR
#define CORINET_EVENTCONCR

#include <Event/Impl/EventImpl.h>
#include <map>
#include <vector>
#include <string>

namespace CORINET {

class CEventModel1 : public CEventImpl {
	typedef std::multimap<ConditionVar,FCondition*> LConditions;
	LConditions mConditions;
	std::vector<CAction*> mActions;
public:
	CEventModel1();
	virtual ~CEventModel1();
	bool CheckConditions(CExTimeInfo*);
	void Initialise(CExTimeInfo*);
	void Handle(CExTimeInfo*);
	void Finalise(CExTimeInfo*);

	void AddCondition(const std::string&,FCondition*);
	void AddAction(CAction*);
};

} //end namespace CORINET	

#endif //CORINET_EVENTCONCR

