/*********************************************************************************************
 * Name      :  ExTimeInfoRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of CExTimeInfo with
 *				the factory manager for the abstract CExTimeInfo type. Since an ExTimeInfo is
 *				always used in conjuction with a CExecution object, the name for registration
 *				in this case is the corresponding name for the concrete CExecution class. 
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

#include <Engine/Concr/ConcreteExTimeInfo.h>
#include <Util/Factory.h>

namespace CORINET {

GET_REGISTER(CExTimeInfo)

REGISTER_CLASS_2(CExTimeInfo,CExTimeInfoV1,executionV1)
REGISTER_CLASS_2(CExTimeInfo,CExTimeInfoPatternGenerator,patternGenerator)
REGISTER_CLASS_2(CExTimeInfo,CExTimeInfoRandTest,randTest)

} //end namespace CORINET
