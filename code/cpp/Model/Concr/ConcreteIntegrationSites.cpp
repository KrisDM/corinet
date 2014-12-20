/*********************************************************************************************
 * Name      :  ConcreteIntegrationSites.cpp
 *
 * Purpose   :  Definition of concrete types of integration sites.
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

#include "ConcreteIntegrationSites.h"
#include <Model/Normalisation.h>
#include <Model/Misc/Synapses.h>

namespace CORINET {

//////////////////////////////////////////////////////////////////////
//Integration sites that do not learn
//////////////////////////////////////////////////////////////////////

CIntegrationSiteAddInt1::CIntegrationSiteAddInt1(size_t* s,double*) 
		: CIntegrationSiteImpl(s[0],s[1])
{

}

CIntegrationSiteAddInt1::~CIntegrationSiteAddInt1()
{	
	
}

bool CIntegrationSiteAddInt1::Integrate(size_t nodes,HBlockOutput&)
{
	const size_t inputs = mWeights.NumInputs();
	mIntegrationVals = 0.0;
	for(size_t i=0;i<inputs;++i) {
		double inputval = (*pInputVals)[i];
		if (inputval < gPrecision)
			continue;
		for (size_t j=0;j<nodes;++j) {
			mIntegrationVals[j] += mWeights(i,j)*inputval;
		}
	}
	for(size_t j=0;j<nodes;++j) {
		if (mIntegrationVals[j] < gPrecision) {
			mIntegrationVals[j] = 0.0;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////

CIntegrationSiteMaxInt1::CIntegrationSiteMaxInt1(size_t* s,double*)
	: CIntegrationSiteImpl(s[0],s[1]),mMaxIndex(s[1])
{

}

CIntegrationSiteMaxInt1::~CIntegrationSiteMaxInt1()
{
	
}

bool CIntegrationSiteMaxInt1::Integrate(size_t nodes,HBlockOutput&)
{
	const size_t inputs = mWeights.NumInputs();
	mMaxIndex = std::numeric_limits<size_t>::max();
	mIntegrationVals = 0.0;
	for(size_t i=0;i<inputs;++i) {
		double inputval = (*pInputVals)[i];
		if (inputval < gPrecision)
			continue;
		double maxwi = mWeights.MaxWForInputSpecial(i,nodes);
		for(size_t j=0;j<nodes;++j) {
			double maxwj = mWeights.MaxWForNodeSpecial(j);
			double wij = mWeights(i,j);
			if (maxwi && maxwj) {
				double temp = inputval*wij*wij/maxwi/maxwj;
				if (temp >= mIntegrationVals[j]) {
					mIntegrationVals[j] = temp;
					mMaxIndex[j] = i;
				}
			}
		}
	}
	for(size_t j=0;j<nodes;++j) {
		if (mIntegrationVals[j] < gPrecision) {
			mIntegrationVals[j] = 0.0;
		}
	}
	return true;
}

SynapseWrapper* CIntegrationSiteMaxInt1::GetSynapses()
{
	if (!pSynapseWrapper) 
		pSynapseWrapper = new SynapseWrapperMaxInt1(pInputVals,&mWeights);
	return pSynapseWrapper;
}

//////////////////////////////////////////////////////////////////////

CIntegrationSiteCompInt1::CIntegrationSiteCompInt1(size_t* s,double* params) : CIntegrationSiteImpl(s[0],s[1]),yTemp(s[1]),
			mMaxVals1(s[0]),mMaxVals2(s[0]),mMaxIndex(s[0])
{
	mAlphaStep = params[0];
	mAlphaMax = params[1];
	mCompleteIntegration = params[2];
	mCurrentAlpha = 0.0;
}

CIntegrationSiteCompInt1::~CIntegrationSiteCompInt1()
{
	
}

void CIntegrationSiteCompInt1::Reset()
{
	mCurrentAlpha = 0.0;
	CIntegrationSiteImpl::Reset();
}

bool CIntegrationSiteCompInt1::Integrate(size_t nodes,HBlockOutput& y)
{
	bool conv = true;
	const size_t inputs = mWeights.NumInputs();
	const double xMax = pInputVals->max();
	const double yMax = y.max(nodes);
	mIntegrationVals = 0.0;
	mMaxVals1 = 0.0;
	mMaxVals2 = 0.0;
	mMaxIndex = 0;
	if (xMax < gPrecision) {//no input - conv is true
		conv = true;
	}
	else if (mCurrentAlpha < gPrecision) {//no inhibition because alpha == 0.0
		for(size_t i0=0;i0<inputs;++i0) {
			double inputval = (*pInputVals)[i0];
			if (inputval < gPrecision)
				continue;
			mMaxVals1[i0] = inputval;
			mMaxVals2[i0] = inputval;
			for (size_t j0=0;j0<nodes;++j0) {
				mIntegrationVals[j0] += mWeights(i0,j0)*inputval;
			}
		}
		for(size_t j0=0;j0<nodes;++j0) {
			if (mIntegrationVals[j0] < gPrecision) {
				mIntegrationVals[j0] = 0.0;
			}
		}
		mCurrentAlpha = mAlphaStep;
		if (mCurrentAlpha < gPrecision) //if alphaStep is 0, there will never be inhibition, so conv = true
			conv = true;
		else
			conv = false; //competitive phase has started, so no convergence yet
	}
	else if (yMax > gPrecision) {//at least for one input competition is in full swing
		double yAlpha = mCurrentAlpha/yMax;
		for(size_t j0=0;j0<nodes;++j0) {
			yTemp[j0] = yAlpha*y[j0]/mWeights.MaxWForNodeSpecial(j0);
		}
		for(size_t i1=0;i1<inputs;++i1) {
			double inputval = (*pInputVals)[i1];
			if (inputval < gPrecision)
				continue;
			for(size_t j1=0;j1<nodes;++j1) {
				double temp = mWeights(i1,j1)*yTemp[j1];
				if (temp > mMaxVals1[i1]) {
					mMaxVals2[i1] = mMaxVals1[i1];
					mMaxVals1[i1] = temp;
					mMaxIndex[i1] = j1;
				}
				else if (temp > mMaxVals2[i1]) {
					mMaxVals2[i1] = temp;
				}
			}
			if (mMaxVals1[i1] < gPrecision) {//this prevents re-entry of a previously suppressed input
				continue;
			}
			else if (mMaxVals2[i1] >= 1.0) {//all synapses for this input become suppressed in this round
				mMaxVals1[i1] = 0.0;
				mMaxVals2[i1] = 0.0;
				continue;
			}
			else if (mMaxVals1[i1] >= 1.0) {//all but one synapse is suppressed (this one wins the competition)
				mMaxVals1[i1] = 0.0;
				if (mMaxVals2[i1])
					conv = false;//input on synapse has not yet returned to original input value 
				mMaxVals2[i1] = inputval*(1.0 - mMaxVals2[i1]);
				size_t maxindex = mMaxIndex[i1];
				mIntegrationVals[maxindex] += mWeights(i1,maxindex)*mMaxVals2[i1];
			}
			else if (mMaxVals2[i1] < gPrecision) {//only one synapse is receiving a signal from this input, no competition for it
				mMaxVals2[i1] = inputval;
				mMaxVals1[i1] = 0.0;
				size_t maxindex = mMaxIndex[i1];
				mIntegrationVals[maxindex] += mWeights(i1,maxindex)*mMaxVals2[i1];
			}
			else {//the competition for this input is still going on, multiple nodes are receiving from it
				mMaxVals1[i1] = inputval*(1.0 - mMaxVals1[i1]);
				mMaxVals2[i1] = inputval*(1.0 - mMaxVals2[i1]);
				conv = false;
				size_t maxindex = mMaxIndex[i1];
				for(size_t j2=0;j2<nodes;++j2) {
					if (maxindex == j2)
						mIntegrationVals[j2] += mWeights(i1,j2)*mMaxVals2[i1];
					else
						mIntegrationVals[j2] += mWeights(i1,j2)*mMaxVals1[i1];
				}
			}		
		}
		for(size_t j3=0;j3<nodes;++j3) {
			if (mIntegrationVals[j3] < gPrecision)
				mIntegrationVals[j3] = 0.0;
		}
		if (mCompleteIntegration != 0.0)//run the integration until alphaMax is reached
			conv = false;
		if (mAlphaMax - mCurrentAlpha < gPrecision)
			conv = true;
		mCurrentAlpha = (mCurrentAlpha + mAlphaStep + gPrecision)>mAlphaMax?mAlphaMax:(mCurrentAlpha+mAlphaStep);
	}
	return conv;
}

void CIntegrationSiteCompInt1::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mAlphaStep = v;
		break;
	case 1:
		mAlphaMax = v;
		break;
	case 2:
		mCompleteIntegration = v;
		break;
	}
}

double CIntegrationSiteCompInt1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mAlphaStep;
		break;
	case 1:
		v = mAlphaMax;
		break;
	case 2: 
		v = mCompleteIntegration;
		break;
	}
	return v;
}

SynapseWrapper* CIntegrationSiteCompInt1::GetSynapses()
{
	if (!pSynapseWrapper) {
		pSynapseWrapper = new SynapseWrapperCompInt1(mWeights.NumNodes(),&mMaxVals1,&mMaxVals2,&mMaxIndex);
	}
	return pSynapseWrapper;
}

////////////////////////////////////////////////////////////////////////////
//Integration sites that learn
////////////////////////////////////////////////////////////////////////////

CIntegrationSiteDisj1::CIntegrationSiteDisj1(size_t* s,double* params) 
	: CIntegrationSiteMaxInt1(s,0),mTraceOutputs(s[1])
{
	mLearningRate = params[0];
	mTrace = params[1];
	mNTrace = 1 - params[1];
}

CIntegrationSiteDisj1::~CIntegrationSiteDisj1()
{
	
}

bool CIntegrationSiteDisj1::Learn(size_t nodes,HBlockOutput& y)
{
	for(size_t j=0;j<nodes;++j) //for mTrace = 0, this uses the current y values
		mTraceOutputs[j] = mNTrace*y[j] + mTrace*mTraceOutputs[j];

	const size_t inputs = mWeights.NumInputs();
	double sumy = 0.0;
	for(size_t s1=0;s1<nodes;++s1)
		sumy+=mTraceOutputs[s1];

	if (sumy > gPrecision) {
		const double meany = sumy/nodes;
		const double gammay = mLearningRate/sumy;
		for(size_t j=0;j<nodes;++j) {
			size_t maxInput = mMaxIndex[j];
			if (maxInput == std::numeric_limits<size_t>::max())
				continue;
			if (mTraceOutputs[j]>meany) {
				double yTemp = (mTraceOutputs[j]-meany)*gammay;
				for(size_t i=0;i<inputs;++i) {
					double temp = (*pInputVals)[i]*yTemp;
					if (maxInput == i)
						mWeights.Add4(temp,i,j);
					else if (mWeights(i,j) > temp + gPrecision)
						mWeights.Add4(-temp,i,j);
					else
						mWeights.Set4(0.0,i,j);//make sure weights don't get negative
				}
			}
		}
		(*pNorm)(mWeights);
	}
	return false;
}

void CIntegrationSiteDisj1::Initialise()
{
	mTraceOutputs = 0.0;
	CIntegrationSiteImpl::Initialise();
}

void CIntegrationSiteDisj1::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mLearningRate = val;
		break;
	case 1:
		mTrace = val;
		mNTrace = 1 - val;
		break;
	}
}

double CIntegrationSiteDisj1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mLearningRate;
		break;
	case 1:
		v = mTrace;
		break;
	}
	return v;
}

//////////////////////////////////////////////////////////////////////////////

CIntegrationSiteDisj2::CIntegrationSiteDisj2(size_t* s,double* params) : CIntegrationSiteMaxInt1(s,params),mPrevOutputs(s[1])
{
	mLearningRate = params[0];
}

CIntegrationSiteDisj2::~CIntegrationSiteDisj2()
{
	
}

bool CIntegrationSiteDisj2::Learn(size_t nodes,HBlockOutput& y)
{
	const size_t inputs = mWeights.NumInputs();
	double sumy = 0.0;
	for(size_t s1=0;s1<nodes;++s1)
		sumy+=mPrevOutputs[s1];

	if (sumy > gPrecision) {
		const double meany = sumy/nodes;
		const double gammay = mLearningRate/sumy;
		for(size_t j=0;j<nodes;++j) {
			size_t maxInput = mMaxIndex[j];
			if (maxInput == std::numeric_limits<size_t>::max())
				continue;
			if (mPrevOutputs[j]>meany) {
				double yTemp = (mPrevOutputs[j]-meany)*gammay;
				for(size_t i=0;i<inputs;++i) {
					double temp = (*pInputVals)[i]*yTemp;
					if (maxInput == i)
						mWeights.Add4(temp,i,j);
					else if (mWeights(i,j) > temp + gPrecision)
						mWeights.Add4(-temp,i,j);
					else
						mWeights.Set4(0.0,i,j);//make sure weights don't get negative
				}
			}
		}
		(*pNorm)(mWeights);
	}

	for(size_t j1=0;j1<nodes;++j1)
		mPrevOutputs[j1] = y[j1];
	return false;
}

void CIntegrationSiteDisj2::Initialise()
{
	mPrevOutputs = 0.0;
	CIntegrationSiteImpl::Initialise();
}

void CIntegrationSiteDisj2::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mLearningRate = val;
		break;
	}
}

double CIntegrationSiteDisj2::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mLearningRate;
		break;
	}
	return v;
}

//////////////////////////////////////////////////////////////////////////////

CIntegrationSiteConj1::CIntegrationSiteConj1(size_t* s,double* params) 
		: CIntegrationSiteCompInt1(s,params),xTemp(s[0])
{
	mLearningRate = params[3];
	mNegLearningRate = params[4];
}

CIntegrationSiteConj1::~CIntegrationSiteConj1()
{

}

bool CIntegrationSiteConj1::Learn(size_t nodes,HBlockOutput& y)
{
	bool lastLearned = false;//for use in constructive blocks
	const size_t inputs = mWeights.NumInputs();
	const double sumx = pInputVals->sum();
	const double sumy = y.sum(nodes);
	if (sumx > gPrecision && sumy > gPrecision) {
		const double meanx = sumx/inputs;
		const double meany = sumy/nodes;
		const double lrxy = mLearningRate/sumx/sumy;
		for(size_t i0=0;i0<inputs;++i0) {
			xTemp[i0] = (*pInputVals)[i0] - meanx;
		}
		for(size_t j1=0;j1<nodes;++j1) {
			double yPos = (y[j1] - meany)*lrxy;
			double yNeg = (y[j1] - meany)*mNegLearningRate;
			if (yPos > 0.0) {
				for(size_t i1=0;i1<inputs;++i1) {
					if (mWeights(i1,j1) <= 0.0 && mMaxVals2[i1]) {
						double wDelta = (mMaxVals1[i1] - (*pInputVals)[i1])*yNeg;//it can never be mMaxVals2
						if (wDelta) {
							mWeights.Add2(wDelta,i1,j1);
						}
					}
					double wij = mWeights(i1,j1);
					if (wij >= 0) {
						double wDelta = xTemp[i1]*yPos;
						if (wij > -wDelta + gPrecision)
							mWeights.Add2(wDelta,i1,j1);
						else
							mWeights.Set2(0.0,i1,j1);
					}
				}
				if (j1 == nodes - 1) {//last node has learned
					lastLearned = true;
				}
			}
			else if (yNeg) {
				for(size_t i2=0;i2<inputs;++i2) {
					double wij = mWeights(i2,j1);
					if (wij <= 0.0 && mMaxVals2[i2]) {
						double wDelta = (mMaxVals1[i2] - (*pInputVals)[i2])*yNeg;//it can never be mMaxVals2
						if (wDelta) {
							if (wij < -wDelta - gPrecision) {
								mWeights.Add2(wDelta,i2,j1);
							}
							else {
								mWeights.Set2(0.0,i2,j1);
							}
						}
					}
				}
			}
		}
		(*pNorm)(mWeights);
	}	
	return lastLearned;
}

void CIntegrationSiteConj1::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:case 1:case 2:
		CIntegrationSiteCompInt1::SetParam(p,v);
		break;
	case 3:
		mLearningRate = v;
		break;
	case 4:
		mNegLearningRate = v;
		break;
	}
}

double CIntegrationSiteConj1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:case 1:case 2:
		v = CIntegrationSiteCompInt1::GetParam(p);
		break;
	case 3:
		v = mLearningRate;
		break;
	case 4:
		v = mNegLearningRate;
		break;
	}
	return v;
}

//////////////////////////////////////////////////////////////////////////////

CIntegrationSiteConj2::CIntegrationSiteConj2(size_t* s,double* params) 
		: CIntegrationSiteCompInt1(s,params),xTemp(s[0])
{
	mLearningRate = params[3];
	mNegLearningRate = params[4];
}

CIntegrationSiteConj2::~CIntegrationSiteConj2()
{

}

bool CIntegrationSiteConj2::Learn(size_t nodes,HBlockOutput& y)
{
	bool lastLearned = false;
	const size_t inputs = mWeights.NumInputs();
	const double sumx = pInputVals->sum();
	const double sumy = y.sum(nodes);
	if (sumx > gPrecision && sumy > gPrecision) {
		const double meanx = sumx/inputs;
		const double meany = sumy/nodes;
		const double lrx = mLearningRate/sumx;
		const double nlry = mNegLearningRate/sumy;
		for(size_t i0=0;i0<inputs;++i0) {
			xTemp[i0] = (*pInputVals)[i0] - meanx;
		}
		for(size_t j1=0;j1<nodes;++j1) {
			double yPos = (y[j1] - meany)*lrx;
			double yNeg = (y[j1] - meany)*nlry;
			if (yPos > 0.0) {
				for(size_t i1=0;i1<inputs;++i1) {
					if (mWeights(i1,j1) <= 0.0 && mMaxVals2[i1]) {
						double wDelta = mMaxVals1[i1] - (*pInputVals)[i1]/2.0;
						wDelta = (wDelta<0.0)?(wDelta*yNeg):0.0;
						if (wDelta) {
							mWeights.Add2(wDelta,i1,j1);
						}
					}
					double wij = mWeights(i1,j1);
					if (wij >= 0) {
						double wDelta = xTemp[i1]*yPos;
						if (wij > -wDelta + gPrecision)
							mWeights.Add2(wDelta,i1,j1);
						else
							mWeights.Set2(0.0,i1,j1);
					}
				}
				if (j1 == nodes - 1) {//last node has learned
					lastLearned = true;
				}
			}
			else if (yNeg) {
				for(size_t i2=0;i2<inputs;++i2) {
					double wij = mWeights(i2,j1);
					if (wij <= 0.0 && mMaxVals2[i2]) {
						double wDelta = mMaxVals1[i2] - (*pInputVals)[i2]/2.0;
						wDelta = (wDelta<0.0)?wDelta*yNeg:0.0;
						if (wDelta) {
							if (wij < -wDelta - gPrecision) {
								mWeights.Add2(wDelta,i2,j1);
							}
							else {
								mWeights.Set2(0.0,i2,j1);
							}
						}
					}
				}
			}
		}
		(*pNorm)(mWeights);
	}	
	return lastLearned;
}

void CIntegrationSiteConj2::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:case 1:case 2:
		CIntegrationSiteCompInt1::SetParam(p,v);
		break;
	case 3:
		mLearningRate = v;
		break;
	case 4:
		mNegLearningRate = v;
		break;
	}
}

double CIntegrationSiteConj2::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:case 1:case 2:
		v = CIntegrationSiteCompInt1::GetParam(p);
		break;
	case 3:
		v = mLearningRate;
		break;
	case 4:
		v = mNegLearningRate;
		break;
	}
	return v;
}

//////////////////////////////////////////////////////////////////////////////

CIntegrationSiteConj3::CIntegrationSiteConj3(size_t* s,double* params) 
		: CIntegrationSiteCompInt1(s,params),xTemp(s[0])
{
	mLearningRate = params[3];
}

CIntegrationSiteConj3::~CIntegrationSiteConj3()
{

}

bool CIntegrationSiteConj3::Learn(size_t nodes,HBlockOutput& y)
{
	bool lastLearned = false;
	const size_t inputs = mWeights.NumInputs();
	const double sumx = pInputVals->sum();
	const double sumy = y.sum(nodes);
	if (sumx > gPrecision && sumy > gPrecision) {
		const double meanx = sumx/inputs;
		const double meany = sumy/nodes;
		const double lrx = mLearningRate/sumx;
		for(size_t i0=0;i0<inputs;++i0) {
			xTemp[i0] = (*pInputVals)[i0] - meanx;
		}
		for(size_t j1=0;j1<nodes;++j1) {
			double yPos = (y[j1] - meany)*lrx;
			if (yPos > 0.0) {
				for(size_t i1=0;i1<inputs;++i1) {
					double wij = mWeights(i1,j1);
					if (wij > 0) {
						double wDelta = xTemp[i1]*yPos;
						if (wij > -wDelta + gPrecision)
							mWeights.Add2(wDelta,i1,j1);
						else
							mWeights.Set2(0.0,i1,j1);
					}
				}
				if (j1 == nodes - 1) {//last node has learned
					lastLearned = true;
				}
			}
		}
		(*pNorm)(mWeights);
	}	
	return lastLearned;
}

void CIntegrationSiteConj3::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:case 1:case 2:
		CIntegrationSiteCompInt1::SetParam(p,v);
		break;
	case 3:
		mLearningRate = v;
		break;
	}
}

double CIntegrationSiteConj3::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:case 1:case 2:
		v = CIntegrationSiteCompInt1::GetParam(p);
		break;
	case 3:
		v = mLearningRate;
		break;
	}
	return v;
}

} //end namespace CORINET


