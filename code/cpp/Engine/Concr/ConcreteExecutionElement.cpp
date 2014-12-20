/*********************************************************************************************
 * Name      :  ConcreteExecutionElement.cpp
 *
 * Purpose   :  Concrete types of execution elements.
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

#include "ConcreteExecutionElement.h"
#include <Model/Network.h>
#include <Task/Task.h>
#include <Event/Event.h>
#include <Engine/ExTimeInfo.h>
#include <Util/Iterator.h>
#include <limits>

namespace CORINET {

CExecutionSequenceV1::CExecutionSequenceV1() : mSequenceEntry(0),pRepeats(0),mExElements()
{

}

CExecutionSequenceV1::~CExecutionSequenceV1()
{

}

void CExecutionSequenceV1::operator()(CExTimeInfo* pet,std::vector<CNetwork*>& networks)
{
	const size_t currentRepeat = (*pRepeats)[mSequenceEntry%(pRepeats->size())];
	const size_t es = mExElements.size();
	for(size_t r1=0;r1<currentRepeat;++r1) {
		for(size_t e1=0;e1<es;++e1) {
			(*(mExElements[e1]))(pet,networks);
		}
	}
	++mSequenceEntry;
}

void CExecutionSequenceV1::AddExElement(CExecutionElement* pex)
{
	mExElements.push_back(pex);
}

void CExecutionSequenceV1::SetTimes(const std::valarray<size_t>* prep)
{
	pRepeats = prep;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

CExecutionPartV1::CExecutionPartV1(size_t* b,double* params) 
		: mPartEntry(0),pIterations(0),
		bRandom(static_cast<bool>(b[0])),bLearn(static_cast<bool>(b[1])),bLearnDuringReset(static_cast<bool>(b[2])),
		bGenerateOnly(static_cast<bool>(b[3])),mTimePerPattern(params[0]),mZeroTime(params[1]),mTasks(),mEvents()
{

}

CExecutionPartV1::~CExecutionPartV1()
{

}

void CExecutionPartV1::operator()(CExTimeInfo* pet,std::vector<CNetwork*>& networks)
{ 
	const size_t ts = mTasks.size();
	const size_t ns = networks.size();
	const size_t currentIterations = (*pIterations)[mPartEntry%(pIterations->size())];
	pet->SetPartEntry(mPartEntry++);
	pet->SetPart(this);
	pet->SetNetwork(0);
	pet->ClearTasks();
	for(size_t t1=0;t1<ts;++t1) {
		pet->AddTask(mTasks[t1]);
	}
	
	HandleEvents(BEGIN_PART,pet);
	for(pet->SetIteration(0);pet->GetIteration() < currentIterations;pet->IncrIteration()) {
		pet->SetIntegration(std::numeric_limits<size_t>::max());
		HandleEvents(BEGIN_ITERATION,pet);
		HandleEvents(BEFORE_GENERATE,pet);
		for(size_t t2=0;t2<ts;++t2) {
			mTasks[t2]->Generate(bRandom);
		}
		HandleEvents(AFTER_GENERATE,pet);
		if (bGenerateOnly) {//skip all integration and learning
			HandleEvents(END_ITERATION,pet);
			continue;
		}

		for(size_t n1=0;n1<ns;++n1) {
			//take a network
			CNetwork* thisnet = networks[n1];
			pet->SetNetwork(thisnet);
			HandleEvents(BEFORE_RESET,pet);
			//reset the network
			NextStep next = thisnet->Reset(mZeroTime);
			HandleEvents(AFTER_RESET,pet);
			pet->SetIntegration(std::numeric_limits<size_t>::max());
			while(next != NEXT_ENGINE) {
				//potentially perform the integrate and learn resets to flush a network of previous activity
				switch (next) {
				case NEXT_INTEGRATE:
					pet->IncrIntegration();
					HandleEvents(BEFORE_RESETINTEGRATE,pet);
					next = thisnet->Integrate();
					HandleEvents(AFTER_RESETINTEGRATE,pet);
					thisnet->CalculateOutput();
					HandleEvents(AFTER_RESETOUTPUT,pet);
					break;
				case NEXT_LEARN:
					HandleEvents(BEFORE_RESETLEARN,pet);
					next = thisnet->Learn(bLearnDuringReset);
					HandleEvents(AFTER_RESETLEARN,pet);
					break;
				case NEXT_ENGINE:
					break;
				}
			}

			HandleEvents(BEFORE_SETINPUT,pet);
			for(size_t t3=0,indexCounter=0;t3<ts;++t3) {
				thisnet->SetInput(indexCounter,*(mTasks[t3]->GetValuesConst()),mTimePerPattern);
				indexCounter += mTasks[t3]->GetValuesConst()->size();
			}
			HandleEvents(AFTER_SETINPUT,pet);

			next = NEXT_INTEGRATE;
			pet->SetIntegration(std::numeric_limits<size_t>::max());
			while(next != NEXT_ENGINE) {
				switch (next) {
				case NEXT_INTEGRATE:
					pet->IncrIntegration();
					HandleEvents(BEFORE_INTEGRATE,pet);
					next = thisnet->Integrate();
					HandleEvents(AFTER_INTEGRATE,pet);
					thisnet->CalculateOutput();
					HandleEvents(AFTER_OUTPUT,pet);
					break;
				case NEXT_LEARN:
					HandleEvents(BEFORE_LEARN,pet);
					next = thisnet->Learn(bLearn);
					HandleEvents(AFTER_LEARN,pet);
					break;
				case NEXT_ENGINE:
					break;
				}
			}
		}
		pet->SetNetwork(0);
		pet->SetIntegration(std::numeric_limits<size_t>::max());
		HandleEvents(END_ITERATION,pet);
	}
	pet->SetGlobalIteration(pet->GetGlobalIteration()-1);
	HandleEvents(END_PART,pet);
	pet->SetGlobalIteration(pet->GetGlobalIteration()+1);
}

void CExecutionPartV1::AddEvent(const std::string& eTime,CEvent* pev)
{
	EventTimeV1 et = DUMMY_TIME;
	if (eTime == "afterGenerate")
		et = AFTER_GENERATE;
	else if (eTime == "afterIntegrate")
		et = AFTER_INTEGRATE;
	else if (eTime == "afterLearn")
		et = AFTER_LEARN;
	else if (eTime == "afterOutput")
		et = AFTER_OUTPUT;
	else if (eTime == "afterReset")
		et = AFTER_RESET;
	else if (eTime == "afterResetIntegrate")
		et = AFTER_RESETINTEGRATE;
	else if (eTime == "afterResetLearn")
		et = AFTER_RESETLEARN;
	else if (eTime == "afterResetOutput")
		et = AFTER_RESETOUTPUT;
	else if (eTime == "afterSetInput")
		et = AFTER_SETINPUT;
	else if (eTime == "beforeGenerate")
		et = BEFORE_GENERATE;
	else if (eTime == "beforeIntegrate")
		et = BEFORE_INTEGRATE;
	else if (eTime == "beforeLearn")
		et = BEFORE_LEARN;
	else if (eTime == "beforeReset")
		et = BEFORE_RESET;
	else if (eTime == "beforeResetIntegrate")
		et = BEFORE_RESETINTEGRATE;
	else if (eTime == "beforeResetLearn")
		et = BEFORE_RESETLEARN;
	else if (eTime == "beforeSetInput")
		et = BEFORE_SETINPUT;
	else if (eTime == "beginIteration")
		et = BEGIN_ITERATION;
	else if (eTime == "beginPart")
		et = BEGIN_PART;
	else if (eTime == "endIteration")
		et = END_ITERATION;
	else if (eTime == "endPart")
		et = END_PART;
	
	if (mEvents.find(et) == mEvents.end()) {
		mEvents[et] = std::vector<CEvent*>();
	}
	mEvents[et].push_back(pev);
}

void CExecutionPartV1::AddTask(CTask* pt)
{
	mTasks.push_back(pt);
}

void CExecutionPartV1::SetTimes(const std::valarray<size_t>* piterations)
{
	pIterations = piterations;
}

void CExecutionPartV1::HandleEvents(EventTimeV1 eTime,CExTimeInfo* pet)
{
	if (mEvents.find(eTime) != mEvents.end()) {
		std::vector<CEvent*>& eventVec = mEvents[eTime];
		for(std::vector<CEvent*>::iterator it = eventVec.begin(),ite = eventVec.end();it != ite;++it) {
			(*it)->Handle(pet);
		}
	}
}

void CExecutionPartV1::SetParam(size_t p,double val)
{
	switch (p) {
	case 0:
		mTimePerPattern = val;
		break;
	case 1:
		mZeroTime = val;
		break;
	}
}

double CExecutionPartV1::GetParam(size_t p)
{
	double v = 0.0;
	switch (p) {
	case 0:
		v = mTimePerPattern;
		break;
	case 1:
		v = mZeroTime;
		break;
	}
	return v;
}

} //end namespace CORINET

