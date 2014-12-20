/*********************************************************************************************
 * Name      :  ConcreteLoops.h
 *
 * Purpose   :  Concrete types of loops.
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

#ifndef CORINET_LOOPCONCR
#define CORINET_LOOPCONCR

#include <Engine/Impl/LoopImpl.h>
#include <vector>

namespace CORINET {

class CLoopsV1 : public CLoopsImpl {
	size_t mTotalConfigs;
	std::vector<CLoop*> mLoops;
public:
	CLoopsV1();
	virtual ~CLoopsV1();
	void Begin();
	void operator++();
	size_t Configs() const;

	void AddLoop(CLoop*);	
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CLoopV1 : public CLoopImpl {
	size_t mCurrent;
	size_t mConfigs;
	std::vector<CLoopElement*> mLoopElements;
public:
	CLoopV1();
	virtual ~CLoopV1();
	void Begin();
	size_t operator++();
	size_t Configs() const;

	void AddLoopElement(CLoopElement*);
	void SetSize(size_t);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CLoopVarV1 : public CLoopElementImpl {
	size_t mParamNum;
	const std::valarray<double>* pParamVals;
	std::vector<CParamInterface*> mTargets;
public:
	CLoopVarV1();
	virtual ~CLoopVarV1();
	void Update(size_t);
	size_t Size() const;

	void AddValues(const std::valarray<double>*);
	void AddTarget(void*,size_t);
};

class CLoopWeightsV1 : public CLoopElementImpl {
	std::vector<const std::valarray<double>*> mWeightVals;
	std::vector<FInitialisation*> mTargets;
public:
	CLoopWeightsV1();
	virtual ~CLoopWeightsV1();
	void Update(size_t);
	size_t Size() const;

	void AddValues(const std::valarray<double>*);
	void AddTarget(void*,size_t);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //end namespace CORINET

#endif //CORINET_LOOPCONCR

