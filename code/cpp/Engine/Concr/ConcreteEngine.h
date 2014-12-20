/*********************************************************************************************
 * Name      :  ConcreteEngine.h
 *
 * Purpose   :  Concrete types of execution engines.
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

#ifndef CORINET_ENGINECONCR
#define CORINET_ENGINECONCR

#include <Engine/Impl/EngineImpl.h>

namespace CORINET {
	
class CEngineV1 : public CEngineImpl {
	CStatus* pStatus;
public:
	CEngineV1();
	virtual ~CEngineV1();
	void Execute(CBuilder*);

	void SetStatus(CStatus*);
};

} //end namespace CORINET

#endif //CORINET_ENGINECONCR
