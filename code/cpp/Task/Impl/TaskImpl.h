/*********************************************************************************************
 * Name      :  TaskImpl.h
 *
 * Purpose   :  Implementation of tasks. These are still not concrete tasks but general
 *				base classes that can be used to derive concrete tasks from.
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

#ifndef CORINET_TASKIMPL
#define CORINET_TASKIMPL

#include <Task/Task.h>
#include <valarray>
#include <vector>

namespace CORINET {
	class CDataSource;
	class FAttenuation;
	class FNoiseFunction;
	class FInsert;
	class RandInt;

class CTaskImpl : public CTask {//base implementation, functionality for storing and retrieving patterns
protected:
	std::valarray<double> mCurrentPattern; //the place that holds the current pattern
	const size_t mStoreMax; //the number of patterns to be stored in memory for reuse
	size_t mStoreIndex; //the current index into stored patterns
	RandInt* pStoreRS; //when patterns of mStoreSet need to be presented in random order
	std::vector<std::valarray<double>*> mStoreSet; //finished patterns that are stored for reuse
	FAttenuation* pAttenuation;
	FNoiseFunction* pNoise;	
protected:
	const size_t mColumns;
	const size_t mRows;
	SubArrayIterator* pValuesIterator;
	SubArrayIteratorConst* pValuesConstIterator;
	MatrixIterator* pPatternIterator;
	MatrixIteratorConst* pPatternConstIterator;
protected:
	bool Get(bool); //function that prepares mCurrentPattern, if it returns true, mCurrentPattern is already finished pattern
	void Put(); //function that potentially stores the pattern in mStoreSet
public:
	CTaskImpl(size_t,size_t,size_t,size_t);
	virtual ~CTaskImpl();
	void Initialise();
	void Finalise();
	void Generate(bool);
	void Seed(size_t); //to seed all internal random number generators to predefined values (pNoise is external)
	
	//access functions for event handlers etc.
	SubArrayIteratorConst* GetValuesConst();
	SubArrayIterator* GetValues();
	MatrixIteratorConst* GetPatternConst();
	MatrixIterator* GetPattern();

	//initialisation functions
	virtual void SetPatternSet(const std::vector<const std::valarray<double>*>* const);
	virtual void SetDataSource(CDataSource*);
	virtual void SetAttenuation(FAttenuation*);
	virtual void SetNoise(FNoiseFunction*);
	virtual void AddInsert(FInsert*);
};

class CTaskSimple : public CTaskImpl {//base class for all simple tasks
protected:
	const std::vector<const std::valarray<double>*>* pPatternSet;
	CDataSource* pDataSource;
public:
	CTaskSimple(size_t*);
	virtual ~CTaskSimple();
	void Initialise();
	void Finalise();
	void Seed(size_t);

	void SetDataSource(CDataSource*);
	void SetPatternSet(const std::vector<const std::valarray<double>*>* const);
};

class CTaskComposite : public CTaskImpl {//base class for all composite tasks
protected:
	std::vector<FInsert*> mInserts;
public:
	CTaskComposite(size_t*);
	virtual ~CTaskComposite();
	void Initialise();
	void Finalise();
	void Seed(size_t);

	void AddInsert(FInsert*);
};
	
} //end namespace CORINET

#endif //CORINET_TASKIMPL
