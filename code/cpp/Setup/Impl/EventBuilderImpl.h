/*********************************************************************************************
 * Name      :  EventBuilderImpl.h
 *
 * Purpose   :  Create events and cleanup after use. Implementation class.
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

#ifndef CORINET_EVENTBUILDERIMPL
#define CORINET_EVENTBUILDERIMPL

#include <Setup/EventBuilder.h>
#include <map>

namespace CORINET {
	class FOperation;
	class FCondition;
	class CReport;
	class CAction;
	class CEvent;
	struct SOperationMaker;
	struct SConditionMaker;
	struct SReportMaker;
	struct SActionMaker;
	struct SEventMaker;
	class CCommonBuilder;
	class CNetBuilder;
	class CTaskBuilder;
	class CExecutionBuilder;

class CEventBuilderImpl : public CEventBuilder {
	typedef std::map<SOperationMaker*,FOperation*> LOperations;
	typedef std::map<SConditionMaker*,FCondition*> LConditions;
	typedef std::map<SReportMaker*,CReport*> LReports;
	typedef std::map<SActionMaker*,CAction*> LActions;
	typedef std::map<SEventMaker*,CEvent*> LEvents;
	LOperations mOperations;
	LConditions mConditions;
	LReports mReports;
	LActions mActions;
	LEvents mEvents;

	CCommonBuilder* pCommonBuilder;
	CNetBuilder* pNetBuilder;
	CTaskBuilder* pTaskBuilder;
	CExecutionBuilder* pExecutionBuilder;
public:
	CEventBuilderImpl();
	virtual ~CEventBuilderImpl();

	//initialisation functions
	void SetCommonBuilder(CCommonBuilder*);
	void SetNetBuilder(CNetBuilder*);
	void SetTaskBuilder(CTaskBuilder*);
	void SetExecutionBuilder(CExecutionBuilder*);

	//create function
	CEvent* Create(SEventMaker*);
	CAction* Create(SActionMaker*);
	CReport* Create(SReportMaker*);
	FCondition* Create(SConditionMaker*);
	FOperation* Create(SOperationMaker*);

	//access function
	CEvent* Get(SEventMaker*);
	CReport* Get(SReportMaker*);
	
	//cleanup function
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_EVENTBUILDERIMPL

