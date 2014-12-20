/*********************************************************************************************
 * Name      :  ConcreteInitialisation.cpp
 *
 * Purpose   :  Concrete initialisation functions.
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

#include "ConcreteInitialisation.h"
#include <Model/Misc/Weights.h>
#include <Common/RandGen.h>

namespace CORINET {

FInitialisationExplicit::FInitialisationExplicit(size_t*,double*)
{

}

FInitialisationExplicit::~FInitialisationExplicit()
{

}

void FInitialisationExplicit::operator()(HWeights& w)
{
	const size_t inputs = w.NumInputs();
	const size_t nodes = w.NumNodes();
	size_t counter = 0;
	for(size_t j=0;j<nodes;++j) {
		for(size_t i=0;i<inputs;++i) {
			w.Set1((*pValues)[counter++],i,j);
			if (pRandGen)
				w.Add1((*pRandGen)(),i,j);
			if (w(i,j) < gPrecision)
				w.Set1(0.0,i,j);
		}
	}
	w.InvalMaxWForInputs();
	w.InvalMaxWForNodes();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

FInitialisationValue::FInitialisationValue(size_t*,double* params) : mValue(params[0])
{
	
}

FInitialisationValue::~FInitialisationValue()
{

}

void FInitialisationValue::operator()(HWeights& w)
{
	const size_t inputs = w.NumInputs();
	const size_t nodes = w.NumNodes();
	for(size_t i=0;i<inputs;++i) {
		for(size_t j=0;j<nodes;++j) {
			w.Set1(mValue,i,j);
			if (pRandGen)
				w.Add1((*pRandGen)(),i,j);
			if (w(i,j) < gPrecision)
				w.Set1(0.0,i,j);
		}
	}
	w.InvalMaxWForInputs();
	w.InvalMaxWForNodes();
}

void FInitialisationValue::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mValue = val;
		break;
	}
}

double FInitialisationValue::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mValue;
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

FInitialisationDiagonal::FInitialisationDiagonal(size_t*,double* params) : mValue(params[0])
{
	
}

FInitialisationDiagonal::~FInitialisationDiagonal()
{

}

void FInitialisationDiagonal::operator()(HWeights& w)
{
	const size_t inputs = w.NumInputs();
	const size_t nodes = w.NumNodes();
	for(size_t i=0;i<inputs;++i) {
		for(size_t j=0;j<nodes;++j) {
			w.Set1(0.0,i,j);
		}
	}
	const size_t minindex = inputs>nodes?nodes:inputs;
	for(size_t i2=0;i2<minindex;++i2) {
		w.Set1(mValue,i2,i2);
	}
	w.InvalMaxWForInputs();
	w.InvalMaxWForNodes();
}

void FInitialisationDiagonal::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mValue = val;
		break;
	}
}

double FInitialisationDiagonal::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mValue;
		break;
	}
	return v;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

FInitialisationRandom::FInitialisationRandom(size_t*,double*)
{

}

FInitialisationRandom::~FInitialisationRandom()
{

}

void FInitialisationRandom::operator()(HWeights& w)
{
	const size_t inputs = w.NumInputs();
	const size_t nodes = w.NumNodes();
	for(size_t i=0;i<inputs;++i) {
		for(size_t j=0;j<nodes;++j) {
			w.Set1((*pRandGen)(),i,j);
			if (w(i,j) < gPrecision)
				w.Set1(gPrecision,i,j);
		}
	}
	w.InvalMaxWForInputs();
	w.InvalMaxWForNodes();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

FInitialisationInputSize::FInitialisationInputSize(size_t* s,double* params)
{

}

FInitialisationInputSize::~FInitialisationInputSize()
{
	
}

void FInitialisationInputSize::operator()(HWeights& w)
{
	const size_t inputs = w.NumInputs();
	const size_t nodes = w.NumNodes();
	for(size_t i=0;i<inputs;++i) {
		for(size_t j=0;j<nodes;++j) {
			w.Set1(1.0/static_cast<double>(inputs),i,j);
			if (pRandGen)
				w.Add1((*pRandGen)(),i,j);
			if (w(i,j) < gPrecision)
				w.Set1(0.0,i,j);
		}
	}
	w.InvalMaxWForInputs();
	w.InvalMaxWForNodes();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

FInitialisationNodeSize::FInitialisationNodeSize(size_t* s,double* params)
{

}

FInitialisationNodeSize::~FInitialisationNodeSize()
{

}

void FInitialisationNodeSize::operator()(HWeights& w)
{
	const size_t inputs = w.NumInputs();
	const size_t nodes = w.NumNodes();
	for(size_t i=0;i<inputs;++i) {
		for(size_t j=0;j<nodes;++j) {
			w.Set1(1.0/static_cast<double>(nodes),i,j);
			if (pRandGen)
				w.Add1((*pRandGen)(),i,j);
			if (w(i,j) < gPrecision)
				w.Set1(0.0,i,j);
		}
	}
	w.InvalMaxWForInputs();
	w.InvalMaxWForNodes();
}

} //end namespace CORINET
