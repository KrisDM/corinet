/*********************************************************************************************
 * Name      :  BuilderImpl.cpp
 *
 * Purpose   :  Create execution engine, networks, tasks and events. 
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

#include "BuilderImpl.h"
#include "CommonBuilderImpl.h"
#include "NetBuilderImpl.h"
#include "TaskBuilderImpl.h"
#include "EventBuilderImpl.h"
#include "ExecutionBuilderImpl.h"
#include <Util/Factory.h>
#include <Engine/Impl/EngineImpl.h>
#include <Engine/Impl/StatusImpl.h>
#include <Setup/Makers.h>
#include <Client/MessageHandler.h>

namespace CORINET {

CBuilderEngineV1::CBuilderEngineV1(SEngineMaker* em) : mExecutionCounter(0),pEngineMaker(em),pEngine(0),pStatus(0),
													   pCommonBuilder(0),pNetBuilder(0),pTaskBuilder(0),
													   pEventBuilder(0),pExecutionBuilder(0)
{
	pCommonBuilder = new CCommonBuilderImpl();
	pNetBuilder = new CNetBuilderImpl();
	pTaskBuilder = new CTaskBuilderImpl();
	pEventBuilder = new CEventBuilderImpl();
	pExecutionBuilder = new CExecutionBuilderImpl();
	static_cast<CNetBuilderImpl*>(pNetBuilder)->SetCommonBuilder(pCommonBuilder);
	static_cast<CTaskBuilderImpl*>(pTaskBuilder)->SetCommonBuilder(pCommonBuilder);
	static_cast<CEventBuilderImpl*>(pEventBuilder)->SetCommonBuilder(pCommonBuilder);
	static_cast<CEventBuilderImpl*>(pEventBuilder)->SetNetBuilder(pNetBuilder);
	static_cast<CEventBuilderImpl*>(pEventBuilder)->SetTaskBuilder(pTaskBuilder);
	static_cast<CEventBuilderImpl*>(pEventBuilder)->SetExecutionBuilder(pExecutionBuilder);
	static_cast<CExecutionBuilderImpl*>(pExecutionBuilder)->SetCommonBuilder(pCommonBuilder);
	static_cast<CExecutionBuilderImpl*>(pExecutionBuilder)->SetNetBuilder(pNetBuilder);
	static_cast<CExecutionBuilderImpl*>(pExecutionBuilder)->SetTaskBuilder(pTaskBuilder);
	static_cast<CExecutionBuilderImpl*>(pExecutionBuilder)->SetEventBuilder(pEventBuilder);
}

CBuilderEngineV1::~CBuilderEngineV1()
{
	ReleaseAll();
}
	
CEngine* CBuilderEngineV1::CreateEngine(CMessageHandler* pmes)
{
	if (!pEngine) {
		mExecutionCounter = 0;
		pEngine = CFactoryManager<CEngine>::CreateInstance(pEngineMaker->type);

		if (!pEngine) {
			throw ECreation("engine",pEngineMaker->type);
		}

		if (pEngineMaker->statusMaker) {
			pStatus = CFactoryManager<CStatus>::CreateInstance(pEngineMaker->statusMaker->type);
			
			if (!pStatus) {
				throw ECreation("status",pEngineMaker->statusMaker->type);
			}

			static_cast<CStatusImpl*>(pStatus)->SetTotalExecutions(pEngineMaker->statusMaker->numExecutions);
			static_cast<CStatusImpl*>(pStatus)->SetMessageHandler(pmes);

			static_cast<CEngineImpl*>(pEngine)->SetStatus(pStatus);
		}

	}
	return pEngine;
}
	
CExecution* CBuilderEngineV1::CreateExecution()
{
	CExecution* pExecution = 0;
	if (mExecutionCounter < pEngineMaker->executionMakers.size()) {
		pExecution = pExecutionBuilder->Create(pEngineMaker->executionMakers[mExecutionCounter++]);
	}
	return pExecution;
}
	
void CBuilderEngineV1::ReleaseExecution()
{
	if (pExecutionBuilder)
		pExecutionBuilder->ReleaseAll();
	if (pEventBuilder)
		pEventBuilder->ReleaseAll();
	if (pTaskBuilder)
		pTaskBuilder->ReleaseAll();
	if (pNetBuilder)
		pNetBuilder->ReleaseAll();
	if (pCommonBuilder)
		pCommonBuilder->ReleaseAll();
}
	
void CBuilderEngineV1::ReleaseAll()
{
	ReleaseExecution();
	if (pEngine) {
		delete pEngine;
		pEngine = 0;
	}
	if (pStatus) {
		delete pStatus;
		pStatus = 0;
	}
	if (pCommonBuilder) {
		delete pCommonBuilder;
		pCommonBuilder = 0;
	}
	if (pNetBuilder) {
		delete pNetBuilder;
		pNetBuilder = 0;
	}
	if (pTaskBuilder) {
		delete pTaskBuilder;
		pTaskBuilder = 0;
	}
	if (pEventBuilder) {
		delete pEventBuilder;
		pEventBuilder = 0;
	}
	if (pExecutionBuilder) {
		delete pExecutionBuilder;
		pExecutionBuilder = 0;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //end namespace CORINET


