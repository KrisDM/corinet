/*********************************************************************************************
 * Name      :  BuilderImpl.h
 *
 * Purpose   :  Implementations of builders. 
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

#ifndef CORINET_BUILDERIMPL
#define CORINET_BUILDERIMPL

#include <Setup/Builder.h>

namespace CORINET {
	struct SEngineMaker;
	class CEngine;
	class CStatus;
	class CCommonBuilder;
	class CNetBuilder;
	class CTaskBuilder;
	class CEventBuilder;
	class CExecutionBuilder;

class CBuilderEngineV1 : public CBuilder {
	size_t mExecutionCounter;
	SEngineMaker* pEngineMaker;
	CEngine* pEngine;
	CStatus* pStatus;
	CCommonBuilder* pCommonBuilder;
	CNetBuilder* pNetBuilder;
	CTaskBuilder* pTaskBuilder;
	CEventBuilder* pEventBuilder;
	CExecutionBuilder* pExecutionBuilder;
public:
	CBuilderEngineV1(SEngineMaker*);
	virtual ~CBuilderEngineV1();
	//create functions
	CEngine* CreateEngine(CMessageHandler*);
	CExecution* CreateExecution();
	
	//cleanup functions
	void ReleaseExecution();
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_BUILDER

