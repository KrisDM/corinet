/*********************************************************************************************
 * Name      :  LoopImpl.cpp
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

#include "LoopImpl.h"

namespace CORINET {
	
CLoopsImpl::~CLoopsImpl() 
{
	
}

void CLoopsImpl::AddLoop(CLoop*)
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

CLoopImpl::~CLoopImpl() 
{
	
}

void CLoopImpl::AddLoopElement(CLoopElement*)
{
	
}

void CLoopImpl::SetSize(size_t)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

CLoopElementImpl::~CLoopElementImpl()
{

}

void CLoopElementImpl::AddValues(const std::valarray<double>*)
{

}

void CLoopElementImpl::AddTarget(void*,size_t)
{

}

} //end namespace CORINET
