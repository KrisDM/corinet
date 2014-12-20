/*********************************************************************************************
 * Name      :  RandTest.cpp
 *
 * Purpose   :  Function to test machine compatibility of random generators.
 *
 * Notes	 :	If it returns true, compatibility is guaranteed. If it returns false, you 
 *				should investigate whether the test itself or the underlying random
 *				generator has failed, and decide to add your own random generator in 
 *				file RandImpl.h.
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

#include <Common/Impl/RandDraw.h>

namespace CORINET {

bool RandTest() 
{
	RandDraw rd;
	rd.seed(0);
	if (rd.draw()!=0x3C6EF35F) return false;
	if (rd.draw()!=0x47502932) return false;
	if (rd.draw()!=0xD1CCF6E9) return false;
	if (rd.draw()!=0xAAF95334) return false;
	if (rd.draw()!=0x6252E503) return false;
	if (rd.draw()!=0x9F2EC686) return false;
	return true;
}

} //end namespace CORINET



