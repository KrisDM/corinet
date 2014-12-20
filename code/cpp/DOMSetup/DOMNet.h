/*********************************************************************************************
 * Name      :  DOMNet.h
 *
 * Purpose   :  Interface for handling networks and its child elements.
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

#ifndef CORINET_DOMNET
#define CORINET_DOMNET

#include <Platform/Platform.h>
#include <xercesc/dom/DOM.hpp>
#include <valarray>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

	struct SNetworkMaker;
	struct SMaker;

class CDOMNet {
public:
	virtual ~CDOMNet() {}

	virtual void Handle(const DOMDocument* setupDoc,const DOMDocument* valDoc,DOMErrorHandler* eHandler,bool create) =0;

	//access functions
	virtual SNetworkMaker* GetNetMaker(const DOMElement*) =0;
	virtual SMaker* GetMaker(const DOMElement*) =0;
	virtual std::valarray<double>* GetWeightVals(const DOMElement*) =0;

	//cleanup
	virtual void ReleaseAll() =0;
};

} //end namespace CORINET

#endif //CORINET_DOMNET



