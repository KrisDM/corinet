/*********************************************************************************************
 * Name      :  NetBuilder.h
 *
 * Purpose   :  Create networks and cleanup after use. 
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

#ifndef CORINET_NETBUILDER
#define CORINET_NETBUILDER

#include <Platform/Platform.h>
#include <string>
#include <vector>

namespace CORINET {
	struct SNetworkMaker;
	struct SMaker;
	class CNetwork;

class CNetBuilder {
public:
	virtual ~CNetBuilder() {}

	//create function
	virtual CNetwork* Create(SNetworkMaker*) =0;

	//access functions
	virtual CNetwork* Get(SNetworkMaker*) =0;
	virtual std::vector<void*>& GetVoid(SMaker*) =0;
	virtual std::vector<CNetwork*>& GetParents(void*) =0;
	virtual const std::string& GetNetworkID(CNetwork* const) =0;
	
	//cleanup function
	virtual void ReleaseAll() =0;
};

} //end namespace CORINET

#endif //CORINET_NETBUILDER

