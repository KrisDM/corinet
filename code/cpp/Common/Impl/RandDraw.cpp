/*********************************************************************************************
 * Name      :  RandDraw.cpp
 *
 * Purpose   :  Set the offset for seeding, so that two random generators created at the same
 *				time will not be seeded with the same number (unless specified explicitly).
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

#include "RandDraw.h"

namespace CORINET {

unsigned int RandDraw::seedBase = 2873;

} //end namespace CORINET



