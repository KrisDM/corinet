/*********************************************************************************************
 * Name      :  TaskBuilderImpl.cpp
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

#include "TaskBuilderImpl.h"
#include <Task/Impl/TaskImpl.h>
#include <Task/Impl/DataSourceImpl.h>
#include <Task/Impl/InsertImpl.h>
#include <Util/Factory.h>
#include <Setup/Makers.h>
#include <Setup/CommonBuilder.h>
#include <limits>

namespace CORINET {

CTaskBuilderImpl::CTaskBuilderImpl() : mDataSources(),mInserts(),mTasks(),mTaskIDs(),
										mParents(),mTempParent(),mTempObject(),pCommonBuilder(0)
{

}

CTaskBuilderImpl::~CTaskBuilderImpl()
{
	ReleaseAll();
}

void CTaskBuilderImpl::AddParent(void* object,CTask* parent)
{
	if (mParents.find(object) == mParents.end()) {
		mParents[object] = std::list<CTask*>();
		mParents[object].push_back(parent);
	}
	else {
		mParents[object].push_back(parent);
		mParents[object].sort();
		mParents[object].unique();
	}
}

void CTaskBuilderImpl::SetCommonBuilder(CCommonBuilder* pcb)
{
	pCommonBuilder = pcb;
}

CTask* CTaskBuilderImpl::Create(STaskMaker* ptm,CTask* pparent)
{
	if (mTasks.find(ptm) == mTasks.end()) {
		size_t sizeparams[5];
		sizeparams[0] = ptm->columns;
		sizeparams[1] = ptm->rows;
		sizeparams[2] = ptm->store;
		if (ptm->patterns)
			sizeparams[3] = ptm->patterns->size();
		else if (ptm->dataMaker)
			sizeparams[3] = ptm->dataMaker->patterns;
		else
			sizeparams[3] = 0;

		if (ptm->sampleMethod == "withoutReplacement")
			sizeparams[4] = 0;
		else 
			sizeparams[4] = 1;
		
		CTask* pt = CFactoryManager<CTask>::CreateInstance(ptm->type,sizeparams,ptm->taskParams);
		
		if (!pt)
			throw ECreation("task",ptm->type);
		else {
			mTasks.insert(LTasks::value_type(ptm,pt));
			mTaskIDs.insert(LTaskIDs::value_type(pt,ptm->idStr));
		}

		if (!pparent) //this is a freestanding task, it is its own parent
			pparent = pt;

		//add the patternset
		if (ptm->patterns) {
			static_cast<CTaskImpl*>(pt)->SetPatternSet(ptm->patterns);
		}
		//add the dataMaker
		if (ptm->dataMaker) {
			static_cast<CTaskImpl*>(pt)->SetDataSource(Create(ptm->dataMaker,pparent));
		}
		//add the inserts
		size_t sin = ptm->insertMakers.size();
		for(size_t i=0;i<sin;++i) {
			static_cast<CTaskImpl*>(pt)->AddInsert(Create(ptm->insertMakers[i],pparent));
		}

		//set the attenuation
		if (ptm->attenuationMaker) {
			FAttenuation* pat = pCommonBuilder->Create(ptm->attenuationMaker,sizeparams[0]*sizeparams[1]);
			static_cast<CTaskImpl*>(pt)->SetAttenuation(pat);
			AddParent(pat,pparent);
		}
		else
			static_cast<CTaskImpl*>(pt)->SetAttenuation(0);
		//set the noise function
		if (ptm->noiseMaker) {
			FNoiseFunction* pnf = pCommonBuilder->Create(ptm->noiseMaker,sizeparams[0]*sizeparams[1]);
			static_cast<CTaskImpl*>(pt)->SetNoise(pnf);
			AddParent(pnf,pparent);
		}
		else
			static_cast<CTaskImpl*>(pt)->SetNoise(0);
		//seed
		if (ptm->seed < std::numeric_limits<size_t>::max()) 
			pt->Seed(ptm->seed);

		AddParent(pt,pparent);
	}
	return mTasks[ptm];
}

FInsert* CTaskBuilderImpl::Create(SInsertMaker* pim,CTask* pparent)
{
	FInsert* pi = 0;
	if (mInserts.find(pim) == mInserts.end()) {
		size_t sizeparams[2];
		sizeparams[0] = pim->inColumn;
		sizeparams[1] = pim->inRow;

		pi = CFactoryManager<FInsert>::CreateInstance(pim->type,sizeparams,pim->insertParams);
		
		if (!pi)
			throw ECreation("insert",pim->type);
		else
			mInserts.insert(LInserts::value_type(pim,pi));

		//add the tasks
		const size_t st = pim->taskMakers.size();
		for(size_t i=0;i<st;++i) {
			static_cast<FInsertImpl*>(pi)->AddTask(static_cast<CTaskSimple*>(Create(pim->taskMakers[i],pparent)));
		}

		AddParent(pi,pparent);
	}
	else {
		pi = mInserts.find(pim)->second;
		AddParent(pi,pparent);
	}

	return pi;
}

CDataSource* CTaskBuilderImpl::Create(SDataSourceMaker* pdm,CTask* pparent)
{
	CDataSource* pd = 0;
	if (mDataSources.find(pdm) == mDataSources.end()) {
		//datasource processing here
		size_t sizeparams[3];
		sizeparams[0] = pdm->columns;
		sizeparams[1] = pdm->rows;
		sizeparams[2] = pdm->patterns;

		pd = CFactoryManager<CDataSource>::CreateInstance(pdm->type,sizeparams,pdm->sourceParams);
		
		if (!pd)
			throw ECreation("dataSource",pdm->type);
		else
			mDataSources.insert(LDataSources::value_type(pdm,pd));


		AddParent(pd,pparent);
	}
	else {
		pd = mDataSources.find(pdm)->second;
		AddParent(pd,pparent);
	}

	return pd;
}

CTask* CTaskBuilderImpl::Get(STaskMaker* tm)
{
	if (mTasks.find(tm) != mTasks.end()) 
		return mTasks[tm];
	else
		return 0;
}

std::vector<void*>& CTaskBuilderImpl::GetVoid(SMaker* maker)
{
	mTempObject.clear();
	if (maker->makerType == "task") {
		if (mTasks.find(static_cast<STaskMaker*>(maker)) != mTasks.end()) {
			mTempObject.push_back(mTasks[static_cast<STaskMaker*>(maker)]);
		}
	}
	else if (maker->makerType == "dataSource") {
		if (mDataSources.find(static_cast<SDataSourceMaker*>(maker)) != mDataSources.end()) {
			mTempObject.push_back(mDataSources[static_cast<SDataSourceMaker*>(maker)]);
		}
	}
	return mTempObject;
}
	
std::vector<CTask*>& CTaskBuilderImpl::GetParents(void* object)
{
	mTempParent.clear();
	if (mParents.find(object) != mParents.end()) {
		std::list<CTask*>& templist = mParents[object];
		for(std::list<CTask*>::iterator it=templist.begin(),ite=templist.end();it != ite;++it) {
			mTempParent.push_back(*it);
		}
	}
	return mTempParent;
}

const std::string& CTaskBuilderImpl::GetTaskID(CTask* const task)
{
	return mTaskIDs[task];
}
	
void CTaskBuilderImpl::ReleaseAll()
{
	for(LDataSources::iterator it1=mDataSources.begin(),ite1=mDataSources.end();it1 != ite1;++it1) {
		delete it1->second;
		it1->second = 0;
	}
	mDataSources.clear();
	for(LInserts::iterator it2=mInserts.begin(),ite2=mInserts.end();it2 != ite2;++it2) {
		delete it2->second;
		it2->second = 0;
	}
	mInserts.clear();
	for(LTasks::iterator it3=mTasks.begin(),ite3=mTasks.end();it3 != ite3;++it3) {
		delete it3->second;
		it3->second = 0;
	}
	mTasks.clear();
	mTaskIDs.clear();
}

} //end namespace CORINET

