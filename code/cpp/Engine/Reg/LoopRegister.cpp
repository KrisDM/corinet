/*********************************************************************************************
 * Name      :  LoopRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of loops and loopelements with
 *				the factory manager for the abstract basetypes.
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

#include <Engine/Concr/ConcreteLoops.h>
#include <Util/Factory.h>

namespace CORINET {

GET_REGISTER(CLoops)
GET_REGISTER(CLoop)
GET_REGISTER(CLoopElement)

REGISTER_CLASS_2(CLoops,CLoopsV1,loopsV1)
REGISTER_CLASS_2(CLoop,CLoopV1,loopV1)
REGISTER_CLASS_2(CLoopElement,CLoopVarV1,loopVarV1)
REGISTER_CLASS_2(CLoopElement,CLoopWeightsV1,loopWeightsV1)

} //end namespace CORINET
