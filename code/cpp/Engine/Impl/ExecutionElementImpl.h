/*********************************************************************************************
 * Name      :  ExecutionElementImpl.h
 *
 * Purpose   :  Implementation class for executions.
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

#ifndef CORINET_EXECUTIONELEMENTIMPL
#define CORINET_EXECUTIONELEMENTIMPL

#include <Engine/ExecutionElement.h>
#include <valarray>
#include <string>

namespace CORINET {
	class CTask;
	class CEvent;
	
class CExecutionElementImpl : public CExecutionElement {
public:
	virtual ~CExecutionElementImpl();

	virtual void SetTimes(const std::valarray<size_t>*);
	virtual void AddExElement(CExecutionElement*);
	virtual void AddTask(CTask*);
	virtual void AddEvent(const std::string&,CEvent*);
};

} //end namespace CORINET

#endif //CORINET_EXECUTEELEMENTIMPL

