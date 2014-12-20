/*********************************************************************************************
 * Name      :  ConcreteNormalisation.cpp
 *
 * Purpose   :  ConcreteNormalisation rules.
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

#include "ConcreteNormalisation.h"
#include <Model/Misc/Weights.h>

namespace CORINET {

FNormalisationNormNone::FNormalisationNormNone(size_t*,double*)
{

}

FNormalisationNormNone::~FNormalisationNormNone()
{

}
	
void FNormalisationNormNone::operator()(HWeights&)
{

}

////////////////////////////////////////////////////////////////////////////////////////////

FNormalisationNormNode::FNormalisationNormNode(size_t*,double* params)
{
	mPosNorm = params[0];
	mPosConstrain = params[1];
	mPosMax = params[2];
	mNegNorm = params[3];
	mNegConstrain = params[4];
	mNegMax = params[5];
}

FNormalisationNormNode::~FNormalisationNormNode()
{

}
	
void FNormalisationNormNode::operator()(HWeights& w)
{
	const size_t inputs = w.NumInputs();
	const size_t nodes = w.NumNodes();
	for(size_t j=0;j<nodes;++j) {
		double wSumP = 0.0;
		double wSumN = 0.0;
		for(size_t i=0;i<inputs;++i) {
			if (w(i,j) > 0.0) 
				wSumP+=w(i,j);
			else
				wSumN+=w(i,j);
		}
		wSumP = (wSumP>mPosConstrain)?(wSumP/mPosNorm):1;
		wSumN = (wSumN<mNegConstrain)?(wSumN/mNegNorm):1;
		for(size_t i2=0;i2<inputs;++i2) {
			if (w(i2,j) > 0.0) {
				w.Div1(wSumP,i2,j);
				if (w(i2,j) > mPosMax) 
					w.Set1(mPosMax,i2,j);
			}
			else if (w(i2,j) < 0.0) {
				w.Div1(wSumN,i2,j);
				if (w(i2,j) < mNegMax)
					w.Set1(mNegMax,i2,j);
			}
		}
	}
	w.InvalMaxWForInputs();
}

void FNormalisationNormNode::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mPosNorm = v;
		break;
	case 1:
		mPosConstrain = v;
		break;
	case 2:
		mPosMax = v;
		break;
	case 3:
		mNegNorm = v;
		break;
	case 4:
		mNegConstrain = v;
		break;
	case 5:
		mNegMax = v;
		break;
	}
}

double FNormalisationNormNode::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0: 
		v = mPosNorm;
		break;
	case 1:
		v = mPosConstrain;
		break;
	case 2:
		v = mPosMax;
		break;
	case 3:
		v = mNegNorm;
		break;
	case 4:
		v = mNegConstrain;
		break;
	case 5:
		v = mNegMax;
		break;
	}
	return v;
}

////////////////////////////////////////////////////////////////////////////////////////////

FNormalisationNormInput::FNormalisationNormInput(size_t*,double* params)
{
	mPosNorm = params[0];
	mPosConstrain = params[1];
	mPosMax = params[2];
	mNegNorm = params[3];
	mNegConstrain = params[4];
	mNegMax = params[5];
}

FNormalisationNormInput::~FNormalisationNormInput()
{

}
	
void FNormalisationNormInput::operator()(HWeights& w)
{
	const size_t inputs = w.NumInputs();
	const size_t nodes = w.NumNodes();
	for(size_t i=0;i<inputs;++i) {
		double wSumP = 0.0;
		double wSumN = 0.0;
		for(size_t j=0;j<nodes;++j) {
			if (w(i,j) > 0.0) 
				wSumP+=w(i,j);
			else
				wSumN+=w(i,j);
		}
		wSumP = (wSumP>mPosConstrain)?(wSumP/mPosNorm):1.0;
		wSumN = (wSumN<mNegConstrain)?(wSumN/mNegNorm):1.0;
		for(size_t j2=0;j2<nodes;++j2) {
			if (w(i,j2) > 0.0) {
				w.Div1(wSumP,i,j2);
				if (w(i,j2) > mPosMax) 
					w.Set1(mPosMax,i,j2);
			}
			else if (w(i,j2) < 0.0) {
				w.Div1(wSumN,i,j2);
				if (w(i,j2) < mNegMax)
					w.Set1(mNegMax,i,j2);
			}
		}
	}
	w.InvalMaxWForNodes();
}

void FNormalisationNormInput::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mPosNorm = v;
		break;
	case 1:
		mPosConstrain = v;
		break;
	case 2:
		mPosMax = v;
		break;
	case 3:
		mNegNorm = v;
		break;
	case 4:
		mNegConstrain = v;
		break;
	case 5:
		mNegMax = v;
		break;
	}
}

double FNormalisationNormInput::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0: 
		v = mPosNorm;
		break;
	case 1:
		v = mPosConstrain;
		break;
	case 2:
		v = mPosMax;
		break;
	case 3:
		v = mNegNorm;
		break;
	case 4:
		v = mNegConstrain;
		break;
	case 5:
		v = mNegMax;
		break;
	}
	return v;
}
////////////////////////////////////////////////////////////////////////////////////////////

} //end namespace CORINET
