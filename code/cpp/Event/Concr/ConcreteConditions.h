/*********************************************************************************************
 * Name      :  ConcreteConditions.h
 *
 * Purpose   :  Function objects implementing the operators for conditions in event handlers.
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

#ifndef CORINET_CONDITIONCONCR
#define CORINET_CONDITIONCONCR

#include <Event/Impl/ConditionImpl.h>

namespace CORINET {

class FCMultiple : public FConditionImpl {
public:
	bool operator()(double) const;
};

class FCEquals : public FConditionImpl {
public:
	bool operator()(double) const;
};

class FCGT : public FConditionImpl {
public:
	bool operator()(double) const;
};

class FCGTE : public FConditionImpl {
public:
	bool operator()(double) const;
};

class FCLT : public FConditionImpl {
public:
	bool operator()(double) const;
};

class FCLTE : public FConditionImpl {
public:
	bool operator()(double) const;
};

} //end namespace CORINET

#endif //CORINET_CONDITIONCONCR

