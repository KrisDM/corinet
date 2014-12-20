/*********************************************************************************************
 * Name		:  InsertInsertTest1.h
 *
 * Purpose	:
 *
 * Notes	:  This file was generated by CORINET on Wed Dec 20 17:25:16 2006 
 *
 * Info		:  http://www.corinet.org
 *
 * Copyright:
 *
 * Licensce	: This program is free software; you can redistribute it and/or modify
 * 			   it under the terms of the GNU General Public License as published by
 * 			   the Free Software Foundation; either version 2 of the License, or
 * 			   (at your option) any later version.
 *
 * 			   This program is distributed in the hope that it will be useful,
 * 			   but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 			   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 			   GNU General Public License in $CORINETROOT/licenses for more details.
 *
 **********************************************************************************************/

#ifndef CORINET_INSERTINSERTTEST1
#define CORINET_INSERTINSERTTEST1

#include <Task/Impl/InsertImpl.h>

namespace CORINET {

class FInsertInsertTest1 : public FInsertImpl {
	
public:
	FInsertInsertTest1(size_t*,double*);
	virtual ~FInsertInsertTest1();
	void Initialise();
	void operator()(bool,MatrixIterator*);
	void Finalise();
	void SetParam(size_t,double);
	double GetParam(size_t);
};

} //end namespace CORINET

#endif //CORINET_INSERTINSERTTEST1

