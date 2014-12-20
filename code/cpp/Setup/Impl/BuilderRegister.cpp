/*********************************************************************************************
 * Name      :  BuilderRegister.cpp
 *
 * Purpose   :  Creates a suitable builder depending on the type of engine.
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

#include <Setup/BuilderRegister.h>
#include <Setup/Builder.h>
#include <Setup/Makers.h>
#include "BuilderImpl.h"

namespace CORINET {

CBuilderRegister::~CBuilderRegister()
{

}

CBuilder* CBuilderRegister::GetBuilder(SEngineMaker* em)
{
	CBuilder* thisBuilder = 0;
	if (em->type == "engineV1") {
		thisBuilder = new CBuilderEngineV1(em);
	}

	return thisBuilder;
}

} //end namespace CORINET


