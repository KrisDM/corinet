/*********************************************************************************************
 * Name      :  NetBuilder.cpp
 *
 * Purpose   :  Create networks and cleanup after use. Implementation class.
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

#include "NetBuilderImpl.h"
#include <Model/Impl/InitialisationImpl.h>
#include <Model/Impl/NormalisationImpl.h>
#include <Model/Impl/OutputFunctionImpl.h>
#include <Model/Impl/IntegrationSiteImpl.h>
#include <Model/Impl/BlockImpl.h>
#include <Model/Impl/NetworkImpl.h>
#include <Util/Factory.h>
#include <Common/RandGen.h>
#include <Setup/Makers.h>
#include <Setup/CommonBuilder.h>

namespace CORINET {

CNetBuilderImpl::CNetBuilderImpl() : mInitialisations(),mNormalisations(),mOutputFunctions(),mIntegrationSites(),
									 mBlocks(),mNetworks(),mParents(),mNetworkIDs(),
									 mTempParent(),mTempObject(),pCommonBuilder(0)
{
		
}

CNetBuilderImpl::~CNetBuilderImpl()
{
	ReleaseAll();
}

void CNetBuilderImpl::AddParent(void* object,CNetwork* parent)
{
	if (mParents.find(object) == mParents.end()) {
		mParents[object] = std::list<CNetwork*>();
		mParents[object].push_back(parent);
	}
	else {
		mParents[object].push_back(parent);
		mParents[object].sort();
		mParents[object].unique();
	}
}

void CNetBuilderImpl::SetCommonBuilder(CCommonBuilder* pcb)
{
	pCommonBuilder = pcb;
}

CNetwork* CNetBuilderImpl::Create(SNetworkMaker* pnm)
{
	if (mNetworks.find(pnm) == mNetworks.end()) {
		size_t sizeparams[3];
		sizeparams[0] = pnm->numInputs;
		sizeparams[1] = pnm->numNodes;
		sizeparams[2] = pnm->blockMakers.size();

		CNetwork* pn = CFactoryManager<CNetwork>::CreateInstance(pnm->type,sizeparams,pnm->netParams);

		if (!pn)
			throw ECreation("network",pnm->type);
		else {
			mNetworks.insert(LNetworks::value_type(pnm,pn));
			mNetworkIDs.insert(LNetworkIDs::value_type(pn,pnm->idStr));
		}

		//add the blocks
		for(size_t b=0,bs=pnm->blockMakers.size();b<bs;++b) {
			static_cast<CNetworkImpl*>(pn)->AddBlock(Create(pnm->blockMakers[b],pn),pnm->blockMakers[b]->outputBlock);
		}

		AddParent(pn,pn);
	}

	return mNetworks[pnm];
}

CBlock* CNetBuilderImpl::Create(SBlockMaker* pbm,CNetwork* pparent)
{
	if (mBlocks.find(pbm) == mBlocks.end()) {
		size_t sizeparams[2];
		sizeparams[0] = pbm->numNodes;
		sizeparams[1] = pbm->siteMakers.size();

		CBlock* pb = CFactoryManager<CBlock>::CreateInstance(pbm->type,sizeparams,pbm->blockParams);
	
		if (!pb)
			throw ECreation("block",pbm->type);
		else
			mBlocks.insert(LBlocks::value_type(pbm,pb));

		//set the node (output) indices
		static_cast<CBlockImpl*>(pb)->SetOutputIndices(static_cast<CNetworkImpl*>(pparent)->GetNodePool(),pbm->beginNode,pbm->numNodes);
		//set the outputfunction
		static_cast<CBlockImpl*>(pb)->SetOutputFunction(Create(pbm->outputMaker,pparent,pbm->numNodes));
		//add the integration sites
		for(size_t i=0,is=pbm->siteMakers.size();i<is;++i) {
			static_cast<CBlockImpl*>(pb)->AddIntegrationSite(Create(pbm->siteMakers[i],pparent,pbm->numNodes));
		}

		AddParent(pb,pparent);
	}
	
	return mBlocks[pbm];
}

CIntegrationSite* CNetBuilderImpl::Create(SIntegrationSiteMaker* psm,CNetwork* pparent,size_t numnodes)
{
	if (mIntegrationSites.find(psm) == mIntegrationSites.end()) {
		size_t sizeparams[2];
		sizeparams[0] = psm->inputIndex->size();
		sizeparams[1] = numnodes;

		CIntegrationSite* ps = CFactoryManager<CIntegrationSite>::CreateInstance(psm->type,sizeparams,psm->siteParams);

		if (!ps)
			throw ECreation("integration site",psm->type);
		else
			mIntegrationSites.insert(LIntegrationSites::value_type(psm,ps));

		//set the input indices
		static_cast<CIntegrationSiteImpl*>(ps)->SetInputIndices(static_cast<CNetworkImpl*>(pparent)->GetNodePool(),psm->inputIndex);
		//set the normalisation
		static_cast<CIntegrationSiteImpl*>(ps)->SetNormalisation(Create(psm->normMaker,pparent,sizeparams[0],sizeparams[1]));
		//set the initialisation
		static_cast<CIntegrationSiteImpl*>(ps)->SetInitialisation(Create(psm->initMaker,pparent,sizeparams[0],sizeparams[1]));
	
		AddParent(ps,pparent);
	}

	return mIntegrationSites[psm];
}

FOutputFunction* CNetBuilderImpl::Create(SOutputFunctionMaker* pom,CNetwork* pparent,size_t numnodes)
{
	FOutputFunction* po;
	//if pom->state, then a new function object needs to be created for every call of this Create function
	if (pom->state || (mOutputFunctions.find(pom) == mOutputFunctions.end())) {
		po = CFactoryManager<FOutputFunction>::CreateInstance(pom->type,&numnodes,pom->outputParams);

		if (!po)
			throw ECreation("output function",pom->type);
		else
			mOutputFunctions.insert(LOutputFunctions::value_type(pom,po));

		//set the attenuation function
		if (pom->attenuationMaker) {
			FAttenuation* pat = pCommonBuilder->Create(pom->attenuationMaker,numnodes);
			static_cast<FOutputFunctionImpl*>(po)->SetAttenuation(pat);
			AddParent(pat,pparent);
		}
		else
			static_cast<FOutputFunctionImpl*>(po)->SetAttenuation(0);
		//set the noise function
		if (pom->noiseMaker) {
			FNoiseFunction* pnf = pCommonBuilder->Create(pom->noiseMaker,numnodes);
			static_cast<FOutputFunctionImpl*>(po)->SetNoise(pnf);
			AddParent(pnf,pparent);
			if(pom->noiseMaker->randMaker) {
				RandGen* pr = pCommonBuilder->Get(pom->noiseMaker->randMaker);
				AddParent(pr,pparent);
			}
		}
		else
			static_cast<FOutputFunctionImpl*>(po)->SetNoise(0);

		AddParent(po,pparent);
	}
	else {
		po = mOutputFunctions.find(pom)->second;
		AddParent(po,pparent);
	}

	return po;
}

FNormalisation* CNetBuilderImpl::Create(SNormalisationMaker* pnm,CNetwork* pparent,size_t numinputs,size_t numnodes)
{
	FNormalisation* pn;
	//if pnm->state, then a new function object needs to be created for every call of the Create function
	if (pnm->state || (mNormalisations.find(pnm) == mNormalisations.end())) {	
		size_t sizeparams[2];
		sizeparams[0] = numinputs;
		sizeparams[1] = numnodes;

		pn = CFactoryManager<FNormalisation>::CreateInstance(pnm->type,sizeparams,pnm->normParams);

		if (!pn)
			throw ECreation("normalisation function",pnm->type);
		else
			mNormalisations.insert(LNormalisations::value_type(pnm,pn));

		AddParent(pn,pparent);
	}
	else {
		pn = mNormalisations.find(pnm)->second;
		AddParent(pn,pparent);
	}
	return pn;
}

FInitialisation* CNetBuilderImpl::Create(SInitialisationMaker* pim,CNetwork* pparent,size_t numinputs,size_t numnodes)
{
	FInitialisation* pi;
	//if pim->state, then a new function object needs to be created for every call of the Create function
	if (pim->state || (mInitialisations.find(pim) == mInitialisations.end())) {	
		size_t sizeparams[2];
		sizeparams[0] = numinputs;
		sizeparams[1] = numnodes;

		pi = CFactoryManager<FInitialisation>::CreateInstance(pim->type,sizeparams,pim->initParams);

		if (!pi)
			throw ECreation("initialisation function",pim->type);
		else
			mInitialisations.insert(LInitialisations::value_type(pim,pi));

		if (pim->randMaker) {
			RandGen* pr = pCommonBuilder->Create(pim->randMaker);
			static_cast<FInitialisationImpl*>(pi)->SetRandGen(static_cast<RandDouble*>(pr));
			AddParent(pr,pparent);
		}
		else
			static_cast<FInitialisationImpl*>(pi)->SetRandGen(0);

		if (pim->weightVals)
			pi->SetWPointer(pim->weightVals);
		else
			pi->SetWPointer(0);
		
		AddParent(pi,pparent);
	}	
	else {
		pi = mInitialisations.find(pim)->second;
		AddParent(pi,pparent);
	}
	return pi;
}

CNetwork* CNetBuilderImpl::Get(SNetworkMaker* nm)
{
	if (mNetworks.find(nm) != mNetworks.end()) 
		return mNetworks[nm];
	else
		return 0;
}

std::vector<void*>& CNetBuilderImpl::GetVoid(SMaker* maker)
{
	mTempObject.clear();
	if (maker->makerType == "network") {
		if (mNetworks.find(static_cast<SNetworkMaker*>(maker)) != mNetworks.end()) {
			mTempObject.push_back(mNetworks[static_cast<SNetworkMaker*>(maker)]);
		}
	}
	else if (maker->makerType == "block") {
		if (mBlocks.find(static_cast<SBlockMaker*>(maker)) != mBlocks.end()) {
			mTempObject.push_back(mBlocks[static_cast<SBlockMaker*>(maker)]);
		}
	}
	else if (maker->makerType == "integrationSite") {
		if (mIntegrationSites.find(static_cast<SIntegrationSiteMaker*>(maker)) != mIntegrationSites.end()) {
			mTempObject.push_back(mIntegrationSites[static_cast<SIntegrationSiteMaker*>(maker)]);
		}
	}
	else if (maker->makerType == "outputFunction") {
		if (mOutputFunctions.find(static_cast<SOutputFunctionMaker*>(maker)) != mOutputFunctions.end()) {
			SOutputFunctionMaker* om = static_cast<SOutputFunctionMaker*>(maker);
			for(LOutputFunctions::iterator it=mOutputFunctions.lower_bound(om),ite=mOutputFunctions.upper_bound(om);it != ite;++it) {
				mTempObject.push_back(it->second);
			}
		}
	}
	else if (maker->makerType == "normalisation") {
		if (mNormalisations.find(static_cast<SNormalisationMaker*>(maker)) != mNormalisations.end()) {
			SNormalisationMaker* nm = static_cast<SNormalisationMaker*>(maker);
			for(LNormalisations::iterator it=mNormalisations.lower_bound(nm),ite=mNormalisations.upper_bound(nm);it != ite;++it) {
				mTempObject.push_back(it->second);
			}
		}
	}
	else if (maker->makerType == "initialisation") {
		if (mInitialisations.find(static_cast<SInitialisationMaker*>(maker)) != mInitialisations.end()) {
			SInitialisationMaker* im = static_cast<SInitialisationMaker*>(maker);
			for(LInitialisations::iterator it=mInitialisations.lower_bound(im),ite=mInitialisations.upper_bound(im);it != ite;++it) {
				mTempObject.push_back(it->second);
			}
		}
	}
	return mTempObject;
}
	
std::vector<CNetwork*>& CNetBuilderImpl::GetParents(void* object)
{
	mTempParent.clear();
	if (mParents.find(object) != mParents.end()) {
		std::list<CNetwork*>& templist = mParents[object];
		for(std::list<CNetwork*>::iterator it=templist.begin(),ite=templist.end();it != ite;++it) {
			mTempParent.push_back(*it);
		}
	}
	return mTempParent;
}

const std::string& CNetBuilderImpl::GetNetworkID(CNetwork* const net)
{
	return mNetworkIDs[net];
}
	
void CNetBuilderImpl::ReleaseAll()
{
	for(LInitialisations::iterator it1=mInitialisations.begin(),ite1=mInitialisations.end();it1 != ite1;++it1) {
		delete it1->second;
		it1->second = 0;
	}
	mInitialisations.clear();
	for(LNormalisations::iterator it2=mNormalisations.begin(),ite2=mNormalisations.end();it2 != ite2;++it2) {
		delete it2->second;
		it2->second = 0;
	}
	mNormalisations.clear();
	for(LOutputFunctions::iterator it3=mOutputFunctions.begin(),ite3=mOutputFunctions.end();it3 != ite3;++it3) {
		delete it3->second;
		it3->second = 0;
	}
	mOutputFunctions.clear();
	for(LIntegrationSites::iterator it4=mIntegrationSites.begin(),ite4=mIntegrationSites.end();it4 != ite4;++it4) {
		delete it4->second;
		it4->second = 0;
	}
	mIntegrationSites.clear();
	for(LBlocks::iterator it5=mBlocks.begin(),ite5=mBlocks.end();it5 != ite5;++it5) {
		delete it5->second;
		it5->second = 0;
	}
	mBlocks.clear();
	for(LNetworks::iterator it6=mNetworks.begin(),ite6=mNetworks.end();it6 != ite6;++it6) {
		delete it6->second;
		it6->second = 0;
	}
	mNetworks.clear();
	mParents.clear();
	mNetworkIDs.clear();
}

} //end namespace CORINET

