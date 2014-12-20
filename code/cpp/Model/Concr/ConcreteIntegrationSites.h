/*********************************************************************************************
 * Name      :  ConcreteIntegrationSites.h
 *
 * Purpose   :  Concrete types of integration sites. There are non-learning integration sites that only 
 *				specify an integration rule, and learning integration sites which additionally
 *				specify a learning rule.
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

#ifndef CORINET_INTEGRATIONSITECONCR
#define CORINET_INTEGRATIONSITECONCR

#include <Model/Impl/IntegrationSiteImpl.h>

namespace CORINET {

//////////////////////////////////////////////////////////////
//Integration sites that do not learn
//////////////////////////////////////////////////////////////

class CIntegrationSiteAddInt1 : public CIntegrationSiteImpl {
public:
	CIntegrationSiteAddInt1(size_t*,double*);
	virtual ~CIntegrationSiteAddInt1();
	bool Integrate(size_t,HBlockOutput&);
};

class CIntegrationSiteMaxInt1 : public CIntegrationSiteImpl {
protected:
	std::valarray<size_t> mMaxIndex;
public:
	CIntegrationSiteMaxInt1(size_t*,double*);
	virtual ~CIntegrationSiteMaxInt1();
	bool Integrate(size_t,HBlockOutput&);
	SynapseWrapper* GetSynapses();
};

class CIntegrationSiteCompInt1 : public CIntegrationSiteImpl {
	double mCurrentAlpha,mAlphaMax,mAlphaStep,mCompleteIntegration;
	std::valarray<double> yTemp;
protected:
	std::valarray<double> mMaxVals1;
	std::valarray<double> mMaxVals2;
	std::valarray<size_t> mMaxIndex;
public:
	CIntegrationSiteCompInt1(size_t*,double*);
	virtual ~CIntegrationSiteCompInt1();
	void Reset();
	bool Integrate(size_t,HBlockOutput&);
	void SetParam(size_t,double);
	double GetParam(size_t);
	SynapseWrapper* GetSynapses();
};

//////////////////////////////////////////////////////////////////////
//Integration sites that learn
//////////////////////////////////////////////////////////////////////		

class CIntegrationSiteDisj1 : public CIntegrationSiteMaxInt1 {//this class can do trace and non-trace learning
	double mLearningRate,mTrace,mNTrace;
	std::valarray<double> mTraceOutputs;
public:
	CIntegrationSiteDisj1(size_t*,double*);
	virtual ~CIntegrationSiteDisj1();
	bool Learn(size_t,HBlockOutput&);
	void Initialise();
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CIntegrationSiteDisj2 : public CIntegrationSiteMaxInt1 {//this one always uses the previous activity for learning
	double mLearningRate;
	std::valarray<double> mPrevOutputs;
public:
	CIntegrationSiteDisj2(size_t*,double*);
	virtual ~CIntegrationSiteDisj2();
	bool Learn(size_t,HBlockOutput&);
	void Initialise();
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CIntegrationSiteConj1 : public CIntegrationSiteCompInt1 {
	double mLearningRate,mNegLearningRate;
	std::valarray<double> xTemp;
public:
	CIntegrationSiteConj1(size_t*,double*);
	virtual ~CIntegrationSiteConj1();
	bool Learn(size_t,HBlockOutput&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CIntegrationSiteConj2 : public CIntegrationSiteCompInt1 {
	double mLearningRate,mNegLearningRate;
	std::valarray<double> xTemp;
public:
	CIntegrationSiteConj2(size_t*,double*);
	virtual ~CIntegrationSiteConj2();
	bool Learn(size_t,HBlockOutput&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

class CIntegrationSiteConj3 : public CIntegrationSiteCompInt1 {
	double mLearningRate;
	std::valarray<double> xTemp;
public:
	CIntegrationSiteConj3(size_t*,double*);
	virtual ~CIntegrationSiteConj3();
	bool Learn(size_t,HBlockOutput&);
	void SetParam(size_t,double);
	double GetParam(size_t);
};

} //end namespace CORINET

#endif //CORINET_INTEGRATIONSITECONCR

