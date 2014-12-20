/*********************************************************************************************
 * Name      :  SynapseWrapper.h
 *
 * Purpose   :  Wrapper class for per-synapse activation values from an integration site.
 *				It can be used in event handlers to record those activation values.
 *				Especially useful for pre-integration lateral inhibition.
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

#ifndef CORINET_SYNAPSEWRAPPER
#define CORINET_SYNAPSEWRAPPER

#include <Platform/Platform.h>

namespace CORINET {

class SynapseWrapper {
public:
	virtual ~SynapseWrapper() {}
	virtual double operator()(size_t,size_t) const =0;
	virtual size_t inputs() const =0;
	virtual size_t nodes() const =0;
};

} //namespace CORINET

#endif //CORINET_SYNAPSEWRAPPER

