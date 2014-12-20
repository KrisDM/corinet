/*********************************************************************************************
 * Name      :  ActionImpl.cpp
 *
 * Purpose   :  Common functionality of actions. These are still not concrete types,
 *				but general base classes.
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

#include "ActionImpl.h"
#include <Event/Operation.h>
#include <Event/Report.h>
#include <Engine/ExTimeInfo.h>
#include <Util/Iterator.h>
#include <Util/ParamInterface.h>

namespace CORINET {
	class CNetwork;
	class CTask;

template<typename IteratorConstType>
CRecordImpl<IteratorConstType>::CRecordImpl() : mTargets(),mPrecision(4)
{

}
	
template<typename IteratorConstType>
CRecordImpl<IteratorConstType>::~CRecordImpl()
{

}

template<typename IteratorConstType>
void CRecordImpl<IteratorConstType>::Initialise(CExTimeInfo* eTI) 
{
	for(typename LTargets::iterator it=mTargets.begin(),ite=mTargets.end();it != ite;++it) {
		pReporter->Initialise(it->first,eTI);
	}
}

template<typename IteratorConstType>
void CRecordImpl<IteratorConstType>::Finalise(CExTimeInfo* eTI) 
{
	pReporter->Finalise(0,eTI);
}

template<typename IteratorConstType>
void CRecordImpl<IteratorConstType>::SetReporter(CReport* p) 
{
	pReporter = p;
}

template<typename IteratorConstType>
void CRecordImpl<IteratorConstType>::SetPrecision(size_t prec)
{
	mPrecision = prec;
}
	
template<typename IteratorConstType>
void CRecordImpl<IteratorConstType>::Handle(CExTimeInfo* eTI) 
{
	CNetwork* thisNet = eTI->GetNetwork();
	for(typename LTargets::iterator it=mTargets.begin(),ite=mTargets.end();it != ite;++it) {
		if (!thisNet || thisNet == it->second) {
			pReporter->Write(mPrecision,it->first,eTI);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename IteratorType>
CModifyValues<IteratorType>::CModifyValues() : mTargets()
{

}

template<typename IteratorType>
CModifyValues<IteratorType>::~CModifyValues()
{

}
	
template<typename IteratorType>
void CModifyValues<IteratorType>::Initialise(CExTimeInfo*)
{

}

template<typename IteratorType>
void CModifyValues<IteratorType>::Finalise(CExTimeInfo*)
{

}
	
template<typename IteratorType>
void CModifyValues<IteratorType>::SetIndices(const std::valarray<size_t>* pn,const std::valarray<size_t>* pi) 
{
	pNodeIndices = pn;
	pInputIndices = pi;
}

template<typename IteratorType>
void CModifyValues<IteratorType>::Handle(CExTimeInfo* eTI) 
{
	bool next = false;
	CNetwork* thisNet = eTI->GetNetwork();
	for(typename LTargets::iterator it=mTargets.begin(),ite=mTargets.end();it != ite;++it) {
		if (!thisNet || thisNet == it->second) {
			next = true;
			const std::valarray<size_t>* indices = pNodeIndices;
			if (!indices)
				indices = pInputIndices;
			for(size_t j=0,s=indices->size();j<s;++j) {
				double val = (*(it->first))[(*indices)[j]];
				for(size_t k=0,ks=mOperations.size();k<ks;++k) {
					val = (*(mOperations[k]))(val);
				}
				(*(it->first))[(*indices)[j]] = val;
			}
		}
	}
	if (next) {
		for(size_t k=0,ks=mOperations.size();k<ks;++k) {
			mOperations[k]->Next();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename ParentType>
CModifyParam<ParentType>::CModifyParam() : mTargets(),mInitialVals() 
{
	
}
	
template<typename ParentType>
CModifyParam<ParentType>::~CModifyParam()
{

}
	
template<typename ParentType>
void CModifyParam<ParentType>::Initialise(CExTimeInfo*)
{
	for(typename LTargets::iterator it=mTargets.begin(),ite=mTargets.end();it != ite;++it) {
		LParamInfo& paraminfo = it->first;
		mInitialVals[paraminfo.first] = paraminfo.first->GetParam(paraminfo.second);
	}
}
	
template<typename ParentType>
void CModifyParam<ParentType>::Finalise(CExTimeInfo*)
{
	for(typename LTargets::iterator it=mTargets.begin(),ite=mTargets.end();it != ite;++it) {
		LParamInfo& paraminfo = it->first;
		paraminfo.first->SetParam(paraminfo.second,mInitialVals[paraminfo.first]);
	}
}
	
template<typename ParentType>
void CModifyParam<ParentType>::AddTarget(void* parent,void* target,std::string,std::string,size_t param)
{
	typename LTargets::value_type vt(LParamInfo(static_cast<CParamInterface*>(target),param),static_cast<ParentType*>(parent));
	mTargets.push_back(vt);
	mInitialVals.insert(LInitialVals::value_type(static_cast<CParamInterface*>(target),0.0));
}
	
} //end namespace CORINET 
