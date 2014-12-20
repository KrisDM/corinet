/*********************************************************************************************
 * Name      :  DOMCommonImpl.h
 *
 * Purpose   :  Implementation class handling randGens, attenuation and noiseFunctions.
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

#ifndef CORINET_DOMCOMMONIMPL
#define CORINET_DOMCOMMONIMPL

#include <DOMSetup/DOMCommon.h>
#include <map>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

class CDOMCommonImpl : public CDOMCommon {
	typedef std::map<const DOMElement*,SRandGenMaker*> LRandMakers;
	typedef std::map<const DOMElement*,SAttenuationMaker*> LAttenuationMakers;
	typedef std::map<const DOMElement*,SNoiseFunctionMaker*> LNoiseMakers;

	LRandMakers mRandMakers;
	LAttenuationMakers mAttenuationMakers;
	LNoiseMakers mNoiseMakers;
public:
	CDOMCommonImpl();
	virtual ~CDOMCommonImpl();

	void Handle(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create);

	//access functions
	SRandGenMaker* GetRandMaker(const DOMElement*);
	SAttenuationMaker* GetAttenuationMaker(const DOMElement*);
	SNoiseFunctionMaker* GetNoiseMaker(const DOMElement*);
	SMaker* GetMaker(const DOMElement*);

	//cleanup
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_DOMCOMMONIMPL



