/*********************************************************************************************
 * Name      :  TaskBuilder.h
 *
 * Purpose   :  Create tasks and cleanup after use. 
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

#ifndef CORINET_TASKBUILDER
#define CORINET_TASKBUILDER

#include <Platform/Platform.h>
#include <string>
#include <vector>

namespace CORINET {
	class CTask;
	struct STaskMaker;
	struct SMaker;

class CTaskBuilder {
public:
	virtual ~CTaskBuilder() {}

	//create function
	virtual CTask* Create(STaskMaker*,CTask* =0) =0;

	//access function
	virtual CTask* Get(STaskMaker*) =0;
	virtual std::vector<void*>& GetVoid(SMaker*) =0;
	virtual std::vector<CTask*>& GetParents(void*) =0;
	virtual const std::string& GetTaskID(CTask* const) =0;
	
	//cleanup function
	virtual void ReleaseAll() =0;
};

} //end namespace CORINET

#endif //CORINET_TASKBUILDER

