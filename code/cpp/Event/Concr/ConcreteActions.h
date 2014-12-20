/*********************************************************************************************
 * Name      :  ConcreteActions.h
 *
 * Purpose   :  Concrete actions that can be executed in event handlers.
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

#ifndef CORINET_ACTIONCONCR
#define CORINET_ACTIONCONCR

#include <Util/ParamInterface.h>
#include <Util/Iterator.h>
#include <Model/SynapseWrapper.h>
#include <Event/Impl/ActionImpl.h>
#include <Model/Network.h>
#include <Task/Task.h>
#include <Engine/ExecutionElement.h>

namespace CORINET {

class CRecordNetState : public CRecordImpl<SubArrayIteratorConst> {
public:
	CRecordNetState();
	virtual ~CRecordNetState();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CRecordNetInput : public CRecordImpl<SubArrayIteratorConst> {
public:
	CRecordNetInput();
	virtual ~CRecordNetInput();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CRecordNetOutput : public CRecordImpl<MultipleSubArrayIteratorConst> {
public:
	CRecordNetOutput();
	virtual ~CRecordNetOutput();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CRecordNetIO : public CRecordImpl<MultipleSubArrayIteratorConst> {
public:
	CRecordNetIO();
	virtual ~CRecordNetIO();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CRecordBlockOutput : public CRecordImpl<SubArrayIteratorConst> {
public:
	CRecordBlockOutput();
	virtual ~CRecordBlockOutput();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CRecordWeights : public CRecordImpl<MatrixIteratorConst> {
public:
	CRecordWeights();
	virtual ~CRecordWeights();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CRecordSynapses : public CRecordImpl<SynapseWrapper> {
public:
	CRecordSynapses();
	virtual ~CRecordSynapses();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CRecordIntegrationValues : public CRecordImpl<SubArrayIteratorConst> {
public:
	CRecordIntegrationValues();
	virtual ~CRecordIntegrationValues();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CRecordIntegrationInput : public CRecordImpl<IndirectIteratorConst> {
public:
	CRecordIntegrationInput();
	virtual ~CRecordIntegrationInput();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CRecordTaskPatterns : public CRecordImpl<MatrixIteratorConst> {
public:
	CRecordTaskPatterns();
	virtual ~CRecordTaskPatterns();
	void Handle(CExTimeInfo*);
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

/////////////////////////////////////////////////////////////////////////////////////////////

class CModifyNetState : public CModifyValues<SubArrayIterator> {
public:
	CModifyNetState();
	virtual ~CModifyNetState();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CModifyBlockOutput : public CModifyValues<SubArrayIterator> {
public:
	CModifyBlockOutput();
	virtual ~CModifyBlockOutput();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CModifyIntegrationValues : public CModifyValues<SubArrayIterator> {
public:
	CModifyIntegrationValues();
	virtual ~CModifyIntegrationValues();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CModifyIntegrationInput : public CModifyValues<IndirectIterator> {
public:
	CModifyIntegrationInput();
	virtual ~CModifyIntegrationInput();
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

class CModifyWeights : public CModifyValues<MatrixIterator> {
public:
	CModifyWeights();
	virtual ~CModifyWeights();
	void Handle(CExTimeInfo*);
	void AddTarget(void*,void*,std::string,std::string,size_t =std::numeric_limits<size_t>::max());
};

///////////////////////////////////////////////////////////////////////////////////////////////

class CModifyParamTask : public CModifyParam<CTask> {
public:
	CModifyParamTask();
	virtual ~CModifyParamTask();
	void Handle(CExTimeInfo*);
};

class CModifyParamNetwork : public CModifyParam<CNetwork> {
public:
	CModifyParamNetwork();
	virtual ~CModifyParamNetwork();
	void Handle(CExTimeInfo*);
};

class CModifyParamExecution : public CModifyParam<CExecutionElement> {
public:
	CModifyParamExecution();
	virtual ~CModifyParamExecution();
	void Handle(CExTimeInfo*);
};

} //end namespace CORINET	

#endif //CORINET_ACTIONCONCR
