/*********************************************************************************************
 * Name      :  ConcreteInserts.cpp
 *
 * Purpose   :  Concrete classes for insert elements. They determine how patterns from
 *				simple tasks are added to composite tasks. 
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

#include "ConcreteInserts.h"
#include <Util/Iterator.h>
#include <Task/Impl/TaskImpl.h>

namespace CORINET {

FInsertOverwrite::FInsertOverwrite(size_t* s,double* params) : FInsertImpl(s[0],s[1])
{

}

FInsertOverwrite::~FInsertOverwrite()
{

}

void FInsertOverwrite::operator()(bool randseq,MatrixIterator* pmat)
{
	const size_t tasks = mTasks.size();
	const size_t rows = pmat->rows();
	if (rows == 1) {
		for(size_t t1=0;t1<tasks;++t1) {
			mTasks[t1]->Generate(randseq);
			SubArrayIteratorConst* psubpat = mTasks[t1]->GetValuesConst();
			const size_t subsize = psubpat->size();
			for(size_t j=0;j<subsize;++j) {
				(*pmat)(0,mInColumn+j) = (*psubpat)[j];
			}
		}
	}
	else {
		for(size_t t2=0;t2<tasks;++t2) {
			mTasks[t2]->Generate(randseq);
			MatrixIteratorConst* psubmat = mTasks[t2]->GetPatternConst();
			const size_t subrows = psubmat->rows();
			const size_t subcols = psubmat->columns();
			for(size_t j=0;j<subcols;++j) {
				for(size_t i=0;i<subrows;++i) {
					(*pmat)(mInRow+i,mInColumn+j) = (*psubmat)(i,j);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////

FInsertLarger::FInsertLarger(size_t* s,double* params) : FInsertImpl(s[0],s[1])
{

}
	
FInsertLarger::~FInsertLarger()
{

}

void FInsertLarger::operator()(bool randseq,MatrixIterator* pmat)
{
	const size_t tasks = mTasks.size();
	const size_t rows = pmat->rows();
	if (rows == 1) {
		for(size_t t1=0;t1<tasks;++t1) {
			mTasks[t1]->Generate(randseq);
			SubArrayIteratorConst* psubpat = mTasks[t1]->GetValuesConst();
			const size_t subsize = psubpat->size();
			for(size_t j=0;j<subsize;++j) {
				if ((*pmat)(0,mInColumn+j) < (*psubpat)[j])
					(*pmat)(0,mInColumn+j) = (*psubpat)[j];
			}
		}
	}
	else {
		for(size_t t2=0;t2<tasks;++t2) {
			mTasks[t2]->Generate(randseq);
			MatrixIteratorConst* psubmat = mTasks[t2]->GetPatternConst();
			const size_t subrows = psubmat->rows();
			const size_t subcols = psubmat->columns();
			for(size_t j=0;j<subcols;++j) {
				for(size_t i=0;i<subrows;++i) {
					if ((*pmat)(mInRow+i,mInColumn+j) < (*psubmat)(i,j))
						(*pmat)(mInRow+i,mInColumn+j) = (*psubmat)(i,j);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////

FInsertAddPixelValues::FInsertAddPixelValues(size_t* s,double* params) : FInsertImpl(s[0],s[1])
{

}

FInsertAddPixelValues::~FInsertAddPixelValues()
{

}

void FInsertAddPixelValues::operator()(bool randseq,MatrixIterator* pmat)
{
	const size_t tasks = mTasks.size();
	const size_t rows = pmat->rows();
	if (rows == 1) {
		for(size_t t1=0;t1<tasks;++t1) {
			mTasks[t1]->Generate(randseq);
			SubArrayIteratorConst* psubpat = mTasks[t1]->GetValuesConst();
			const size_t subsize = psubpat->size();
			for(size_t j=0;j<subsize;++j) {
				(*pmat)(0,mInColumn+j) += (*psubpat)[j];
			}
		}
	}
	else {
		for(size_t t2=0;t2<tasks;++t2) {
			mTasks[t2]->Generate(randseq);
			MatrixIteratorConst* psubmat = mTasks[t2]->GetPatternConst();
			const size_t subrows = psubmat->rows();
			const size_t subcols = psubmat->columns();
			for(size_t j=0;j<subcols;++j) {
				for(size_t i=0;i<subrows;++i) {
					(*pmat)(mInRow+i,mInColumn+j) += (*psubmat)(i,j);
				}
			}
		}
	}
}

} //end namespace CORINET

