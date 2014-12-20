/*********************************************************************************************
 * Name      :  TaskBuilderImpl.h
 *
 * Purpose   :  Create tasks and cleanup after use. This is the implementation class. 
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

#ifndef CORINET_TASKBUILDERIMPL
#define CORINET_TASKBUILDERIMPL

#include <Setup/TaskBuilder.h>
#include <map>
#include <list>
#include <valarray>

namespace CORINET {
	struct SDataSourceMaker;
	struct SInsertMaker;
	struct STaskMaker;
	class CDataSource;
	class FInsert;
	class CTask;
	class CCommonBuilder;

class CTaskBuilderImpl : public CTaskBuilder {
	typedef std::map<SDataSourceMaker*,CDataSource*> LDataSources;
	typedef std::map<SInsertMaker*,FInsert*> LInserts;
	typedef std::map<STaskMaker*,CTask*> LTasks;
	typedef std::map<CTask*,std::string> LTaskIDs;
	typedef std::map<void*,std::list<CTask*> > LParents;
	LDataSources mDataSources;
	LInserts mInserts;
	LTasks mTasks;
	LTaskIDs mTaskIDs;
	LParents mParents;

	std::vector<CTask*> mTempParent;
	std::vector<void*> mTempObject;

	CCommonBuilder* pCommonBuilder;

	void AddParent(void*,CTask*);
public:
	CTaskBuilderImpl();
	virtual ~CTaskBuilderImpl();

	//initialise functions
	void SetCommonBuilder(CCommonBuilder*);

	//create function
	CTask* Create(STaskMaker*,CTask* =0);
	FInsert* Create(SInsertMaker*,CTask*);
	CDataSource* Create(SDataSourceMaker*,CTask*);

	//access function
	CTask* Get(STaskMaker*);
	std::vector<void*>& GetVoid(SMaker*);
	std::vector<CTask*>& GetParents(void*);
	const std::string& GetTaskID(CTask* const);
	
	//cleanup function
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_TASKBUILDERIMPL

