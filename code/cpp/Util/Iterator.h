/*********************************************************************************************
 * Name      :  Iterator.h
 *
 * Purpose   :  Iterators for addressing elements in a valarray in different ways.
 *				They are used throughout model, task and event classes for various purposes.
 *				Adapted from Stoustrup's "C++ Programming Language" Chapter 22.
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

#include <Platform/Platform.h>

#ifndef CORINET_ITERATOR
#define CORINET_ITERATOR

#include <valarray>
#include <vector>

namespace CORINET {

class SubArrayIterator {
	double* pBegin;
	double* pEnd;
	double* pCurrent;
	friend class SubArrayIteratorConst;
public:
	SubArrayIterator(std::valarray<double>* const pv,size_t b,size_t s) 
		: pBegin(&((*pv)[b])),pEnd(&((*pv)[b+s])),pCurrent(0) {}
	~SubArrayIterator() {}

	//assignment operator
	SubArrayIterator& operator=(const SubArrayIterator& it) {
		if (this != &it) {
			pBegin = it.pBegin;
			pEnd = it.pEnd;
			pCurrent = it.pCurrent;
		}
		return *this;
	}

	void begin() {pCurrent = pBegin;}
	bool end() const {return (pCurrent == pEnd);}
	size_t size() const {return (pEnd-pBegin);}

	SubArrayIterator& operator++() {++pCurrent;return *this;}
	double& operator*() {return *pCurrent;}
	double& operator[](size_t i) {return *(pBegin + i);}
};

class SubArrayIteratorConst {
	double* pBegin;
	double* pEnd;
	double* pCurrent;
public:
	SubArrayIteratorConst(std::valarray<double>* const pv,size_t b,size_t s) 
		: pBegin(&((*pv)[b])),pEnd(&((*pv)[b+s])),pCurrent(0) {}
	~SubArrayIteratorConst() {}

	//copy constructors
	SubArrayIteratorConst(const SubArrayIteratorConst& it) : pBegin(it.pBegin),pEnd(it.pEnd),pCurrent(it.pCurrent) {}
	SubArrayIteratorConst(const SubArrayIterator& it) : pBegin(it.pBegin),pEnd(it.pEnd),pCurrent(it.pCurrent) {}

	//assignment operator
	SubArrayIteratorConst& operator=(const SubArrayIteratorConst& it) {
		if (this != &it) {
			pBegin = it.pBegin;
			pEnd = it.pEnd;
			pCurrent = it.pCurrent;
		}
		return *this;
	}

	void begin() {pCurrent = pBegin;}
	bool end() const {return (pCurrent == pEnd);}
	size_t size() const {return (pEnd-pBegin);}

	SubArrayIteratorConst& operator++() {++pCurrent;return *this;}
	double operator*() const {
		return *pCurrent;
	}
	double operator[](size_t i) const {return *(pBegin + i);}
};

class SliceIterator {
	size_t mStride;
	double* pBegin;
	double* pEnd;
	double* pCurrent;
	friend class SliceIteratorConst;
public:
	SliceIterator(std::valarray<double>* const pv,size_t b,size_t si,size_t str) 
		: mStride(str),pBegin(&((*pv)[b])),pEnd(&((*pv)[b+si*str])),pCurrent(0) {}
	~SliceIterator() {}

	void begin() {pCurrent = pBegin;}
	bool end() const {return (pCurrent >= pEnd);}
	size_t size() const {return (pEnd-pBegin)/mStride;}

	SliceIterator& operator++() {pCurrent+=mStride;return *this;}
	double& operator*() {return *pCurrent;}
	double& operator[](size_t i) {return *(pBegin + i*mStride);}
};

class SliceIteratorConst {
	size_t mStride;
	double* pBegin;
	double* pEnd;
	double* pCurrent;
	friend class SliceIterator;
public:
	SliceIteratorConst(std::valarray<double>* const pv,size_t b,size_t si,size_t str) 
		: mStride(str),pBegin(&((*pv)[b])),pEnd(&((*pv)[b+si*str])),pCurrent(0) {}
	~SliceIteratorConst() {}

	//copy constructors
	SliceIteratorConst(const SliceIteratorConst& it) : mStride(it.mStride),pBegin(it.pBegin),pEnd(it.pEnd),pCurrent(it.pCurrent) {}
	SliceIteratorConst(const SliceIterator& it) : mStride(it.mStride),pBegin(it.pBegin),pEnd(it.pEnd),pCurrent(it.pCurrent) {}

	void begin() {pCurrent = pBegin;}
	bool end() const {return (pCurrent >= pEnd);}
	size_t size() const {return (pEnd-pBegin)/mStride;}

	SliceIteratorConst& operator++() {pCurrent+=mStride;return *this;}
	double operator*() const {return *pCurrent;}
	double operator[](size_t i) const {return *(pBegin + i*mStride);}
};

class IndirectIteratorConst {
	std::valarray<double>* pVals;
	const std::valarray<size_t>* pIndices;
	size_t mSize;
	size_t mCurrent;
	friend class IndirectIterator;
public:
	IndirectIteratorConst(std::valarray<double>* pv,const std::valarray<size_t>* const pi) 
		: pVals(pv),pIndices(pi),mSize(pi->size()),mCurrent(0) {}
	~IndirectIteratorConst() {}

	void begin() {mCurrent = 0;}
	bool end() const {return (mCurrent == mSize);}
	size_t size() const {return mSize;}

	IndirectIteratorConst& operator++() {++mCurrent;return *this;}
	double operator*() const {return (*pVals)[(*pIndices)[mCurrent]];}
	double operator[](size_t i) const {return (*pVals)[(*pIndices)[i]];}
};

class IndirectIterator {
	std::valarray<double>* pVals;
	const std::valarray<size_t>* pIndices;
	size_t mSize;
	size_t mCurrent;
public:
	IndirectIterator(std::valarray<double>* const pv,const std::valarray<size_t>* const pi) 
		: pVals(pv),pIndices(pi),mSize(pi->size()),mCurrent(0) {}
	~IndirectIterator() {}

	//copy constructors
	IndirectIterator(const IndirectIteratorConst& it) : pVals(it.pVals),pIndices(it.pIndices),mSize(it.mSize),mCurrent(it.mCurrent) {}
	IndirectIterator(const IndirectIterator& it) : pVals(it.pVals),pIndices(it.pIndices),mSize(it.mSize),mCurrent(it.mCurrent) {}

	void begin() {mCurrent = 0;}
	bool end() const {return (mCurrent == mSize);}
	size_t size() const {return mSize;}

	IndirectIterator& operator++() {++mCurrent;return *this;}
	double& operator*() {return (*pVals)[(*pIndices)[mCurrent]];}
	double& operator[](size_t i) {return (*pVals)[(*pIndices)[i]];}
};



class MultipleSubArrayIterator {//this is not a random-access iterator, no operator[], no size() function
	size_t mCurrentSubArray;
	std::vector<SubArrayIterator*> mSubArrays;
public:
	MultipleSubArrayIterator() : mCurrentSubArray(0),mSubArrays() {}
	~MultipleSubArrayIterator() {}
	void AddSubArray(SubArrayIterator* it) {mSubArrays.push_back(it);}

	void begin() {
		mCurrentSubArray = 0;
		if (mSubArrays.size())
			mSubArrays[0]->begin();
	}
	bool end() const {
		if (!mSubArrays.size())
			return true;
		if (mSubArrays[mCurrentSubArray]->end() && (mCurrentSubArray == (mSubArrays.size() - 1)))
			return true;	
		return false;
	}
	MultipleSubArrayIterator& operator++() {
		mSubArrays[mCurrentSubArray]->operator++();
		if (mSubArrays[mCurrentSubArray]->end() && (mCurrentSubArray != (mSubArrays.size() - 1))) {
			mSubArrays[++mCurrentSubArray]->begin();
		}
			
		return *this;
	}
	double& operator*() {return mSubArrays[mCurrentSubArray]->operator*();}
};

class MultipleSubArrayIteratorConst {//this is not a random-access iterator, no operator[], no size() function
	size_t mCurrentSubArray;
	std::vector<SubArrayIteratorConst*> mSubArrays;
public:
	MultipleSubArrayIteratorConst() : mCurrentSubArray(0),mSubArrays() {}
	~MultipleSubArrayIteratorConst() {}
	void AddSubArray(SubArrayIteratorConst* it) {mSubArrays.push_back(it);}

	void begin() {
		mCurrentSubArray = 0;
		if (mSubArrays.size())
			mSubArrays[0]->begin();
	}
	bool end() const {
		if (!mSubArrays.size())
			return true;
		if (mSubArrays[mCurrentSubArray]->end() && (mCurrentSubArray == (mSubArrays.size() - 1)))
			return true;	
		return false;
	}
	MultipleSubArrayIteratorConst& operator++() {
		mSubArrays[mCurrentSubArray]->operator++();
		if (mSubArrays[mCurrentSubArray]->end() && (mCurrentSubArray != (mSubArrays.size() - 1))) {
			mSubArrays[++mCurrentSubArray]->begin();
		}
			
		return *this;
	}

	double operator*() const {return mSubArrays[mCurrentSubArray]->operator*();}
};

class MatrixIterator {
	std::valarray<double>* pVals;
	size_t mRows;
	size_t mCols;
	double* pBegin;
	double* pEnd;
	double* pCurrent;	
public:
	MatrixIterator(std::valarray<double>* const pv,size_t r) 
		: pVals(pv),mRows(r),mCols(pv->size()/r),pBegin(&((*pv)[0])),pEnd(&((*pv)[pv->size()])),pCurrent(0) {}
	~MatrixIterator() {}

	void begin() {pCurrent = pBegin;}
	bool end() const {return (pCurrent == pEnd);}
	size_t size() const {return pVals->size();}
	size_t rows() const {return mRows;}
	size_t columns() const {return mCols;}

	MatrixIterator& operator++() {++pCurrent;return *this;}
	double& operator*() {return *pCurrent;}
	double& operator[](size_t i) {return *(pBegin + i);}
	double& operator()(size_t r,size_t c) {return *(pBegin + c*mRows + r);}

	typedef SliceIterator RowIterator;
	typedef SubArrayIterator ColIterator;
	RowIterator GetRow(size_t r) {return RowIterator(pVals,r,mCols,mRows);}
	ColIterator GetCol(size_t c) {return ColIterator(pVals,c*mRows,mRows);}
};

class MatrixIteratorConst {
	std::valarray<double>* pVals;
	size_t mRows;
	size_t mCols;
	double* pBegin;
	double* pEnd;
	double* pCurrent;	
public:
	MatrixIteratorConst(std::valarray<double>* const pv,size_t r) 
		: pVals(pv),mRows(r),mCols(pv->size()/r),pBegin(&((*pv)[0])),pEnd(&((*pv)[pv->size()])),pCurrent(0) {}
	~MatrixIteratorConst() {}

	void begin() {pCurrent = pBegin;}
	bool end() const {return (pCurrent == pEnd);}
	size_t size() const {return pVals->size();}
	size_t rows() const {return mRows;}
	size_t columns() const {return mCols;}

	MatrixIteratorConst& operator++() {++pCurrent;return *this;}
	double operator*() const {return *pCurrent;}
	double operator[](size_t i) const {return *(pBegin + i);}
	double operator()(size_t r,size_t c) const {return *(pBegin + c*mRows + r);}

	typedef SliceIteratorConst RowIteratorConst;
	typedef SubArrayIteratorConst ColIteratorConst;
	RowIteratorConst GetRow(size_t r) {return RowIteratorConst(pVals,r,mCols,mRows);}
	ColIteratorConst GetCol(size_t c) {return ColIteratorConst(pVals,c*mRows,mRows);}
};


} //namespace CORINET

#endif //CORINET_ITERATOR


