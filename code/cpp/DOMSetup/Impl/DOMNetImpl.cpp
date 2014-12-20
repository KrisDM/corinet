/*********************************************************************************************
 * Name      :  DOMNetImpl.cpp
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

#include "DOMNetImpl.h"
#include <DOMSetup/DOMCommon.h>
#include <DOMSetup/DOMDefaults.h>
#include <DOMSetup/Misc/DOMHelperFunctions.h>
#include <Setup/Makers.h>
#include <algorithm>
#include <limits>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

CDOMNetImpl::CDOMNetImpl() : mInputBlocks(),mSiteInputs(),mBlockOutputs(),mWeightVals(),
							 mInitMakers(),mNormMakers(),mOutputMakers(),
							 mSiteMakers(),mBlockMakers(),mNetMakers(),
							 pDefaultsHandler(0),pCommonHandler(0)
{
		
}

CDOMNetImpl::~CDOMNetImpl()
{
	ReleaseAll();
}

void CDOMNetImpl::SetDefaultsHandler(CDOMDefaults* pdef)
{
	pDefaultsHandler = pdef;
}
	
void CDOMNetImpl::SetCommonHandler(CDOMCommon* pcom)
{
	pCommonHandler = pcom;
}

void CDOMNetImpl::Handle(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create)
{
	//handle all <inputBlock> elements
	const DOMNodeList* pDOMInputBlockList = GetElementList(setupDoc,XMLStrDefs::inputBlock);
	for(XMLSize_t a1=0,as1=pDOMInputBlockList->getLength();a1<as1;++a1) {
		std::list<size_t>* tempList = new std::list<size_t>(); //container for inputIndices
		const DOMElement* pDOMIB = GetElement(pDOMInputBlockList,a1);
		const DOMNodeList* pDOMIndicesList = GetElementList(pDOMIB,XMLStrDefs::inputIndices);
		for(XMLSize_t k1=0,ks1=pDOMIndicesList->getLength();k1<ks1;++k1) {
			const DOMElement* pDOMIndices = GetElement(pDOMIndicesList,k1);
			const DOMNodeList* pChildren = pDOMIndices->getChildNodes();
			for(XMLSize_t l1=0,ls1=pChildren->getLength();l1<ls1;++l1) {
				if (pChildren->item(l1)->getNodeType() == DOMNode::TEXT_NODE) {
					std::vector<XMLCh*> indices = XMLStringUtil::Tokenise(pChildren->item(l1)->getNodeValue());
					XMLJanitor jan(indices);
					for(size_t m1=0,ms1=indices.size();m1<ms1;++m1) {
						tempList->push_back(XMLStringUtil::XML2Int(indices[m1]));
					}
				}
			}
		}
		const DOMNodeList* pDOMRangeList = GetElementList(pDOMIB,XMLStrDefs::inputRange);
		for(XMLSize_t k2=0,ks2=pDOMRangeList->getLength();k2<ks2;++k2) {
			const DOMElement* pDOMRange = GetElement(pDOMRangeList,k2);
			int b = XMLStringUtil::XML2Int(pDOMRange->getAttribute(XMLStrDefs::begin));
			int s = XMLStringUtil::XML2Int(pDOMRange->getAttribute(XMLStrDefs::step));
			int e = XMLStringUtil::XML2Int(pDOMRange->getAttribute(XMLStrDefs::end));
			//reverse order of decreasing loops
			if (b>e) {
				for(int v=b;v>=e;v-=s)
					tempList->push_back(v);
			}
			else {
				for(int v=b;v<=e;v+=s)
					tempList->push_back(v);
			}
		}
		//tempList->sort(); //commented out in Revision 1.1
		mInputBlocks[pDOMIB] = tempList;
	}

	//make the network structure, network per network
	const DOMNodeList* pDOMnetList = GetElementList(setupDoc,XMLStrDefs::network);
	for(XMLSize_t a2=0,as2=pDOMnetList->getLength();a2<as2;++a2) {
		const DOMElement* pDOMnet = GetElement(pDOMnetList,a2);
		size_t netInputs = XMLStringUtil::XML2Int(pDOMnet->getAttribute(XMLStrDefs::inputs));
		//first make all the indices for <block> elements
		size_t nodeCounter = netInputs;
		const DOMNodeList* pDOMblockList = GetElementList(pDOMnet,XMLStrDefs::block);
		for(XMLSize_t b2=0,bs2=pDOMblockList->getLength();b2<bs2;++b2) {
			const DOMElement* pDOMblock = GetElement(pDOMblockList,b2);
			std::pair<size_t,size_t>* temp = new std::pair<size_t,size_t>;
			temp->first = nodeCounter;
			temp->second = XMLStringUtil::XML2Int(pDOMblock->getAttribute(XMLStrDefs::nodes));
			nodeCounter += temp->second;
			mBlockOutputs[pDOMblock] = temp;
		}
		//then handle the inputs to <integrationSite> elements
		const DOMNodeList* pDOMsiteList = GetElementList(pDOMnet,XMLStrDefs::integrationSite);
		for(XMLSize_t c2=0,cs2=pDOMsiteList->getLength();c2<cs2;++c2) {
			const DOMElement* pDOMsite = GetElement(pDOMsiteList,c2);
			CheckIDREFS(pDOMsite,setupDoc,eHandler,XMLStrDefs::inputRefs,XMLStrDefs::inputBlock,XMLStrDefs::block);
			//then go through all of them, get the total number of inputs to this site, and check if all references
			//refer to blocks within the same network
			std::vector<XMLCh*> inputRefs = XMLStringUtil::Tokenise(pDOMsite->getAttribute(XMLStrDefs::inputRefs));
			XMLJanitor jan(inputRefs);
			size_t inputCounter = 0;
			for(size_t r1=0,rs1=inputRefs.size();r1<rs1;++r1) {
				const DOMElement* pDOMinputRef = setupDoc->getElementById(inputRefs[r1]);
				if (XMLStringUtil::Equals(pDOMinputRef->getTagName(),XMLStrDefs::block)) {
					const DOMElement* pDOMparentNet = static_cast<DOMElement*>(pDOMinputRef->getParentNode());
					if (!pDOMparentNet->isSameNode(pDOMnet)) {
						CErrorHandler::PrepareError("inputRef \"" + XMLStringUtil::XML2Str(inputRefs[r1]) + 
							"\"refers to <block> in different <network>.",pDOMsite,eHandler);
					}
					inputCounter += mBlockOutputs[pDOMinputRef]->second;
				}
				else {//inputRef refers to inputBlock, check max index
					if (mInputBlocks[pDOMinputRef]->back() >= netInputs) {
						CErrorHandler::PrepareError("Input index of inputRef \"" + XMLStringUtil::XML2Str(inputRefs[r1]) +
							"\"too large for <network>.",pDOMsite,eHandler);
					}
					inputCounter += mInputBlocks[pDOMinputRef]->size();
				}
			}
			std::valarray<size_t>* inputIndices = new std::valarray<size_t>(inputCounter);
			mSiteInputs.insert(LSiteIndices::value_type(pDOMsite,inputIndices));
			inputCounter=0;
			for(size_t r2=0,rs2=inputRefs.size();r2<rs2;++r2) {
				const DOMElement* pDOMinputRef = setupDoc->getElementById(inputRefs[r2]);
				if (XMLStringUtil::Equals(pDOMinputRef->getTagName(),XMLStrDefs::block)) {
					std::pair<size_t,size_t>* thisblock = mBlockOutputs[pDOMinputRef];
					for(size_t index1=0;index1<thisblock->second;++index1) {
						(*inputIndices)[index1+inputCounter] = index1 + thisblock->first;
					}
					inputCounter += thisblock->second;
				}
				else {//inputRef refers to inputBlock, check max index
					std::list<size_t>* temp = mInputBlocks[pDOMinputRef];
					std::copy(temp->begin(),temp->end(),&((*inputIndices)[inputCounter]));
					inputCounter += mInputBlocks[pDOMinputRef]->size();
				}
			}
			//std::sort(&((*inputIndices)[0]),&((*inputIndices)[inputIndices->size()])); //commented out in Revision 1.1
		}
	}

	//handle all <w> elements
	const DOMNodeList* pDOMwList = GetElementList(setupDoc,XMLStrDefs::w);
	for(XMLSize_t w1=0,ws1=pDOMwList->getLength();w1<ws1;++w1) {
		const DOMElement* pDOMw = GetElement(pDOMwList,w1);
		const DOMElement* pDOMparent = static_cast<DOMElement*>(pDOMw->getParentNode()->getParentNode());
		size_t numinputs = 0;
		size_t numnodes = 0;
		if (XMLStringUtil::Equals(pDOMparent->getTagName(),XMLStrDefs::xmldefault)) {
			std::vector<XMLCh*> targets = XMLStringUtil::Tokenise(pDOMparent->getAttribute(XMLStrDefs::targets));
			XMLJanitor jan(targets);
			for(size_t m1=0,ms1=targets.size();m1<ms1;++m1) {
				const DOMElement* pDOMparentIS = setupDoc->getElementById(targets[m1]);
				const DOMElement* pDOMparentBlock = static_cast<DOMElement*>(pDOMparentIS->getParentNode());
				if (m1 == 0) {
					numinputs = mSiteInputs[pDOMparentIS]->size();
					numnodes = mBlockOutputs[pDOMparentBlock]->second;
				}
				else {
					if ((numinputs != mSiteInputs[pDOMparentIS]->size()) || (numnodes != mBlockOutputs[pDOMparentBlock]->second)) {
						CErrorHandler::PrepareError("default <initialisation> with explicit <w> has targets of different sizes.",pDOMparent,eHandler);
					}
				}
			}
		}
		else {
			numinputs = mSiteInputs[pDOMparent]->size();
			const DOMElement* pDOMparentBlock = static_cast<DOMElement*>(pDOMparent->getParentNode());
			numnodes = mBlockOutputs[pDOMparentBlock]->second;
		}
		std::valarray<double>* tempWeights = 0;
		if (create) {
			tempWeights = new std::valarray<double>(numinputs*numnodes);
			mWeightVals.insert(LWeightVals::value_type(pDOMw,tempWeights));
		}
		Get2DVals(pDOMw,numinputs,numnodes,XMLStrDefs::i,XMLStrDefs::n,pDOMparent,eHandler,tempWeights);
	}

	//handle the <initialisation> elements
	const DOMNodeList* pDOMinitList = GetElementList(setupDoc,XMLStrDefs::initialisation);
	for(XMLSize_t i1=0,is1=pDOMinitList->getLength();i1<is1;++i1) {
		//get the current element and the subelement containing the parameters
		const DOMElement* pDOMinit = GetElement(pDOMinitList,i1);
		const DOMElement* pDOMinitParams = GetElement(pDOMinit,XMLStrDefs::initParams,0);

		//check its type
		const DOMElement* pDOMvalInit = GetType(pDOMinit,valDoc,eHandler);

		//check the presence of <randGen> element
		CheckChildElement(pDOMinit,pDOMvalInit,eHandler,XMLStrDefs::randGen);
		//check the presense of <w> element
		CheckChildElement(pDOMinit,pDOMvalInit,eHandler,XMLStrDefs::w);

		//if there is more than one <w>, <initialisation> should have an ID
		if ((GetElementList(pDOMinit,XMLStrDefs::w)->getLength() > 1) &&
			!pDOMinit->hasAttribute(XMLStrDefs::id)) {
			CErrorHandler::PrepareError("<initialisation> with more than one <w> needs to have attribute \"id\".",pDOMinit,eHandler);
		}

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalInit,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMinitParams,pDOMvalInit,eHandler,pDOMinit);
		
		//now that all checks have completed, create the initMaker if needed
		if (create) {
			SInitialisationMaker* initMaker = new SInitialisationMaker(XMLStringUtil::XML2Str(pDOMinit->getAttribute(XMLStrDefs::type)));
			mInitMakers.insert(LInitMakers::value_type(pDOMinit,initMaker));
			for(size_t i=0,is=vals.size();i<is;++i) {
				initMaker->initParams[i] = vals[i];
			}
			initMaker->randMaker = pCommonHandler->GetRandMaker(GetElement(pDOMinit,XMLStrDefs::randGen,0));
			const DOMElement* pDOMw = GetElement(pDOMinit,XMLStrDefs::w,0);
			if (mWeightVals.find(pDOMw) != mWeightVals.end()) {
				initMaker->weightVals = mWeightVals[pDOMw];
			}
			initMaker->state = GetBool(pDOMvalInit,XMLStrDefs::state);
		}
	}

	//handle the <normalisation> elements
	const DOMNodeList* pDOMnormList = GetElementList(setupDoc,XMLStrDefs::normalisation);
	for(XMLSize_t i2=0,is2=pDOMnormList->getLength();i2<is2;++i2) {
		//get the current element
		const DOMElement* pDOMnorm = GetElement(pDOMnormList,i2);
		//check its type
		const DOMElement* pDOMvalNorm = GetType(pDOMnorm,valDoc,eHandler);

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalNorm,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMnorm,pDOMvalNorm,eHandler,pDOMnorm);
		
		//now that all checks have completed, create the attenuationMaker if needed
		if (create) {
			SNormalisationMaker* normMaker = new SNormalisationMaker(XMLStringUtil::XML2Str(pDOMnorm->getAttribute(XMLStrDefs::type)));
			mNormMakers.insert(LNormMakers::value_type(pDOMnorm,normMaker));
			for(size_t i=0,is=vals.size();i<is;++i) {
				normMaker->normParams[i] = vals[i];
			}
			normMaker->state = GetBool(pDOMvalNorm,XMLStrDefs::state);
		}
	}

	//handle the <outputFunction> elements
	const DOMNodeList* pDOMoutputList = GetElementList(setupDoc,XMLStrDefs::outputFunction);
	for(XMLSize_t i3=0,is3=pDOMoutputList->getLength();i3<is3;++i3) {
		//get the current element
		const DOMElement* pDOMoutput = GetElement(pDOMoutputList,i3);
		const DOMElement* pDOMoutputParams = GetElement(pDOMoutput,XMLStrDefs::outputParams,0);
		//check its type
		const DOMElement* pDOMvalOutput = GetType(pDOMoutput,valDoc,eHandler);

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalOutput,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMoutputParams,pDOMvalOutput,eHandler,pDOMoutput);
		
		//now that all checks have completed, create the outputMaker if needed
		if (create) {
			SOutputFunctionMaker* outputMaker = new SOutputFunctionMaker(XMLStringUtil::XML2Str(pDOMoutput->getAttribute(XMLStrDefs::type)));
			mOutputMakers.insert(LOutputMakers::value_type(pDOMoutput,outputMaker));
			for(size_t i=0,is=vals.size();i<is;++i) {
				outputMaker->outputParams[i] = vals[i];
			}
			//set the state bit
			outputMaker->state = GetBool(pDOMvalOutput,XMLStrDefs::state);
			//try to find the attenuation function and add its maker
			const DOMElement* pDOMattenuation = GetElement(pDOMoutput,XMLStrDefs::attenuation,0);
			if (!pDOMattenuation) {//no local definition, look in targetDefaults
				pDOMattenuation = pDefaultsHandler->GetObject(pDOMoutput,XMLStrDefs::attenuation);
			}
			if (!pDOMattenuation) {//now look in typeDefaults
				pDOMattenuation = pDefaultsHandler->GetObject(pDOMoutput->getAttribute(XMLStrDefs::type),XMLStrDefs::attenuation);
			}
			if (pDOMattenuation) {
				outputMaker->attenuationMaker = pCommonHandler->GetAttenuationMaker(pDOMattenuation);
			}
			if (outputMaker->attenuationMaker) {//propagate state bit of attenuationMaker
				if (outputMaker->attenuationMaker->state) 
					outputMaker->state = true;
			}
			//try to find the noise function and add its maker
			const DOMElement* pDOMnoise = GetElement(pDOMoutput,XMLStrDefs::noiseFunction,0);
			if (!pDOMnoise) {//no local definition, look in targetDefaults
				pDOMnoise = pDefaultsHandler->GetObject(pDOMoutput,XMLStrDefs::noiseFunction);
			}
			if (!pDOMnoise) {//now look in typeDefaults
				pDOMnoise = pDefaultsHandler->GetObject(pDOMoutput->getAttribute(XMLStrDefs::type),XMLStrDefs::noiseFunction);
			}
			if (pDOMnoise) {
				outputMaker->noiseMaker = pCommonHandler->GetNoiseMaker(pDOMnoise);
			}
			if (outputMaker->noiseMaker) {//propagate state bit of noiseMaker
				if (outputMaker->noiseMaker->state)
					outputMaker->state = outputMaker->noiseMaker->state;
			}
		}
	}

	//handle the <integrationSite> elements
	const DOMNodeList* pDOMsiteList = GetElementList(setupDoc,XMLStrDefs::integrationSite);
	for(XMLSize_t i4=0,is4=pDOMsiteList->getLength();i4<is4;++i4) {
		//get the current element
		const DOMElement* pDOMsite = GetElement(pDOMsiteList,i4);
		const DOMElement* pDOMsiteParams = GetElement(pDOMsite,XMLStrDefs::siteParams,0);
		const XMLCh* typeXCh = pDOMsite->getAttribute(XMLStrDefs::type);
		//check its type
		const DOMElement* pDOMvalSite = GetType(pDOMsite,valDoc,eHandler);
		//check the validity of the location attribute, if present
		if (pDOMsite->hasAttribute(XMLStrDefs::location)) {
			const XMLCh* locXCh = pDOMsite->getAttribute(XMLStrDefs::location);
			const DOMElement* pDOMvalLoc = valDoc->getElementById(locXCh);
			if (!pDOMvalLoc) {
				CErrorHandler::PrepareError("Unknown location name.",pDOMsite,eHandler);
			}
			else if (!XMLStringUtil::Equals(XMLStrDefs::location,pDOMvalLoc->getTagName())) {
				CErrorHandler::PrepareError("Wrong name for location.",pDOMsite,eHandler);
			}
		}

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalSite,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMsiteParams,pDOMvalSite,eHandler,pDOMsite,
			pDefaultsHandler->GetParams(pDOMsite),pDefaultsHandler->GetParams(typeXCh));

		//check if there's an <initialisation> element
		const DOMElement* pDOMinit = GetElement(pDOMsite,XMLStrDefs::initialisation,0);
		if (!pDOMinit) {//no locally defined one, look in <targetDefaults>
			pDOMinit = pDefaultsHandler->GetObject(pDOMsite,XMLStrDefs::initialisation);
		}
		if (!pDOMinit) {//now look in <typeDefaults>
			pDOMinit = pDefaultsHandler->GetObject(typeXCh,XMLStrDefs::initialisation);
		}
		if (!pDOMinit) {
			CErrorHandler::PrepareError("No <initialisation> defined.",pDOMsite,eHandler);
		}

		//check if there's a <normalisation> element
		const DOMElement* pDOMnorm = GetElement(pDOMsite,XMLStrDefs::normalisation,0);
		if (!pDOMnorm) {//no locally defined one, look in <targetDefaults>
			pDOMnorm = pDefaultsHandler->GetObject(pDOMsite,XMLStrDefs::normalisation);
		}
		if (!pDOMnorm) {//now look in <typeDefaults>
			pDOMnorm = pDefaultsHandler->GetObject(typeXCh,XMLStrDefs::normalisation);
		}
		if (!pDOMnorm) {
			CErrorHandler::PrepareError("No <normalisation> defined.",pDOMsite,eHandler);
		}
		
		//now that all checks have completed, create the siteMaker if needed
		if (create) {
			std::string idstr;
			if (pDOMsite->hasAttribute(XMLStrDefs::id))
				idstr = XMLStringUtil::XML2Str(pDOMsite->getAttribute(XMLStrDefs::id));
			else
				idstr = "";
			SIntegrationSiteMaker* siteMaker = new SIntegrationSiteMaker(XMLStringUtil::XML2Str(typeXCh),idstr);
			mSiteMakers.insert(LSiteMakers::value_type(pDOMsite,siteMaker));
			for(size_t i=0,is=vals.size();i<is;++i) {
				siteMaker->siteParams[i] = vals[i];
			}
			siteMaker->initMaker = mInitMakers[pDOMinit];
			siteMaker->normMaker = mNormMakers[pDOMnorm];
			siteMaker->inputIndex = mSiteInputs[pDOMsite];
		}
	}

	//handle the <block> elements
	const DOMNodeList* pDOMblockList = GetElementList(setupDoc,XMLStrDefs::block);
	for(XMLSize_t i5=0,is5=pDOMblockList->getLength();i5<is5;++i5) {
		//get the current element
		const DOMElement* pDOMblock = GetElement(pDOMblockList,i5);
		const DOMElement* pDOMblockParams = GetElement(pDOMblock,XMLStrDefs::blockParams,0);
		const XMLCh* typeXCh = pDOMblock->getAttribute(XMLStrDefs::type);
		//check its type
		const DOMElement* pDOMvalBlock = GetType(pDOMblock,valDoc,eHandler);

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalBlock,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMblockParams,pDOMvalBlock,eHandler,pDOMblock,
			pDefaultsHandler->GetParams(pDOMblock),pDefaultsHandler->GetParams(typeXCh));

		//check the combination of <integrationSite> locations
		const DOMNodeList* pDOMsiteList = GetElementList(pDOMblock,XMLStrDefs::integrationSite);
		std::valarray<size_t> siteLocations(std::numeric_limits<size_t>::max(),pDOMsiteList->getLength());
		for(XMLSize_t s1=0,ss1=pDOMsiteList->getLength();s1<ss1;++s1) {
			const DOMElement* pDOMsite = GetElement(pDOMsiteList,s1);
			size_t locnum = s1;
			if (pDOMsite->hasAttribute(XMLStrDefs::location)) {
				locnum = XMLStringUtil::XML2Int(valDoc->getElementById(pDOMsite->getAttribute(XMLStrDefs::location))->getAttribute(XMLStrDefs::nr));		
			}
			if ((locnum >= ss1) || (siteLocations[locnum] < std::numeric_limits<size_t>::max())) {
				CErrorHandler::PrepareError("Wrong combination of <integrationSite> locations.",pDOMblock,eHandler);
			}
			else {
				siteLocations[locnum] = s1;
			}
		}

		const DOMElement* pDOMoutput = GetElement(pDOMblock,XMLStrDefs::outputFunction,0);
		if (!pDOMoutput) {//not locally defined, look in <targetDefaults>
			pDOMoutput = pDefaultsHandler->GetObject(pDOMblock,XMLStrDefs::outputFunction);
		}
		if (!pDOMoutput) {//now look in <typeDefaults>
			pDOMoutput = pDefaultsHandler->GetOutputFunction(siteLocations.size());
		}
		if (!pDOMoutput) {
			CErrorHandler::PrepareError("No <outputFunction> defined.",pDOMblock,eHandler);
		}

		size_t allowedsites = XMLStringUtil::XML2Int(GetType(pDOMoutput,valDoc,eHandler)->getAttribute(XMLStrDefs::numSites));
		if (allowedsites && (allowedsites != siteLocations.size())) {
			CErrorHandler::PrepareError("<outputFunction> not suitable for number of <integrationSite> elements.",pDOMblock,eHandler);
		}
		
		//now that all checks have completed, create the blockMaker if needed
		if (create) {
			std::string idstr = XMLStringUtil::XML2Str(pDOMblock->getAttribute(XMLStrDefs::id));
			SBlockMaker* blockMaker = new SBlockMaker(XMLStringUtil::XML2Str(typeXCh),idstr);
			mBlockMakers.insert(LBlockMakers::value_type(pDOMblock,blockMaker));
			for(size_t i=0,is=vals.size();i<is;++i) {
				blockMaker->blockParams[i] = vals[i];
			}
			blockMaker->beginNode = mBlockOutputs[pDOMblock]->first;
			blockMaker->numNodes = mBlockOutputs[pDOMblock]->second;
			blockMaker->outputBlock = GetBool(pDOMblock,XMLStrDefs::outputBlock);
			blockMaker->outputMaker = mOutputMakers[pDOMoutput];
			size_t numsites = siteLocations.size();
			blockMaker->siteMakers.resize(numsites);
			for(size_t s2=0;s2<numsites;++s2) {
				blockMaker->siteMakers[s2] = mSiteMakers[GetElement(pDOMsiteList,siteLocations[s2])];
			}
		}
	}

	//handle the <network> elements, netList exists from building net structure
	for(XMLSize_t i6=0,is6=pDOMnetList->getLength();i6<is6;++i6) {
		//get the current element
		const DOMElement* pDOMnet = GetElement(pDOMnetList,i6);
		const DOMElement* pDOMnetParams = GetElement(pDOMnet,XMLStrDefs::netParams,0);
		const XMLCh* typeXCh = pDOMnet->getAttribute(XMLStrDefs::type);
		//check its type
		const DOMElement* pDOMvalNet = GetType(pDOMnet,valDoc,eHandler);

		//check parameter names and get parameter values
		std::valarray<double> vals(std::numeric_limits<double>::min(),GetElementList(pDOMvalNet,XMLStrDefs::param)->getLength());
		HandleParams(vals,pDOMnetParams,pDOMvalNet,eHandler,pDOMnet,
			pDefaultsHandler->GetParams(pDOMnet),pDefaultsHandler->GetParams(typeXCh));
		
		//now that all checks have completed, create the netMaker if needed
		if (create) {
			std::string idstr = XMLStringUtil::XML2Str(pDOMnet->getAttribute(XMLStrDefs::id));
			SNetworkMaker* netMaker = new SNetworkMaker(XMLStringUtil::XML2Str(typeXCh),idstr);
			mNetMakers.insert(LNetMakers::value_type(pDOMnet,netMaker));
			for(size_t i=0,is=vals.size();i<is;++i) {
				netMaker->netParams[i] = vals[i];
			}
			netMaker->numInputs = XMLStringUtil::XML2Int(pDOMnet->getAttribute(XMLStrDefs::inputs));
			const DOMNodeList* pDOMblockList = GetElementList(pDOMnet,XMLStrDefs::block);
			for(XMLSize_t b1=0,bs1=pDOMblockList->getLength();b1<bs1;++b1) {
				SBlockMaker* blockMaker = mBlockMakers[GetElement(pDOMblockList,b1)];
				netMaker->blockMakers.push_back(blockMaker);
				netMaker->numNodes += blockMaker->numNodes;
			}
		}
	}
}

SNetworkMaker* CDOMNetImpl::GetNetMaker(const DOMElement* el)
{
	if (mNetMakers.find(el) != mNetMakers.end())
		return mNetMakers[el];
	else
		return 0;
}
	
SMaker* CDOMNetImpl::GetMaker(const DOMElement* el)
{
	if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::initialisation)) {
		if (mInitMakers.find(el) != mInitMakers.end())
			return mInitMakers[el];
	}
	else if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::normalisation)) {
		if (mNormMakers.find(el) != mNormMakers.end())
			return mNormMakers[el];
	}
	else if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::outputFunction)) {
		if (mOutputMakers.find(el) != mOutputMakers.end())
			return mOutputMakers[el];
	}
	else if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::integrationSite)) {
		if (mSiteMakers.find(el) != mSiteMakers.end())
			return mSiteMakers[el];
	}
	else if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::block)) {
		if (mBlockMakers.find(el) != mBlockMakers.end())
			return mBlockMakers[el];
	}
	else if (XMLStringUtil::Equals(el->getTagName(),XMLStrDefs::network)) {
		if (mNetMakers.find(el) != mNetMakers.end())
			return mNetMakers[el];
	}
	return 0;
}

std::valarray<double>* CDOMNetImpl::GetWeightVals(const DOMElement* el)
{
	if (mWeightVals.find(el) != mWeightVals.end())
		return mWeightVals[el];
	else
		return 0;
}

void CDOMNetImpl::ReleaseAll()
{
	for(LInputBlockIndices::iterator it01 = mInputBlocks.begin(),ite01 = mInputBlocks.end();it01 != ite01;++it01) {
		delete it01->second;
		it01->second = 0;
	}
	mInputBlocks.clear();
	for(LSiteIndices::iterator it02 = mSiteInputs.begin(),ite02 = mSiteInputs.end();it02 != ite02;++it02) {
		delete it02->second;
		it02->second = 0;
	}
	mSiteInputs.clear();
	for(LBlockIndices::iterator it03 = mBlockOutputs.begin(),ite03 = mBlockOutputs.end();it03 != ite03;++it03) {
		delete it03->second;
		it03->second = 0;
	}
	mBlockOutputs.clear();
	for(LWeightVals::iterator it0=mWeightVals.begin(),ite0=mWeightVals.end();it0 != ite0;++it0) {
		delete it0->second;
		it0->second = 0;
	}
	mWeightVals.clear();
	for(LInitMakers::iterator it1=mInitMakers.begin(),ite1=mInitMakers.end();it1 != ite1;++it1) {
		delete it1->second;
		it1->second = 0;
	}
	mInitMakers.clear();
	for(LNormMakers::iterator it2=mNormMakers.begin(),ite2=mNormMakers.end();it2 != ite2;++it2) {
		delete it2->second;
		it2->second = 0;
	}
	mNormMakers.clear();
	for(LOutputMakers::iterator it3=mOutputMakers.begin(),ite3=mOutputMakers.end();it3 != ite3;++it3) {
		delete it3->second;
		it3->second = 0;
	}
	mOutputMakers.clear();
	for(LSiteMakers::iterator it4=mSiteMakers.begin(),ite4=mSiteMakers.end();it4 != ite4;++it4) {
		delete it4->second;
		it4->second = 0;
	}
	mSiteMakers.clear();
	for(LBlockMakers::iterator it5=mBlockMakers.begin(),ite5=mBlockMakers.end();it5 != ite5;++it5) {
		delete it5->second;
		it5->second = 0;
	}
	mBlockMakers.clear();
	for(LNetMakers::iterator it6=mNetMakers.begin(),ite6=mNetMakers.end();it6 != ite6;++it6) {
		delete it6->second;
		it6->second = 0;
	}
	mNetMakers.clear();
}

} //end namespace CORINET




