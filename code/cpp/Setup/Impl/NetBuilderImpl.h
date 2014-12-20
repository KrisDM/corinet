/*********************************************************************************************
 * Name      :  NetBuilderImpl.h
 *
 * Purpose   :  Create networks and cleanup after use. This is the implementation class. 
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

#ifndef CORINET_NETBUILDERIMPL
#define CORINET_NETBUILDERIMPL

#include <Setup/NetBuilder.h>
#include <map>
#include <list>
#include <valarray>

namespace CORINET {
	struct SInitialisationMaker;
	struct SNormalisationMaker;
	struct SOutputFunctionMaker;
	struct SIntegrationSiteMaker;
	struct SBlockMaker;
	class FInitialisation;
	class FNormalisation;
	class FOutputFunction;
	class CIntegrationSite;
	class CBlock;
	class CCommonBuilder;

class CNetBuilderImpl : public CNetBuilder {
	typedef std::multimap<SInitialisationMaker*,FInitialisation*> LInitialisations;
	typedef std::multimap<SNormalisationMaker*,FNormalisation*> LNormalisations;
	typedef std::multimap<SOutputFunctionMaker*,FOutputFunction*> LOutputFunctions;
	typedef std::map<SIntegrationSiteMaker*,CIntegrationSite*> LIntegrationSites;
	typedef std::map<SBlockMaker*,CBlock*> LBlocks;
	typedef std::map<SNetworkMaker*,CNetwork*> LNetworks;
	typedef std::map<void*,std::list<CNetwork*> > LParents;
	typedef std::map<CNetwork*,std::string> LNetworkIDs;
	LInitialisations mInitialisations;
	LNormalisations mNormalisations;
	LOutputFunctions mOutputFunctions;
	LIntegrationSites mIntegrationSites;
	LBlocks mBlocks;
	LNetworks mNetworks;
	LParents mParents;
	LNetworkIDs mNetworkIDs;

	std::vector<CNetwork*> mTempParent;
	std::vector<void*> mTempObject;

	CCommonBuilder* pCommonBuilder;

	void AddParent(void*,CNetwork*);
public:
	CNetBuilderImpl();
	virtual ~CNetBuilderImpl();

	//initialise function
	void SetCommonBuilder(CCommonBuilder*);

	//create functions
	CNetwork* Create(SNetworkMaker*);

	CBlock* Create(SBlockMaker*,CNetwork*);
	CIntegrationSite* Create(SIntegrationSiteMaker*,CNetwork*,size_t);
	FOutputFunction* Create(SOutputFunctionMaker*,CNetwork*,size_t);
	FNormalisation* Create(SNormalisationMaker*,CNetwork*,size_t,size_t);
	FInitialisation* Create(SInitialisationMaker*,CNetwork*,size_t,size_t);

	//access functions
	CNetwork* Get(SNetworkMaker*);
	std::vector<void*>& GetVoid(SMaker*);
	std::vector<CNetwork*>& GetParents(void*);
	const std::string& GetNetworkID(CNetwork* const);
	
	//cleanup function
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_NETBUILDERIMPL

