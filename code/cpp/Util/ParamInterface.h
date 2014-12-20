/*********************************************************************************************
 * Name      :  ParamInterface.h
 *
 * Purpose   :  An interface for getting and setting parameters from parametrised objects.
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
#include <Util/Constants.h>

#ifndef CORINET_PARAMINTERFACE
#define CORINET_PARAMINTERFACE

namespace CORINET {

class CParamInterface {
public:
	virtual ~CParamInterface() {}
	virtual void SetParam(size_t,double) {}
	virtual double GetParam(size_t) {return 0.0;}
};

} //namespace CORINET

#endif //CORINET_PARAMINTERFACE

