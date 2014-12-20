/*********************************************************************************************
 * Name      :  XMLStrDefs.h
 *
 * Purpose   :  Keywords from CORINET Markup Language defined in Xerces-C XMLCh format.
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

#ifndef CORINET_XMLSTRDEFS
#define CORINET_XMLSTRDEFS

#include <Platform/Platform.h>
#include <xercesc/util/XMLUniDefs.hpp>

namespace CORINET {

class XMLStrDefs {
public:
	//root element + attributes
	static const XMLCh experiment[];
	static const XMLCh definitionFile[];
	static const XMLCh sandBoxFiles[];

	//inputSection
	static const XMLCh inputBlock[];
	static const XMLCh id[];
	static const XMLCh inputIndices[];
	static const XMLCh inputRange[];
	static const XMLCh begin[];
	static const XMLCh end[];
	static const XMLCh step[];

	//networkSection
	static const XMLCh network[];
	static const XMLCh inputs[];
	static const XMLCh type[];
	static const XMLCh netParams[];
	static const XMLCh param[];
	static const XMLCh name[];
	static const XMLCh value[];
	static const XMLCh loopParam[];
	static const XMLCh values[];
	static const XMLCh block[];
	static const XMLCh blockNormal[];
	static const XMLCh nodes[];
	static const XMLCh outputBlock[];
	static const XMLCh blockParams[];
	static const XMLCh integrationSite[];
	static const XMLCh location[];
	static const XMLCh siteParams[];
	static const XMLCh inputRefs[];	
	static const XMLCh weights[];
	static const XMLCh normalisation[];
	static const XMLCh normParams[];
	static const XMLCh initialisation[];
	static const XMLCh initParams[];
	static const XMLCh randGen[];
	static const XMLCh seed[];
	static const XMLCh w[];
	static const XMLCh n[];
	static const XMLCh i[];
	static const XMLCh outputFunction[];
	static const XMLCh outputParams[];
	static const XMLCh noiseFunction[];
	static const XMLCh noiseParams[];
	static const XMLCh attenuation[];

	//taskSection
	static const XMLCh task[];
	static const XMLCh taskParams[];
	static const XMLCh patternSet[];
	static const XMLCh p[];
	static const XMLCh c[];
	static const XMLCh r[];
	static const XMLCh columns[];
	static const XMLCh rows[];
	static const XMLCh store[];
	static const XMLCh sampleMethod[];
	static const XMLCh withReplacement[];
	static const XMLCh withoutReplacement[];
	static const XMLCh dataSource[];
	static const XMLCh patterns[];
	static const XMLCh sourceParams[];
	static const XMLCh compositeTask[];
	static const XMLCh insert[];
	static const XMLCh insertParams[];
	static const XMLCh inColumn[];
	static const XMLCh inRow[];

	//executionSection
	static const XMLCh execution[];
	static const XMLCh executionSection[];
	static const XMLCh networks[];
	static const XMLCh runs[];
	static const XMLCh loop[];
	static const XMLCh targets[];
	static const XMLCh numValues[];
	static const XMLCh sequence[];
	static const XMLCh repeat[];
	static const XMLCh part[];
	static const XMLCh phase[];
	static const XMLCh learnDuringReset[];
	static const XMLCh iterations[];
	static const XMLCh test[];
	static const XMLCh tasks[];
	static const XMLCh random[];

	//defaultSection
	static const XMLCh typeDefaults[];
	static const XMLCh xmldefault[];
	static const XMLCh types[];
	static const XMLCh numSites[];
	static const XMLCh targetDefaults[];

	//eventSection
	static const XMLCh event[];
	static const XMLCh parts[];
	static const XMLCh eventTime[];
	static const XMLCh condition[];
	static const XMLCh variable[];
	static const XMLCh record[];
	static const XMLCh precision[];
	static const XMLCh report[];
	static const XMLCh operation[];
	static const XMLCh modify[];
	static const XMLCh nodeIndices[];
	static const XMLCh modifyParam[];
	static const XMLCh paramName[];
	static const XMLCh xmlstdout[];

	//from languageDefinition
	static const XMLCh languageDefinition[];
	static const XMLCh codeFile[];
	static const XMLCh nr[];
	static const XMLCh Section[];
	static const XMLCh use[];
	static const XMLCh state[];
	static const XMLCh optional[];
	static const XMLCh required[];
	static const XMLCh prohibited[];
	static const XMLCh ignored[];
	static const XMLCh annotation[];
	static const XMLCh appinfo[];
	static const XMLCh documentation[];
	static const XMLCh source[];

	//from codeGenerator
	static const XMLCh codeGenerator[];
	static const XMLCh intro[];
	static const XMLCh hFile[];
	static const XMLCh cppFile[];
	static const XMLCh line[];
	static const XMLCh tab[];
	static const XMLCh insertText[];

	//from results
	static const XMLCh results[];

	//from experimentList
	static const XMLCh experimentList[];
	static const XMLCh file[];

	//from patternGenerator
	static const XMLCh patternGenerator[];

	//from randTest
	static const XMLCh randTest[];

	//various
	static const XMLCh LS[];
	static const XMLCh Params[];
};

} //end namespace CORINET

#endif //CORINET_XMLSTRDEFS

