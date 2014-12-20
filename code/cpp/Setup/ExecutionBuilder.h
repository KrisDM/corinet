/*********************************************************************************************
 * Name      :  ExecutionBuilder.h
 *
 * Purpose   :  Create executions and cleanup after use. 
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

#ifndef CORINET_EXECUTIONBUILDER
#define CORINET_EXECUTIONBUILDER

#include <Platform/Platform.h>
#include <string>
#include <vector>

namespace CORINET {
	class CExecution;
	class CExecutionElement;
	struct SExecutionMaker;
	struct SExecutionElementMaker;
	struct SMaker;

class CExecutionBuilder {
public:
	virtual ~CExecutionBuilder() {}

	//create function
	virtual CExecution* Create(SExecutionMaker*) =0;

	//access function
	virtual CExecution* Get(SExecutionMaker*) =0;
	virtual CExecutionElement* Get(SExecutionElementMaker*) =0;
	virtual std::vector<void*>& GetVoid(SMaker*) =0;

	virtual const std::vector<std::pair<std::string,std::string> >& GetTopLevelIDs() =0;
	
	//cleanup function
	virtual void ReleaseAll() =0;
};

} //end namespace CORINET

#endif //CORINET_EXECUTIONBUILDER

