/*********************************************************************************************
 * Name      :  LoopImpl.h
 *
 * Purpose   :  Functionality for running loops over multiple parameter or weight values.
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

#ifndef CORINET_LOOPIMPL
#define CORINET_LOOPIMPL

#include <Engine/Loop.h>
#include <valarray>

namespace CORINET {
	class CParamInterface;
	class FInitialisation;

class CLoopsImpl : public CLoops {
public:
	virtual ~CLoopsImpl();
	virtual void AddLoop(CLoop*);
};

class CLoopImpl : public CLoop {
public:
	virtual ~CLoopImpl();
	virtual void AddLoopElement(CLoopElement*);
	virtual void SetSize(size_t);
};

class CLoopElementImpl : public CLoopElement {
public:
	virtual ~CLoopElementImpl();
	virtual void AddValues(const std::valarray<double>*);
	virtual void AddTarget(void*,size_t);
};

} //end namespace CORINET

#endif //CORINET_LOOPIMPL

