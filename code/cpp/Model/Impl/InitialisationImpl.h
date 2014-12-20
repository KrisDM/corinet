/*********************************************************************************************
 * Name      :  InitialisationImpl.h
 *
 * Purpose   :  Function objects implementing different weight initialisation functions.
 *				This is the implementation class.
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

#ifndef CORINET_INITIALISATIONIMPL
#define CORINET_INITIALISATIONIMPL

#include <Model/Initialisation.h>

namespace CORINET {
	class RandDouble;

class FInitialisationImpl : public FInitialisation {
protected:
	RandDouble* pRandGen;
	const std::valarray<double>* pValues;
public:
	virtual ~FInitialisationImpl();
	void Initialise();
	void Reset();
	void SetWPointer(const std::valarray<double>*);
	void SetRandGen(RandDouble*);
};

} //end namespace CORINET

#endif //CORINET_INITIALISATIONIMPL
