/*********************************************************************************************
 * Name      :  Condition.h
 *
 * Purpose   :  Function objects implementing the operators for conditions in event handlers.
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

#ifndef CORINET_CONDITION
#define CORINET_CONDITION

#include <Platform/Platform.h>

namespace CORINET {

class FCondition {
public:
	virtual ~FCondition() {}
	virtual bool operator()(double) const =0;
};

} //end namespace CORINET

#endif //CORINET_CONDITION

