/*********************************************************************************************
 * Name      :  ActionImpl.h
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


#ifndef CORINET_ACTIONIMPL
#define CORINET_ACTIONIMPL

#include <Event/Action.h>
#include <valarray>
#include <vector>
#include <map>
#include <limits>
#include <string>

namespace CORINET {
	class CParamInterface;
	class CReport;
	class FOperation;

class CActionImpl : public CAction {//interface for initialising the actions properly
public:
	virtual ~CActionImpl() {}
	virtual void SetReporter(CReport*) {}
	virtual void SetPrecision(size_t) {}
	virtual void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max()) {}
	virtual void AddOperation(FOperation*) {}
	virtual void SetIndices(const std::valarray<size_t>*,const std::valarray<size_t>* =0) {}
};


template<typename IteratorConstType>
class CRecordImpl : public CActionImpl {
protected:
	typedef std::pair<IteratorConstType*,void*> LTargetAndParent;
	typedef std::vector<LTargetAndParent> LTargets;
	LTargets mTargets;
	CReport* pReporter;
	size_t mPrecision;
public:
	CRecordImpl();
	virtual ~CRecordImpl();
	void Initialise(CExTimeInfo*);
	void Handle(CExTimeInfo*);
	void Finalise(CExTimeInfo*);

	void SetReporter(CReport*);
	void SetPrecision(size_t);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CModifyImpl : public CActionImpl {
protected:
	std::vector<FOperation*> mOperations;
public:
	virtual ~CModifyImpl() {}
	void AddOperation(FOperation* po) {
		mOperations.push_back(po);
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename IteratorType>
class CModifyValues : public CModifyImpl {
protected:
	typedef std::pair<IteratorType*,void*> LTargetAndParent;
	typedef std::vector<LTargetAndParent> LTargets;
	LTargets mTargets;
	const std::valarray<size_t>* pNodeIndices;
	const std::valarray<size_t>* pInputIndices;//only used in modifyWeights
public:
	CModifyValues();
	virtual ~CModifyValues();
	void Initialise(CExTimeInfo*);
	void Handle(CExTimeInfo*);
	void Finalise(CExTimeInfo*);

	void SetIndices(const std::valarray<size_t>*,const std::valarray<size_t>* =0);
};

template<typename ParentType>
class CModifyParam : public CModifyImpl {
protected:
	typedef std::pair<CParamInterface*,size_t> LParamInfo;
	typedef std::pair<LParamInfo,ParentType*> LTargetAndParent;
	typedef std::vector<LTargetAndParent> LTargets;
	typedef std::map<CParamInterface*,double> LInitialVals;
	LTargets mTargets;
	LInitialVals mInitialVals;
public:
	CModifyParam();
	virtual ~CModifyParam();
	void Initialise(CExTimeInfo*);
	void Finalise(CExTimeInfo*);
	void AddTarget(void*,void*,std::string,std::string,size_t);
};

} //end namespace CORINET	

#endif //CORINET_ACTIONIMPL

