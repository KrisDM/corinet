/*********************************************************************************************
 * Name      :  Constants.h
 *
 * Purpose   :  Constants used in various places.
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

#ifndef CORINET_CONSTANTS
#define CORINET_CONSTANTS

namespace CORINET {

static const double gPrecision = 1e-12;//cutoff for smallest activity or weight value

static const size_t gNumParams = 10;//number of parameters allowed in makers structs

}

#endif //CORINET_CONSTANTS

