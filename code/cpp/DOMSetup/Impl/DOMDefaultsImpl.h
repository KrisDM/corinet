/*********************************************************************************************
 * Name      :  DOMDefaultsImpl.h
 *
 * Purpose   :  Implementation class handling the defaults in an experiment setup document.
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

#ifndef CORINET_DOMDEFAULTSIMPL
#define CORINET_DOMDEFAULTSIMPL

#include <DOMSetup/DOMDefaults.h>
#include <string>
#include <map>


namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

class CDOMDefaultsImpl : public CDOMDefaults {
	typedef std::map<const DOMElement*,std::vector<const DOMElement*> > LTarget2Vec;
	typedef std::map<const std::string,std::vector<const DOMElement*> > LType2Vec;
	typedef std::map<const DOMElement*,const DOMElement*> LTarget2El;
	typedef std::map<const std::string,const DOMElement*> LType2El;
	typedef std::map<const size_t,const DOMElement*> LNumSites2El;

	LTarget2Vec mParamTargetDefaults;
	LTarget2El mInitTargetDefaults;
	LTarget2El mNormTargetDefaults;
	LTarget2El mOutputTargetDefaults;
	LTarget2El mAttenuationTargetDefaults;
	LTarget2El mNoiseTargetDefaults;
	LTarget2El mPatternSetTargetDefaults;
	LTarget2El mDataSourceTargetDefaults;
	LType2Vec mParamTypeDefaults;
	LType2El mInitTypeDefaults;
	LType2El mNormTypeDefaults;
	LNumSites2El mOutputTypeDefaults;
	LType2El mAttenuationTypeDefaults;
	LType2El mNoiseTypeDefaults;

	void AddParamsFromList(const DOMNodeList*,std::vector<const DOMElement*>&,DOMErrorHandler*);
	void AddTargetParams(const DOMElement*,const DOMDocument*,DOMErrorHandler*);
	void AddTypeParams(const DOMElement*,const DOMDocument*,DOMErrorHandler*);
	void AddTargetObjects(LTarget2El&,const DOMElement*,const XMLCh*,const DOMDocument*,DOMErrorHandler*);
	void AddTypeObjects(LType2El&,const DOMElement*,const XMLCh*,DOMErrorHandler*);
	void AddOutputFunctions(LNumSites2El&,const DOMElement*,DOMErrorHandler*);
	void CheckTypes(const DOMElement*,const DOMDocument*,DOMErrorHandler*,const XMLCh*,const XMLCh* =0);
public:
	CDOMDefaultsImpl();
	virtual ~CDOMDefaultsImpl();

	void Handle(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler);

	//access functions
	const std::vector<const DOMElement*>* GetParams(const DOMElement*);
	const std::vector<const DOMElement*>* GetParams(const XMLCh*);
	const DOMElement* GetObject(const DOMElement*,const XMLCh*);
	const DOMElement* GetObject(const XMLCh*,const XMLCh*);
	const DOMElement* GetOutputFunction(size_t);

	//cleanup
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_DOMDEFAULTSIMPL



