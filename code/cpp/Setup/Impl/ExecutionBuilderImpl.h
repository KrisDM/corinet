/*********************************************************************************************
 * Name      :  ExecutionBuilderImpl.h
 *
 * Purpose   :  Create executions and cleanup after use. Implementation class. 
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

#ifndef CORINET_EXECUTIONBUILDERIMPL
#define CORINET_EXECUTIONBUILDERIMPL

#include <Setup/ExecutionBuilder.h>
#include <map>

namespace CORINET {
	class CCommonBuilder;
	class CNetBuilder;
	class CTaskBuilder;
	class CEventBuilder;
	struct SLoopElementMaker;
	struct SLoopMaker;
	struct SLoopsMaker;
	class CLoopElement;
	class CLoop;
	class CLoops;
	class CExTimeInfo;

class CExecutionBuilderImpl : public CExecutionBuilder {
	typedef std::map<SLoopElementMaker*,CLoopElement*> LLoopElements;
	typedef std::map<SLoopMaker*,CLoop*> LLoops;
	typedef std::map<SExecutionElementMaker*,CExecutionElement*> LExecutionElements;

	LLoopElements mLoopElements;
	LLoops mLoops;
	LExecutionElements mExecutionElements;
	CLoops* pLoops;
	SExecutionMaker* pExecutionMaker;
	CExecution* pExecution;
	CExTimeInfo* pExTimeInfo;

	std::vector<void*> mTempObject;
	std::vector<std::pair<std::string,std::string> > mIDs;

	CCommonBuilder* pCommonBuilder;
	CNetBuilder* pNetBuilder;
	CTaskBuilder* pTaskBuilder;
	CEventBuilder* pEventBuilder;
public:
	CExecutionBuilderImpl();
	virtual ~CExecutionBuilderImpl();

	//initialisation functions
	void SetCommonBuilder(CCommonBuilder*);
	void SetNetBuilder(CNetBuilder*);
	void SetTaskBuilder(CTaskBuilder*);
	void SetEventBuilder(CEventBuilder*);

	//create function
	CExecution* Create(SExecutionMaker*);
	CExecutionElement* Create(SExecutionElementMaker*);
	CLoops* Create(SLoopsMaker*);
	CLoop* Create(SLoopMaker*);
	CLoopElement* Create(SLoopElementMaker*);

	//access functions
	CExecution* Get(SExecutionMaker*);
	CExecutionElement* Get(SExecutionElementMaker*);
	std::vector<void*>& GetVoid(SMaker*);
	const std::vector<std::pair<std::string,std::string> >& GetTopLevelIDs();
	
	//cleanup function
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_EXECUTIONBUILDERIMPL

