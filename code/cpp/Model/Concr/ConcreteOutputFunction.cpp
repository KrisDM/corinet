/*********************************************************************************************
 * Name      :  ConcreteOutputFun.cpp
 *
 * Purpose   :  Concrete types of outputfunctions. 
 *				An outputfunction combines the integration results from separate integration sites 
 *				into an overall node activity value, usually including a small amount of noise.
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

#include <Model/Misc/Nodes.h>
#include <Common/Attenuation.h>
#include <Common/NoiseFunction.h>
#include "ConcreteOutputFunction.h"

namespace CORINET {

FOutputFunctionAddSites::FOutputFunctionAddSites(size_t*,double*)
{
	pAttenuation = 0;
	pNoise = 0;
}

FOutputFunctionAddSites::~FOutputFunctionAddSites()
{

}

void FOutputFunctionAddSites::operator()(const std::vector<SubArrayIteratorConst*>& intvals,HBlockOutput& y)
{
	const SubArrayIteratorConst& basal = *(intvals[0]);
	const size_t s = basal.size();
	for(size_t j=0;j<s;++j) {
		y[j] = basal[j];
	}
	for(size_t k=1,ks=intvals.size();k<ks;++k) {
		const SubArrayIteratorConst& site = *(intvals[k]);
		for(size_t j1=0;j1<s;++j1) {
			y[j1] += site[j1];
		}
	}
	if (pAttenuation) (*pAttenuation)(y);
	if (pNoise) (*pNoise)(y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

FOutputFunctionMaxSites::FOutputFunctionMaxSites(size_t*,double*)
{
	pAttenuation = 0;
	pNoise = 0;
}

FOutputFunctionMaxSites::~FOutputFunctionMaxSites()
{

}

void FOutputFunctionMaxSites::operator()(const std::vector<SubArrayIteratorConst*>& intvals,HBlockOutput& y)
{
	const SubArrayIteratorConst& basal = *(intvals[0]);
	const size_t s = basal.size();
	for(size_t j=0;j<s;++j) {
		y[j] = basal[j];
	}
	for(size_t k=1,ks=intvals.size();k<ks;++k) {
		const SubArrayIteratorConst& site = *(intvals[k]);
		for(size_t j1=0;j1<s;++j1) {
			if (site[j1] > y[j1])
				y[j1] = site[j1];
		}
	}
	if (pAttenuation) (*pAttenuation)(y);
	if (pNoise) (*pNoise)(y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

FOutputFunctionModulate1::FOutputFunctionModulate1(size_t*,double* params) : mA(params[0])
{
	pAttenuation = 0;
	pNoise = 0;
}

FOutputFunctionModulate1::~FOutputFunctionModulate1()
{

}

void FOutputFunctionModulate1::operator()(const std::vector<SubArrayIteratorConst*>& intvals,HBlockOutput& y)
{
	const SubArrayIteratorConst& basal = *(intvals[0]);
	const SubArrayIteratorConst& apical = *(intvals[1]);
	const size_t s = basal.size();
	for(size_t j=0;j<s;++j) {
		y[j] = (1+mA*apical[j])*basal[j];
	}
	if (pAttenuation) (*pAttenuation)(y);
	if (pNoise) (*pNoise)(y);
}

void FOutputFunctionModulate1::SetParam(size_t p,double v)
{
	switch (p) {
	case 0:
		mA = v;
		break;
	}
}

double FOutputFunctionModulate1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0: 
		v = mA;
		break;
	}
	return v;
}

} //end namespace CORINET
