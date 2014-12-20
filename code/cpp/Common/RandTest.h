/*********************************************************************************************
 * Name      :  RandTest.h
 *
 * Purpose   :  Function to test machine compatibility of the random generators.
 *
 * Notes	 :	If the function returns true, compatibility is guaranteed. If it returns false, 
 *				you should investigate whether the test itself or the underlying random
 *				generator has failed, and decide to write your own random generator in 
 *				file RandDraw.h.
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

#ifndef CORINET_RANDTEST
#define CORINET_RANDTEST

#include <Platform/Platform.h>

namespace CORINET {

bool RandTest();

} //end namespace CORINET

#endif //CORINET_RANDTEST


