/*********************************************************************************************
 * Name      :  ConcreteStatus.h
 *
 * Purpose   :  Concrete classes providing information on the status of the experiment.
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

#ifndef CORINET_STATUSCONCR
#define CORINET_STATUSCONCR

#include <Engine/Impl/StatusImpl.h>
#include <sstream>

namespace CORINET {
	class CExTimeInfo;

class CStatusEngineV1 : public CStatusImpl {
	size_t mCurrentExecution;
	size_t mTotalExecutions;
	std::ostringstream ost;
public:
	CStatusEngineV1();
	virtual ~CStatusEngineV1();
	void operator()(CExTimeInfo*);
	void IncrExecution();

	void SetTotalExecutions(size_t);
};

} //end namespace CORINET

#endif //CORINET_STATUSCONCR
