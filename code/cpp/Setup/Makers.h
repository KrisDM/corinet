/*********************************************************************************************
 * Name      :  Makers.h
 *
 * Purpose   :  Structs containing all information to set up experiments. They provide an
 *				intermediary step between engine, network and task objects on one side, and a 
 *				non-specific way of providing the setup information (through either XML
 *				setup files, or through some interactive method).
 *				 
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

#ifndef CORINET_MAKERS
#define CORINET_MAKERS

#include <Platform/Platform.h>
#include <Util/Constants.h>
#include <valarray>
#include <string>
#include <map>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////////////

namespace CORINET {

struct ECreation {
	std::string message;
	ECreation(const std::string& t1,const std::string& t2);
};

//////////////////////////////////////////////////////////////////////////////////////////////////

struct SMaker {
	const std::string makerType;
	const std::string type;
	SMaker(const std::string&,const std::string&);
};

//////////////////////////////////////////////////////////////////////////////////////////////////

struct SRandGenMaker : public SMaker {
	SRandGenMaker(const std::string&);
	double randParams[gNumParams];
	size_t seed;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

struct SAttenuationMaker : public SMaker {
	SAttenuationMaker(const std::string&);
	double attenuationParams[gNumParams];
	bool state;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

struct SNoiseFunctionMaker : public SMaker {
	SNoiseFunctionMaker(const std::string&);
	double noiseParams[gNumParams];
	bool state;
	SRandGenMaker* randMaker;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

struct SInitialisationMaker : public SMaker {
	SInitialisationMaker(const std::string&);
	double initParams[gNumParams];
	bool state;
	SRandGenMaker* randMaker;
	const std::valarray<double>* weightVals;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

struct SNormalisationMaker : public SMaker {
	SNormalisationMaker(const std::string&);
	double normParams[gNumParams];
	bool state;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

struct SOutputFunctionMaker : public SMaker {
	SOutputFunctionMaker(const std::string&);
	double outputParams[gNumParams];
	bool state;
	SAttenuationMaker* attenuationMaker;
	SNoiseFunctionMaker* noiseMaker;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

struct SIntegrationSiteMaker : public SMaker {
	SIntegrationSiteMaker(const std::string&,const std::string&);
	const std::string idStr;
	double siteParams[gNumParams];
	std::valarray<size_t>* inputIndex;
	SInitialisationMaker* initMaker;
	SNormalisationMaker* normMaker;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SBlockMaker : public SMaker {
	SBlockMaker(const std::string&,const std::string&);
	const std::string idStr;
	double blockParams[gNumParams];
	bool outputBlock;
	size_t beginNode;
	size_t numNodes;
	std::vector<SIntegrationSiteMaker*> siteMakers;
	SOutputFunctionMaker* outputMaker;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SNetworkMaker : public SMaker {
	SNetworkMaker(const std::string&,const std::string&);
	const std::string idStr;
	double netParams[gNumParams];
	size_t numInputs;
	size_t numNodes;
	std::vector<SBlockMaker*> blockMakers;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SDataSourceMaker : public SMaker {
	SDataSourceMaker(const std::string&);
	double sourceParams[gNumParams];
	size_t columns;
	size_t rows;
	size_t patterns;
};

struct SInsertMaker;//forward declaration

struct STaskMaker : public SMaker {
	STaskMaker(const std::string&,const std::string&);
	const std::string idStr;
	double taskParams[gNumParams];
	size_t columns;
	size_t rows;
	size_t store;
	size_t seed;
	std::string sampleMethod;
	SAttenuationMaker* attenuationMaker;
	SNoiseFunctionMaker* noiseMaker;
	SDataSourceMaker* dataMaker; //only for simple tasks
	const std::vector<const std::valarray<double>*>* patterns; //only for simple tasks
	std::vector<SInsertMaker*> insertMakers; //only for composite tasks
};

struct SInsertMaker : public SMaker {
	SInsertMaker(const std::string&);
	double insertParams[gNumParams];
	size_t inColumn;
	size_t inRow;
	std::vector<STaskMaker*> taskMakers;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SConditionMaker : public SMaker {
	SConditionMaker(const std::string&);
	const std::valarray<double>* conditionVals;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SOperationMaker : public SMaker {
	SOperationMaker(const std::string&);
	const std::valarray<double>* modifyVals;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SReportMaker : public SMaker { 
	SReportMaker(const std::string&,const std::string&);
	const std::string location;
	void* sink;//connection to writing destination, properly set up
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SActionMaker : public SMaker {
	SActionMaker(const std::string&);
	std::vector<SMaker*> targets;
	std::valarray<size_t>* paramNums;
	std::vector<SOperationMaker*> opMakers;
	std::valarray<size_t>* inputIndices;
	std::valarray<size_t>* nodeIndices;
	size_t precision;
	SReportMaker* reportMaker;
};
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SEventMaker : public SMaker {
	SEventMaker(const std::string&);
	std::multimap<const std::string,SConditionMaker*> condMakers;
	std::vector<SActionMaker*> actionMakers;	
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SLoopElementMaker : public SMaker {
	SLoopElementMaker(const std::string&);
	std::vector<SMaker*> targets;
	std::valarray<size_t>* paramNums;
	std::vector<std::valarray<double>*> values;
};

struct SLoopMaker : public SMaker {
	SLoopMaker(const std::string&);
	size_t numConfigs;
	std::vector<SLoopElementMaker*> elemMakers;
};

struct SLoopsMaker : public SMaker {
	SLoopsMaker(const std::string&);
	std::vector<SLoopMaker*> loopMakers;
};

struct SExecutionElementMaker : public SMaker {
	SExecutionElementMaker(const std::string&);
	double executeParams[gNumParams];
	bool random;
	bool learn;
	bool learnDuringReset;
	bool generate;
	const std::valarray<size_t>* timeValues;
	std::map<const std::string,std::vector<SEventMaker*> > eventMakers;
	std::vector<STaskMaker*> taskMakers;
	std::vector<SExecutionElementMaker*> partMakers;
};

struct SExecutionMaker : public SMaker {
	SExecutionMaker(const std::string&);
	size_t numRuns;
	std::vector<SNetworkMaker*> netMakers;
	std::vector<STaskMaker*> taskMakers;
	std::vector<SEventMaker*> eventMakers;
	SLoopsMaker* loopsMaker;
	SExecutionElementMaker* sequenceMaker;
	SRandGenMaker* randMaker;
	SReportMaker* reportMaker;
	size_t precision;
};

struct SStatusMaker : public SMaker {
	SStatusMaker(const std::string&);
	size_t numExecutions;
};

struct SEngineMaker : public SMaker {
	SEngineMaker(const std::string&);
	std::vector<SExecutionMaker*> executionMakers;
	SStatusMaker* statusMaker;
};

} //end namespace CORINET

#endif //CORINET_MAKERS

