/*********************************************************************************************
 * Name      :  ConcreteTasks.cpp
 *
 * Purpose   :  Concrete tasks.
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

#include <Util/Factory.h>
#include <Common/RandGen.h>
#include "ConcreteTasks.h"
#include <Common/Attenuation.h>
#include <Common/NoiseFunction.h>
#include <Task/DataSource.h>
#include <Task/Insert.h>
#include <cmath>

namespace CORINET {

CTaskSet1::CTaskSet1(size_t* s,double* params) : CTaskSimple(s),mOn(params[0]),mProb(params[1]),
												 mSetSize(s[3]),mSetIndex(0),pRS(0),pRD(0)
												 
{
	double p[2] = {0.0,1.0};
	pRD = CFactoryManager<RandDouble>::CreateInstance("uniDouble",0,p);
	pRD->Seed();
	if (s[4] == 0) {
		double p1 = static_cast<double>(mSetSize);
		pRS = CFactoryManager<RandInt>::CreateInstance("sequence",0,&p1);
	}
	else if (s[4] == 1) {
		p[1] = static_cast<double>(mSetSize);
		pRS = CFactoryManager<RandInt>::CreateInstance("uniInt",0,p);
	}
	pRS->Seed();
}

CTaskSet1::~CTaskSet1()
{
	delete pRS;
	delete pRD;
}

void CTaskSet1::Initialise()
{
	pRS->Reset();
	mSetIndex = 0;
	CTaskSimple::Initialise();
}

void CTaskSet1::Generate(bool randseq)
{
	if (!Get(randseq)) {
		if ((*pRD)() < mProb) {
			size_t patnum;
			if (randseq) 
				patnum = (*pRS)();
			else {
				patnum = mSetIndex++;
				if (mSetIndex == mSetSize)
					mSetIndex = 0;
			}
			if (pPatternSet) {
				mCurrentPattern = *((*pPatternSet)[patnum]);
			}
			else {
				mCurrentPattern = *(pDataSource->Get(patnum));
			}
			if (mOn != 1.0)
				mCurrentPattern *= mOn;
			Put();
		}
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskSet1::Seed(size_t s)
{
	pRD->Seed(s+938);
	pRS->Seed(s+17264);
	CTaskSimple::Seed(s);
}

void CTaskSet1::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mOn = v;
		break;
	case 1:
		mProb = v;
		break;
	}
}

double CTaskSet1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	case 1:
		v = mProb;
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////

CTaskSet2::CTaskSet2(size_t* s,double* params) : CTaskSimple(s),mOn(params[0]),mProbSame(params[1]),
												 mSetSize(s[3]),bPresent(false),pRI(0),pRD(0)
{
	double p[2] = {0.0,1.0};
	pRD = CFactoryManager<RandDouble>::CreateInstance("uniDouble",0,p);
	pRD->Seed();
	p[1] = static_cast<double>(mSetSize);
	pRI = CFactoryManager<RandInt>::CreateInstance("uniInt",0,p);
	pRI->Seed();
}

CTaskSet2::~CTaskSet2()
{
	delete pRD;
	delete pRI;
}

void CTaskSet2::Initialise()
{
	bPresent = false;
	CTaskSimple::Initialise();
}

void CTaskSet2::Generate(bool randseq)
{
	if (!Get(randseq)) {
		if ((*pRD)() > mProbSame)
			bPresent = !bPresent;//switch from current state
		if (bPresent) {
			size_t patnum = (*pRI)();//pick one random pattern from the set
			if (pPatternSet) {
				mCurrentPattern = *((*pPatternSet)[patnum]);
			}
			else {
				mCurrentPattern = *(pDataSource->Get(patnum));
			}
			if (mOn != 1.0)
				mCurrentPattern *= mOn;
			Put();
		}
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskSet2::Seed(size_t s)
{
	pRD->Seed(s+48722);
	pRI->Seed(s+9474922);
	CTaskSimple::Seed(s);
}

void CTaskSet2::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mOn = v;
		break;
	case 1:
		mProbSame = v;
		break;
	}
}

double CTaskSet2::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	case 1:
		v = mProbSame;
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////

CTaskSet3::CTaskSet3(size_t* s,double* params) : CTaskSimple(s),mOn(params[0]),mProb(params[1]),
												 mSetSize(s[3]),pRD(0)
												 
{
	double p[2] = {0.0,1.0};
	pRD = CFactoryManager<RandDouble>::CreateInstance("uniDouble",0,p);
	pRD->Seed();
}

CTaskSet3::~CTaskSet3()
{
	delete pRD;
}

void CTaskSet3::Initialise()
{
	mSetIndex = 0;
	CTaskSimple::Initialise();
}

void CTaskSet3::Generate(bool randseq)
{
	if (!Get(randseq)) {
		if (!randseq) {
			size_t p = mSetIndex++;
			if (mSetIndex == mSetSize)
				mSetIndex = 0;
			if (pPatternSet)
				mCurrentPattern = *((*pPatternSet)[p]);
			else
				mCurrentPattern = *(pDataSource->Get(p));
		}
		else {
			for(size_t p=0;p<mSetSize;++p) {
				if ((*pRD)() < mProb) {
					const std::valarray<double>* pat = 0;
					if (pPatternSet) {
						pat = (*pPatternSet)[p];
					}
					else {
						pat = pDataSource->Get(p);
					}
					for(size_t j=0,sp=pat->size();j<sp;++j) {
						if (mCurrentPattern[j] < (*pat)[j])
							mCurrentPattern[j] = (*pat)[j];
					}
				}
			}
		}
		if (mOn != 1.0)
			mCurrentPattern *= mOn;
		Put();
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskSet3::Seed(size_t s)
{
	pRD->Seed(s+938);
	CTaskSimple::Seed(s);
}

void CTaskSet3::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mOn = v;
		break;
	case 1:
		mProb = v;
		break;
	}
}

double CTaskSet3::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	case 1:
		v = mProb;
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////

CTaskAddExtraBits1::CTaskAddExtraBits1(size_t* s,double* params) : CTaskSimple(s),mOn(params[0]),
												mNumBits(static_cast<size_t>(params[1])),mSetSize(s[3]),mSetIndex(0),
												pRSet(0),pRBits(0),pRD(0)
												 
{
	if (s[4] == 0) {
		double p1 = static_cast<double>(mSetSize);
		pRSet = CFactoryManager<RandInt>::CreateInstance("sequence",0,&p1);
	}
	else if (s[4] == 1) {
		double p[2] = {0.0,static_cast<double>(mSetSize)};
		pRSet = CFactoryManager<RandInt>::CreateInstance("uniInt",0,p);
	}
	pRSet->Seed();
	double p2 = static_cast<double>(mCurrentPattern.size());
	pRBits = CFactoryManager<RandInt>::CreateInstance("sequence",0,&p2);
	pRBits->Seed();
	double p[2] = {0.0,1.0};
	pRD = CFactoryManager<RandDouble>::CreateInstance("uniDouble",0,p);
	pRD->Seed();
}

CTaskAddExtraBits1::~CTaskAddExtraBits1()
{
	delete pRSet;
	delete pRBits;
	delete pRD;
}

void CTaskAddExtraBits1::Initialise()
{
	pRSet->Reset();
	pRBits->Reset();
	CTaskSimple::Initialise();
}

void CTaskAddExtraBits1::Generate(bool randseq)
{
	if (!Get(randseq)) {
		size_t patnum;
		if (randseq) 
			patnum = (*pRSet)();
		else {
			patnum = mSetIndex++;
			if (mSetIndex == mSetSize)
				mSetIndex = 0;
		}
		if (pPatternSet) {
			mCurrentPattern = *((*pPatternSet)[patnum]);
		}
		else {
			mCurrentPattern = *(pDataSource->Get(patnum));
		}
		for(size_t i=0;i<mNumBits;++i) {
			size_t n = (*pRBits)();
			while (mCurrentPattern[n] > 0.0) {
				n = (*pRBits)();
			}
			mCurrentPattern[n] = 1.0;
		}
		pRBits->Reset();
		if (mOn != 1.0)
			mCurrentPattern *= mOn;
		Put();
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskAddExtraBits1::Seed(size_t s)
{
	pRD->Seed(s+938);
	pRSet->Seed(s+17264);
	pRBits->Seed(s+93838291);
	CTaskSimple::Seed(s);
}

void CTaskAddExtraBits1::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mOn = v;
		break;
	case 1:
		mNumBits = static_cast<size_t>(v);
		break;
	}
}

double CTaskAddExtraBits1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	case 1:
		v = static_cast<double>(mNumBits);
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////

CTaskBits1::CTaskBits1(size_t* s,double* params) : CTaskSimple(s),mOn(params[0]),mCurrent(0)
{
	mMax = static_cast<size_t>(pow(2,s[0]));
	if (s[4] == 0) {
		double p1 = static_cast<double>(mMax);
		pRS = CFactoryManager<RandInt>::CreateInstance("sequence",0,&p1);
	}
	else if (s[4] == 1) {
		double p[2] = {0.0,static_cast<double>(mMax)};
		pRS = CFactoryManager<RandInt>::CreateInstance("uniInt",0,p);
	}
	pRS->Seed();
}

CTaskBits1::~CTaskBits1()
{
	delete pRS;
}

void CTaskBits1::Initialise()
{
	pRS->Reset();
	CTaskSimple::Initialise();
}

void CTaskBits1::Generate(bool randseq)
{
	if (!Get(randseq)) {
		size_t patnum;
		if (randseq) 
			patnum = (*pRS)();
		else {
			patnum = mCurrent++;
			if (mCurrent == mMax)
				mCurrent = 0;
		}
		const size_t s = mCurrentPattern.size();
		size_t pow2 = 1;
		for(size_t i=s;i>0;--i) {
			if ((patnum/pow2)&0x1)
				mCurrentPattern[i-1] = 1.0;
			else 
				mCurrentPattern[i-1] = 0.0;
			pow2*=2;
		}
		if (mOn != 1.0)
			mCurrentPattern *= mOn;
		Put();
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskBits1::Seed(size_t s)
{
	pRS->Seed(s);
	CTaskSimple::Seed(s);
}

void CTaskBits1::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mOn = v;
		break;
	}
}

double CTaskBits1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////

CTaskBits2::CTaskBits2(size_t* s,double* params) : CTaskSimple(s),mOn(params[0]),mCurrent(0)
{
	if (s[4] == 0) {
		double p1 = static_cast<double>(s[0]);
		pRS = CFactoryManager<RandInt>::CreateInstance("sequence",0,&p1);
	}
	else if (s[4] == 1) {
		double p[2] = {0.0,static_cast<double>(s[0])};
		pRS = CFactoryManager<RandInt>::CreateInstance("uniInt",0,p);
	}
	pRS->Seed();
}

CTaskBits2::~CTaskBits2()
{
	delete pRS;
}

void CTaskBits2::Initialise()
{
	pRS->Reset();
	CTaskSimple::Initialise();
}

void CTaskBits2::Generate(bool randseq)
{
	if (!Get(randseq)) {
		size_t patnum;
		if (randseq) 
			patnum = (*pRS)();
		else {
			patnum = mCurrent++;
			if (mCurrent == mCurrentPattern.size())
				mCurrent = 0;
		}
		mCurrentPattern = 0.0;
		mCurrentPattern[patnum] = 1.0;
		if (mOn != 1.0)
			mCurrentPattern *= mOn;
		Put();
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskBits2::Seed(size_t s)
{
	pRS->Seed(s);
	CTaskSimple::Seed(s);
}

void CTaskBits2::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mOn = v;
		break;
	}
}

double CTaskBits2::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	}
	return v;
}

/////////////////////////////////////////////////////////////////////////////////////////////

CTaskBars1::CTaskBars1(size_t* s,double* params)  : CTaskSimple(s),mOn(params[0]),mHorProb(params[1]),mVerProb(params[2]),
													mGrid(&mCurrentPattern,s[1])
													
{
	double p[2] = {0.0,1.0};
	pRD = CFactoryManager<RandDouble>::CreateInstance("uniDouble",0,p);
	pRD->Seed();
}

CTaskBars1::~CTaskBars1()
{
	delete pRD;
}

void CTaskBars1::Generate(bool randseq)
{
	if (!Get(randseq)) {
		const size_t r = mGrid.rows();
		const size_t c = mGrid.columns();
		for(size_t i=0;i<r;++i) {
			if ((*pRD)() < mHorProb) 
				mGrid.SetRow(i,1.0);
		}
		for(size_t j=0;j<c;++j) {
			if ((*pRD)() < mVerProb) 
				mGrid.SetCol(j,1.0);
		}
		if (mOn != 1.0)
			mCurrentPattern *= mOn;
		Put();
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskBars1::Seed(size_t s)
{
	pRD->Seed(s);
	CTaskSimple::Seed(s);
}

void CTaskBars1::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mOn = v;
		break;
	case 1:
		mHorProb = v;
		break;
	case 2:
		mVerProb = v;
		break;
	}
}

double CTaskBars1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	case 1:
		v = mHorProb;
		break;
	case 2:
		v = mVerProb;
		break;
	}
	return v;
}

//////////////////////////////////////////////////////////////////////////////////////////////

CTaskBars2::CTaskBars2(size_t* s,double* params) : CTaskSimple(s),mOn(params[0]),mHorProb(params[1]),mVerProb(params[2]),
												   mGrid(&mCurrentPattern,s[1])
												   
{
	double p[2] = {0.0,1.0};
	pRD = CFactoryManager<RandDouble>::CreateInstance("uniDouble",0,p);
	pRD->Seed();
}

CTaskBars2::~CTaskBars2()
{
	delete pRD;
}

void CTaskBars2::Generate(bool randseq)
{
	if (!Get(randseq)) {
		if ((*pRD)() < 0.5) {//set only rows
			const size_t r = mGrid.rows();
			for(size_t i=0;i<r;++i) {
				if ((*pRD)() < mHorProb) 
					mGrid.SetRow(i,1.0);
			}
		}
		else {//set only columns
			const size_t c = mGrid.columns();
			for(size_t j=0;j<c;++j) {
			if ((*pRD)() < mVerProb) 
				mGrid.SetCol(j,1.0);
			}
		}
		if (mOn != 1.0)
			mCurrentPattern *= mOn;
		Put();
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskBars2::Seed(size_t s)
{
	pRD->Seed(s);
	CTaskSimple::Seed(s);
}

void CTaskBars2::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mOn = val;
		break;
	case 1:
		mHorProb = val;
		break;
	case 2:
		mVerProb = val;
		break;
	}
}

double CTaskBars2::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	case 1:
		v = mHorProb;
		break;
	case 2:
		v = mVerProb;
		break;
	}
	return v;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CTaskBars3::CTaskBars3(size_t* s,double* params) : CTaskSimple(s),mOn(params[0]),mGrid(&mCurrentPattern,s[1])
												   
{
	mNumBars = static_cast<size_t>(params[1]);
	double p1 = static_cast<double>(s[0]+s[1]);
	pRS = CFactoryManager<RandInt>::CreateInstance("sequence",0,&p1);
	pRS->Seed();
}

CTaskBars3::~CTaskBars3()
{
	delete pRS;
}

void CTaskBars3::Initialise()
{
	pRS->Reset();
	CTaskSimple::Initialise();
}

void CTaskBars3::Generate(bool randseq)
{
	if (!Get(randseq)) {
		for(size_t i=0;i<mNumBars;++i) {
			size_t n = (*pRS)();
			if (n<mGrid.rows()) 
				mGrid.SetRow(n,1.0);
			else 
				mGrid.SetCol(n-mGrid.rows(),1.0);
		}
		pRS->Reset();
		if (mOn != 1.0)
			mCurrentPattern *= mOn;
		Put();
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskBars3::Seed(size_t s)
{
	pRS->Seed(s);
	CTaskSimple::Seed(s);
}

void CTaskBars3::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mOn = v;
		break;
	case 1:
		mNumBars = static_cast<size_t>(v);
		break;
	}
}

double CTaskBars3::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	case 1:
		v = static_cast<double>(mNumBars);
		break;
	}
	return v;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
CTaskBars4::CTaskBars4(size_t* s,double* params) : CTaskSimple(s),mOn(params[0]),mProbSame(params[2]),mProbTwo(params[3]),
												   mGrid(&mCurrentPattern,s[1])
												   
{
	mNumDiags = s[0]>s[1]?s[1]:s[0];
	if (!(mNumDiags&0x1)) --mNumDiags;
	mNumOrientations = static_cast<size_t>(params[1]);
	if (mNumOrientations != 2 && mNumOrientations != 4)  {
		throw ETask("Error: parameter \"numOrientations\" should be 2 or 4.\n");
	}
	
	double p[2] = {0.0,1.0};
	pRD = CFactoryManager<RandDouble>::CreateInstance("uniDouble",0,p);
	pRD->Seed();
	p[1] = static_cast<double>(mNumOrientations);
	pRI = CFactoryManager<RandInt>::CreateInstance("uniInt",0,p);
	pRI->Seed();
	double p1 = static_cast<double>(s[0]>s[1]?s[0]:s[1]);
	pRS = CFactoryManager<RandInt>::CreateInstance("sequence",0,&p1);
	pRS->Seed();
	mCurOr = (*pRI)();
}

CTaskBars4::~CTaskBars4()
{
	delete pRD;
	delete pRI;
	delete pRS;
}

void CTaskBars4::Initialise()
{
	pRS->Reset();
	CTaskSimple::Initialise();
}

void CTaskBars4::Generate(bool randseq)
{
	if (!Get(randseq)) {
		if ((*pRD)()>mProbSame) {//generate a new orientation
			size_t newor;
			do {
				newor = (*pRI)();
			}
			while (mCurOr == newor);
			mCurOr = newor;
		}
		size_t numBars = ((*pRD)()<mProbTwo)?2:1; //determine if there are 1 or 2 bars
		for(size_t n=0;n<numBars;++n) {
			size_t b;
			switch (mCurOr) {
			case 0:
				do 
					b=(*pRS)();
				while (b>=mGrid.rows());
				mGrid.SetRow(b,1.0);
				break;
			case 1:
				do 
					b=(*pRS)();
				while (b>=mGrid.columns());
				mGrid.SetCol(b,1.0);
				break;
			case 2:
				do 
					b=(*pRS)();
				while (b>=mNumDiags);
				mGrid.SetDiagLRUp(b-mNumDiags/2,1.0);
				break;
			case 3:
				do 
					b=(*pRS)();
				while (b>=mNumDiags);
				mGrid.SetDiagLRDown(b-mNumDiags/2,1.0);
				break;
			}
		}
		pRS->Reset();
		if (mOn != 1.0)
			mCurrentPattern *= mOn;
		Put();
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskBars4::Seed(size_t s)
{
	pRD->Seed(s);
	pRI->Seed(s+1373);
	pRS->Seed(s+13357);
	mCurOr = (*pRI)();
	CTaskSimple::Seed(s);
}

void CTaskBars4::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mOn = v;
		break;
	case 1:
		mNumOrientations = static_cast<size_t>(v);
		break;
	case 2:
		mProbSame = v;
		break;
	case 3:
		mProbTwo = v;
		break;
	}
}

double CTaskBars4::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	case 1:
		v = static_cast<double>(mNumOrientations);
		break;
	case 2:
		v = mProbSame;
		break;
	case 3:
		v = mProbTwo;
		break;
	}
	return v;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
CTaskBars5::CTaskBars5(size_t* s,double* params) : CTaskSimple(s),mOn(params[0]),mProbSame(params[2]),mProbTwo(params[3]),
									mGrid(&mCurrentPattern,s[1]),bPresent(false,static_cast<size_t>(params[1]))
												   
{
	mNumDiags = s[0]>s[1]?s[1]:s[0];
	if (!(mNumDiags&0x1)) --mNumDiags;
	mNumOrientations = static_cast<size_t>(params[1]);
	if (mNumOrientations != 2 && mNumOrientations != 4)  {
		throw ETask("Error: parameter \"numOrientations\" should be 2 or 4.\n");
	}
	double p[2] = {0.0,1.0};
	pRD = CFactoryManager<RandDouble>::CreateInstance("uniDouble",0,p);
	pRD->Seed();
	double p1 = static_cast<double>(s[0]>s[1]?s[0]:s[1]);
	pRS = CFactoryManager<RandInt>::CreateInstance("sequence",0,&p1);
	pRS->Seed();
}

CTaskBars5::~CTaskBars5()
{
	delete pRD;
	delete pRS;
}

void CTaskBars5::Initialise()
{
	pRS->Reset();
	CTaskSimple::Initialise();
}

void CTaskBars5::Generate(bool randseq)
{
	if (!Get(randseq)) {
		for(size_t i=0;i<mNumOrientations;++i) {
			if ((*pRD)()>mProbSame) 
				bPresent[i] = !bPresent[i];
			if (bPresent[i]) {
				size_t numBars = ((*pRD)()<mProbTwo)?2:1; //determine if there are 1 or 2 bars
				for(size_t n=0;n<numBars;++n) {
					size_t b;
					switch (i) {
					case 0:
						do 
							b=(*pRS)();
						while (b>=mGrid.rows());
						mGrid.SetRow(b,1.0);
						break;
					case 1:
						do 
							b=(*pRS)();
						while (b>=mGrid.columns());
						mGrid.SetCol(b,1.0);
						break;
					case 2:
						do 
							b=(*pRS)();
						while (b>=mNumDiags);
						mGrid.SetDiagLRUp(b-mNumDiags/2,1.0);
						break;
					case 3:	
						do 
							b=(*pRS)();
						while (b>=mNumDiags);
						mGrid.SetDiagLRDown(b-mNumDiags/2,1.0);
						break;
					}
				}
				pRS->Reset();
			}
		}
		if (mOn != 1.0)
			mCurrentPattern *= mOn;
		Put();
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}

void CTaskBars5::Seed(size_t s)
{
	pRD->Seed(s);
	pRS->Seed(s+13357);
	CTaskSimple::Seed(s);
}

void CTaskBars5::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mOn = v;
		break;
	case 1:
		mNumOrientations = static_cast<size_t>(v);
		break;
	case 2:
		mProbSame = v;
		break;
	case 3:
		mProbTwo = v;
		break;
	}
}

double CTaskBars5::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	case 1:
		v = mNumOrientations;
		break;
	case 2:
		v = mProbSame;
		break;
	case 3:
		v = mProbTwo;
		break;
	}
	return v;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

CTaskInsertIndependent::CTaskInsertIndependent(size_t* s,double* params) : CTaskComposite(s),mOn(params[0])
{

}
	
CTaskInsertIndependent::~CTaskInsertIndependent()
{

}
	
void CTaskInsertIndependent::Generate(bool randseq)
{
	if (!Get(randseq)) {
		const size_t s = mInserts.size();
		MatrixIterator* pmat = GetPattern();
		for(size_t i=0;i<s;++i) {
			mInserts[i]->operator()(randseq,pmat);
		}
		if (mOn != 1.0)
			mCurrentPattern *= mOn;
		Put();
	}
	if (pAttenuation) (*pAttenuation)(*GetValues());
	if (pNoise) (*pNoise)(*GetValues());
}
	
void CTaskInsertIndependent::SetParam(size_t p,double v) 
{
	switch (p) {
	case 0:
		mOn = v;
		break;
	}
}
	
double CTaskInsertIndependent::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mOn;
		break;
	}
	return v;
}

} //end namespace CORINET

	




