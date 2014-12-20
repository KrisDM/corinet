/*********************************************************************************************
 * Name      :  Makers.cpp
 *
 * Purpose   :  Constructors for makers structs.
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

#include <Setup/Makers.h>
#include <limits>

namespace CORINET {

ECreation::ECreation(const std::string& t1,const std::string& t2)
{
	message = "Error during creation of " + t1 + ": unregistered type \"" + t2 + "\".\n";
}

//////////////////////////////////////////////////////////////////////////////////////////////////

SMaker::SMaker(const std::string& t,const std::string& mt) : makerType(mt),type(t)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////

SRandGenMaker::SRandGenMaker(const std::string& t) : SMaker(t,"randGen")
{
	for(size_t i=0;i<gNumParams;i++)
		randParams[i] = 0.0;
	seed = std::numeric_limits<size_t>::max();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

SAttenuationMaker::SAttenuationMaker(const std::string& t) : SMaker(t,"attenuation"),state(false)
{
	for(size_t i=0;i<gNumParams;i++)
		attenuationParams[i] = 0.0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

SNoiseFunctionMaker::SNoiseFunctionMaker(const std::string& t) : SMaker(t,"noiseFunction"),state(false),randMaker(0)
{
	for(size_t i=0;i<gNumParams;i++)
		noiseParams[i] = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

SInitialisationMaker::SInitialisationMaker(const std::string& t) : SMaker(t,"initialisation"),state(false),
																	randMaker(0),weightVals(0)
{
	for(size_t i=0;i<gNumParams;i++)
		initParams[i] = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

SNormalisationMaker::SNormalisationMaker(const std::string& t) : SMaker(t,"normalisation"),state(false)
{
	for(size_t i=0;i<gNumParams;i++)
		normParams[i] = 0.0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

SOutputFunctionMaker::SOutputFunctionMaker(const std::string& t) : SMaker(t,"outputFunction"),state(false),
															attenuationMaker(0),noiseMaker(0)
{
	for(size_t i=0;i<gNumParams;i++)
		outputParams[i] = 0.0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

SIntegrationSiteMaker::SIntegrationSiteMaker(const std::string& t,const std::string& id) : SMaker(t,"integrationSite"),
																			idStr(id),inputIndex(0),initMaker(0),normMaker(0)
{
	for(size_t i=0;i<gNumParams;i++)
		siteParams[i] = 0.0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

SBlockMaker::SBlockMaker(const std::string& t,const std::string& id) : SMaker(t,"block"),idStr(id),outputBlock(false),
														beginNode(0),numNodes(0),siteMakers(),outputMaker(0)
{
	for(size_t i=0;i<gNumParams;i++)
		blockParams[i] = 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

SNetworkMaker::SNetworkMaker(const std::string& t,const std::string& id) : SMaker(t,"network"),idStr(id),numInputs(0),numNodes(0),blockMakers()
{
	for(size_t i=0;i<gNumParams;i++)
		netParams[i] = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

SDataSourceMaker::SDataSourceMaker(const std::string& t) : SMaker(t,"dataSource"),columns(0),rows(0),patterns(0)
{
	for(size_t i=0;i<gNumParams;i++)
		sourceParams[i] = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

STaskMaker::STaskMaker(const std::string& t,const std::string& id) : SMaker(t,"task"),idStr(id),columns(0),rows(0),store(0),seed(std::numeric_limits<size_t>::max()),
												sampleMethod(""),attenuationMaker(0),noiseMaker(0),dataMaker(0),patterns(0),insertMakers()
{
	for(size_t i=0;i<gNumParams;i++)
		taskParams[i] = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

SInsertMaker::SInsertMaker(const std::string& t) : SMaker(t,"insert"),inColumn(0),inRow(0),taskMakers()
{
	for(size_t i=0;i<gNumParams;i++)
		insertParams[i] = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

SConditionMaker::SConditionMaker(const std::string& t) : SMaker(t,"condition"),conditionVals(0)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

SOperationMaker::SOperationMaker(const std::string& t) : SMaker(t,"operation"),modifyVals(0)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

SReportMaker::SReportMaker(const std::string& t,const std::string& l) : SMaker(t,"report"),location(l),sink(0)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

SActionMaker::SActionMaker(const std::string& t) : SMaker(t,"action"),targets(0),paramNums(0),opMakers(),
												   inputIndices(0),nodeIndices(0),precision(4),reportMaker(0)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

SEventMaker::SEventMaker(const std::string& t) : SMaker(t,"event"),condMakers(),actionMakers()
{
		
}
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////

SLoopElementMaker::SLoopElementMaker(const std::string& t) : SMaker(t,"loopElem"),targets(0),paramNums(0),values(0)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

SLoopMaker::SLoopMaker(const std::string& t) : SMaker(t,"loop"),numConfigs(1),elemMakers()
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

SLoopsMaker::SLoopsMaker(const std::string& t) : SMaker(t,"loops"),loopMakers()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

SExecutionElementMaker::SExecutionElementMaker(const std::string& t) : SMaker(t,"executionElement"),
																random(false),learn(false),learnDuringReset(false),generate(false),
																timeValues(0),eventMakers(),taskMakers(),partMakers()
{
	for(size_t i=0;i<gNumParams;i++)
		executeParams[i] = 0.0;
}

SExecutionMaker::SExecutionMaker(const std::string& t) : SMaker(t,"execution"),numRuns(1),netMakers(),taskMakers(),eventMakers(),
												  loopsMaker(0),sequenceMaker(0),randMaker(0),reportMaker(0),precision(4)
{
	
}

SStatusMaker::SStatusMaker(const std::string& t) : SMaker(t,"status"),numExecutions(0)
{

}

SEngineMaker::SEngineMaker(const std::string& t) : SMaker(t,"engine"),executionMakers(),statusMaker(0)
{

}

} //end namespace CORINETSetup


