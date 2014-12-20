/*********************************************************************************************
 * Name      :  ConcreteInserts.h
 *
 * Purpose   :  Concrete classes for insert elements. They determine how patterns from
 *				simple tasks are inserted into composite tasks. 
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

#ifndef CORINET_INSERTCONCR
#define CORINET_INSERTCONCR

#include <Task/Impl/InsertImpl.h>

namespace CORINET {

class FInsertOverwrite : public FInsertImpl {
public:
	FInsertOverwrite(size_t*,double*);
	virtual ~FInsertOverwrite();

	void operator()(bool,MatrixIterator*);
};

class FInsertLarger : public FInsertImpl {
public:
	FInsertLarger(size_t*,double*);
	virtual ~FInsertLarger();

	void operator()(bool,MatrixIterator*);
};

class FInsertAddPixelValues : public FInsertImpl {
public:
	FInsertAddPixelValues(size_t*,double*);
	virtual ~FInsertAddPixelValues();

	void operator()(bool,MatrixIterator*);
};

} //end namespace CORINET

#endif //CORINET_INSERTCONCR
