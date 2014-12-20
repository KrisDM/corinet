/*********************************************************************************************
 * Name      :  TaskImpl.cpp
 *
 * Purpose   :  General base classes for tasks. Some common functionality is defined here.
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

#include "TaskImpl.h"
#include <Util/Iterator.h>
#include <Util/Factory.h>
#include <Common/RandGen.h>
#include <Common/Attenuation.h>
#include <Common/NoiseFunction.h>
#include <Task/DataSource.h>
#include <Task/Insert.h>

namespace CORINET {

CTaskImpl::CTaskImpl(size_t columns,size_t rows,size_t store,size_t samplemethod) : mCurrentPattern(0.0,columns*rows),mStoreMax(store),
	mStoreIndex(0),pStoreRS(0),mStoreSet(store,0),pAttenuation(0),pNoise(0),mColumns(columns),mRows(rows),
	pValuesIterator(0),pValuesConstIterator(0),pPatternIterator(0),pPatternConstIterator(0)
{
	if (samplemethod == 0) {
		double p1 = static_cast<double>(mStoreMax);
		pStoreRS = CFactoryManager<RandInt>::CreateInstance("sequence",0,&p1);
	}
	else if (samplemethod == 1) {
		double p[2] = {0.0,static_cast<double>(mStoreMax)};
		pStoreRS = CFactoryManager<RandInt>::CreateInstance("uniInt",0,p);
	}
	pStoreRS->Seed();
}

CTaskImpl::~CTaskImpl()
{
	delete pStoreRS;
	delete pValuesConstIterator;
	delete pValuesIterator;
	delete pPatternConstIterator;
	delete pPatternIterator;
}

void CTaskImpl::Initialise()
{
	mStoreIndex = 0;
	pStoreRS->Reset();
}

void CTaskImpl::Finalise()
{
	for(size_t i=0;i<mStoreMax;++i) {
		delete mStoreSet[i];
		mStoreSet[i] = 0;
	}
}
void CTaskImpl::Seed(size_t s)
{
	pStoreRS->Seed(s+7894746);
}

bool CTaskImpl::Get(bool randseq)
{
	if (!mStoreMax) {//not storing any patterns
		mCurrentPattern = 0.0;
		return false;
	}
	else if (!mStoreSet.back()) {//storing patterns for reuse, but need to generate new one
		mCurrentPattern = 0.0;
		return false;
	}
	else {//reusing previously stored pattern
		if (randseq) {
			mCurrentPattern = *(mStoreSet[(*pStoreRS)()]);
		}
		else {
			mCurrentPattern = *(mStoreSet[mStoreIndex++]);
			if (mStoreIndex == mStoreMax) {
				mStoreIndex = 0;
			}
		}
		return true;
	}
}

void CTaskImpl::Put()
{
	if (mStoreMax && !mStoreSet.back()) {//storing patterns and storeset not full yet
		mStoreSet[mStoreIndex++] = new std::valarray<double>(mCurrentPattern);
		if (mStoreIndex == mStoreMax) {
			mStoreIndex = 0;
		}
	}
}

void CTaskImpl::Generate(bool randseq)
{
	if (!Get(randseq)) {
		//generate your pattern here
		Put();
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskImpl::SetPatternSet(const std::vector<const std::valarray<double>*>* const pset)
{

}

void CTaskImpl::SetDataSource(CDataSource*)
{

}

void CTaskImpl::AddInsert(FInsert*)
{

}

void CTaskImpl::SetAttenuation(FAttenuation* pat)
{
	pAttenuation = pat;
}

void CTaskImpl::SetNoise(FNoiseFunction* pn)
{
	pNoise = pn;
}

SubArrayIteratorConst* CTaskImpl::GetValuesConst()
{
	if (!pValuesConstIterator) 
		pValuesConstIterator = new SubArrayIteratorConst(&mCurrentPattern,0,mCurrentPattern.size());
	return pValuesConstIterator;
}
	
MatrixIteratorConst* CTaskImpl::GetPatternConst()
{
	if (!pPatternConstIterator)
		pPatternConstIterator = new MatrixIteratorConst(&mCurrentPattern,mRows);
	return pPatternConstIterator;
}

SubArrayIterator* CTaskImpl::GetValues()
{
	if (!pValuesIterator) 
		pValuesIterator = new SubArrayIterator(&mCurrentPattern,0,mCurrentPattern.size());
	return pValuesIterator;
}
	
MatrixIterator* CTaskImpl::GetPattern()
{
	if (!pPatternIterator)
		pPatternIterator = new MatrixIterator(&mCurrentPattern,mRows);
	return pPatternIterator;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

CTaskSimple::CTaskSimple(size_t* s) : CTaskImpl(s[0],s[1],s[2],s[4]),pPatternSet(0),pDataSource(0)
{
	
}

CTaskSimple::~CTaskSimple()
{
	
}

void CTaskSimple::Initialise()
{
	if (pDataSource)
		pDataSource->Initialise();
	CTaskImpl::Initialise();
}

void CTaskSimple::Finalise()
{
	if (pDataSource)
		pDataSource->Finalise();
	CTaskImpl::Finalise();
}

void CTaskSimple::Seed(size_t s)
{
	CTaskImpl::Seed(s);
}

void CTaskSimple::SetPatternSet(const std::vector<const std::valarray<double>*>* const pset) 
{
	pPatternSet = pset;
}

void CTaskSimple::SetDataSource(CDataSource* psrc)
{
	pDataSource = psrc;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

CTaskComposite::CTaskComposite(size_t* s) : CTaskImpl(s[0],s[1],s[2],s[4]),mInserts()
{
	
}

CTaskComposite::~CTaskComposite()
{

}

void CTaskComposite::Initialise()
{
	const size_t s = mInserts.size();
	for(size_t i=0;i<s;++i)
		mInserts[i]->Initialise();
	CTaskImpl::Initialise();
}

void CTaskComposite::Finalise()
{
	const size_t s = mInserts.size();
	for(size_t i=0;i<s;++i)
		mInserts[i]->Finalise();
	CTaskImpl::Finalise();
}

void CTaskComposite::Seed(size_t s)
{
	CTaskImpl::Seed(s);
}

void CTaskComposite::AddInsert(FInsert* pins)
{
	mInserts.push_back(pins);
}

} //end namespace CORINET

	




