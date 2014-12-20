/*********************************************************************************************
 * Name      :  Status.h
 *
 * Purpose   :  Class providing information on the status of the experiment.
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

#ifndef CORINET_STATUS
#define CORINET_STATUS

#include <Platform/Platform.h>

namespace CORINET {
	class CExTimeInfo;

class CStatus {
public:
	virtual ~CStatus() {}
	virtual void operator()(CExTimeInfo*) =0;
	virtual void IncrExecution() =0;
};

} //end namespace CORINET

#endif //CORINET_STATUS
