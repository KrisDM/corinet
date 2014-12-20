/*********************************************************************************************
 * Name      :  Util.h
 *
 * Purpose   :  Various functions.
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

#include <Platform/Platform.h>
#include <Common/RandTest.h>
#include <cstdlib>

#ifndef CORINET_UTIL
#define CORINET_UTIL

namespace {//unnamed namespace

const char* GetRoot() {
	return getenv("CORINETROOT");
}

bool TestCompatibility() {
	return CORINET::RandTest();
}

}

#endif //CORINET_UTIL

