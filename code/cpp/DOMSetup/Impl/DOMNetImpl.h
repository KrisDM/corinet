/*********************************************************************************************
 * Name      :  DOMNetImpl.h
 *
 * Purpose   :  Implementation class handling networks and child elements.
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

#ifndef CORINET_DOMNETIMPL
#define CORINET_DOMNETIMPL

#include <DOMSetup/DOMNet.h>
#include <map>
#include <list>
#include <valarray>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE
	
	struct SInitialisationMaker;
	struct SNormalisationMaker;
	struct SOutputFunctionMaker;
	struct SIntegrationSiteMaker;
	struct SBlockMaker;
	class CDOMDefaults;
	class CDOMCommon;

class CDOMNetImpl : public CDOMNet{
	typedef std::map<const DOMElement*,std::list<size_t>*> LInputBlockIndices;
	typedef std::map<const DOMElement*,std::valarray<size_t>*> LSiteIndices;
	typedef std::map<const DOMElement*,std::pair<size_t,size_t>*> LBlockIndices;
	typedef std::map<const DOMElement*,std::valarray<double>*> LWeightVals;
	typedef std::map<const DOMElement*,SInitialisationMaker*> LInitMakers;
	typedef std::map<const DOMElement*,SNormalisationMaker*> LNormMakers;
	typedef std::map<const DOMElement*,SOutputFunctionMaker*> LOutputMakers;
	typedef std::map<const DOMElement*,SIntegrationSiteMaker*> LSiteMakers;
	typedef std::map<const DOMElement*,SBlockMaker*> LBlockMakers;
	typedef std::map<const DOMElement*,SNetworkMaker*> LNetMakers;
	LInputBlockIndices mInputBlocks;
	LSiteIndices mSiteInputs;
	LBlockIndices mBlockOutputs;
	LWeightVals mWeightVals;
	LInitMakers mInitMakers;
	LNormMakers mNormMakers;
	LOutputMakers mOutputMakers;
	LSiteMakers mSiteMakers;
	LBlockMakers mBlockMakers;
	LNetMakers mNetMakers;
	CDOMDefaults* pDefaultsHandler;
	CDOMCommon* pCommonHandler;
public:
	CDOMNetImpl();
	virtual ~CDOMNetImpl();

	//initialise functions
	void SetDefaultsHandler(CDOMDefaults*);
	void SetCommonHandler(CDOMCommon*);

	void Handle(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create);

	//access functions
	SNetworkMaker* GetNetMaker(const DOMElement*);
	SMaker* GetMaker(const DOMElement*);
	std::valarray<double>* GetWeightVals(const DOMElement*);

	//cleanup
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_DOMNETIMPL



