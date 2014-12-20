/*********************************************************************************************
 * Name      :  Task.h
 *
 * Purpose   :  Abstract interface for tasks.
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

#ifndef CORINET_TASK
#define CORINET_TASK

#include <Util/ParamInterface.h>
#include <string>

namespace CORINET {
	class SubArrayIteratorConst;
	class SubArrayIterator;
	class MatrixIteratorConst;
	class MatrixIterator;

struct ETask {//exceptions to be thrown during task creation, checking things that can't be checked anywhere else
	std::string message;
	ETask(const char* m) {message = m;}
};

class CTask : public CParamInterface {
public:
	virtual ~CTask() {}

	//interface for engine
	virtual void Initialise() =0;
	virtual void Finalise() =0;
	virtual void Generate(bool) =0;
	virtual void Seed(size_t) =0;
	
	//access functions for event handlers etc.
	virtual SubArrayIteratorConst* GetValuesConst() =0;
	virtual SubArrayIterator* GetValues() =0;
	virtual MatrixIteratorConst* GetPatternConst() =0;
	virtual MatrixIterator* GetPattern() =0;
};

} //end namespace CORINET

#endif //CORINET_TASK
