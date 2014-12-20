/*********************************************************************************************
 * Name      :  ConcreteTasks.h
 *
 * Purpose   :  Specific tasks that can be used in experiments.
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

#ifndef CORINET_TASKCONCR
#define CORINET_TASKCONCR

#include <vector>
#include <Task/Impl/TaskImpl.h>
#include <Task/Misc/Patterns.h>
#include <Common/RandGen.h>

namespace CORINET {

class CTaskSet1 : public CTaskSimple {
	double mOn;
	double mProb;
	const size_t mSetSize;
	size_t mSetIndex;
	RandInt* pRS;
	RandDouble* pRD;
public:
	CTaskSet1(size_t*,double*);
	virtual ~CTaskSet1();
	void Initialise();
	void Generate(bool);
	void Seed(size_t);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CTaskSet2 : public CTaskSimple {
	double mOn;
	double mProbSame;
	const size_t mSetSize;
	bool bPresent;
	RandInt* pRI;
	RandDouble* pRD;
public:
	CTaskSet2(size_t*,double*);
	virtual ~CTaskSet2();
	void Initialise();
	void Generate(bool);
	void Seed(size_t);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CTaskSet3 : public CTaskSimple {
	double mOn;
	double mProb;
	const size_t mSetSize;
	size_t mSetIndex;
	RandDouble* pRD;
public:
	CTaskSet3(size_t*,double*);
	virtual ~CTaskSet3();
	void Initialise();
	void Generate(bool);
	void Seed(size_t);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CTaskAddExtraBits1 : public CTaskSimple {
	double mOn;
	double mNumBits;
	const size_t mSetSize;
	size_t mSetIndex;
	RandInt* pRSet;
	RandInt* pRBits;
	RandDouble* pRD;
public:
	CTaskAddExtraBits1(size_t*,double*);
	virtual ~CTaskAddExtraBits1();
	void Initialise();
	void Generate(bool);
	void Seed(size_t);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CTaskBits1 : public CTaskSimple {//all patterns of n bits from all zeros to all ones, for testing, not training
	double mOn;
	size_t mCurrent,mMax;
	RandInt* pRS;	
public:
	CTaskBits1(size_t*,double*);
	virtual ~CTaskBits1();
	void Initialise();
	void Generate(bool);
	void Seed(size_t);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CTaskBits2 : public CTaskSimple {//all patterns of a single 1 within an array of all zeros
	double mOn;
	size_t mCurrent;
	RandInt* pRS;	
public:
	CTaskBits2(size_t*,double*);
	virtual ~CTaskBits2();
	void Initialise();
	void Generate(bool);
	void Seed(size_t);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CTaskBars1 : public CTaskSimple {//horizontal and vertical bars in an nxn grid, each present with prob p
	double mOn;
	double mHorProb,mVerProb;
	HPattern2D mGrid;
	RandDouble* pRD;
public:
	CTaskBars1(size_t*,double*);
	virtual ~CTaskBars1();
	void Generate(bool);
	void Seed(size_t);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CTaskBars2 : public CTaskSimple {//horizontal OR vertical bars in grid, but never together
	double mOn;
	double mHorProb,mVerProb;
	HPattern2D mGrid;
	RandDouble* pRD;
public:
	CTaskBars2(size_t*,double*);
	virtual ~CTaskBars2();
	void Generate(bool);
	void Seed(size_t);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CTaskBars3 : public CTaskSimple {//a fixed number of bars in each image
	double mOn;
	size_t mNumBars;
	HPattern2D mGrid;
	RandInt* pRS;
public:
	CTaskBars3(size_t*,double*);
	virtual ~CTaskBars3();
	void Initialise();
	void Generate(bool);
	void Seed(size_t);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CTaskBars4 : public CTaskSimple {//a single bar that changes orientation with fixed probability	
	double mOn;
	size_t mNumOrientations;//either 2 or 4
	size_t mNumDiags;
	double mProbSame,mProbTwo;
	HPattern2D mGrid;
	RandDouble* pRD;
	RandInt* pRI;
	RandInt* pRS;
	size_t mCurOr;
public:
	CTaskBars4(size_t*,double*);
	virtual ~CTaskBars4();
	void Initialise();
	void Generate(bool);
	void Seed(size_t);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CTaskBars5 : public CTaskSimple {//each orientation is independently present or absent
	double mOn;
	size_t mNumOrientations;//either 2 or 4
	size_t mNumDiags;
	double mProbSame,mProbTwo;
	HPattern2D mGrid;
	RandDouble* pRD;
	RandInt* pRS;
	std::valarray<bool> bPresent;
public:
	CTaskBars5(size_t*,double*);
	virtual ~CTaskBars5();
	void Initialise();
	void Generate(bool);
	void Seed(size_t);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CTaskInsertIndependent : public CTaskComposite {//all inserts are treated independently
	double mOn;
public:
	CTaskInsertIndependent(size_t*,double*);
	virtual ~CTaskInsertIndependent();
	void Generate(bool);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

} //end namespace CORINET

#endif //CORINET_TASKCONCR
