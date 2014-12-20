/*********************************************************************************************
 * Name      :  ActionRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of actions with
 *				the factory manager for the abstract CAction type. The name used here should
 *				be the name used in XML CORINET language definition.
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

#include <Event/Concr/ConcreteActions.h>
#include <Util/Factory.h>

namespace CORINET {

GET_REGISTER(CAction)

REGISTER_CLASS_2(CAction,CRecordNetState,recordNetState)
REGISTER_CLASS_2(CAction,CRecordNetInput,recordNetInput)
REGISTER_CLASS_2(CAction,CRecordNetOutput,recordNetOutput)
REGISTER_CLASS_2(CAction,CRecordNetIO,recordNetIO)
REGISTER_CLASS_2(CAction,CRecordBlockOutput,recordBlockOutput)
REGISTER_CLASS_2(CAction,CRecordWeights,recordWeights)
REGISTER_CLASS_2(CAction,CRecordSynapses,recordSynapses)
REGISTER_CLASS_2(CAction,CRecordIntegrationInput,recordIntegrationInput)
REGISTER_CLASS_2(CAction,CRecordIntegrationValues,recordIntegrationValues)
REGISTER_CLASS_2(CAction,CRecordTaskPatterns,recordTaskPatterns)
REGISTER_CLASS_2(CAction,CModifyWeights,modifyWeights)
REGISTER_CLASS_2(CAction,CModifyNetState,modifyNetState)
REGISTER_CLASS_2(CAction,CModifyBlockOutput,modifyBlockOutput)
REGISTER_CLASS_2(CAction,CModifyIntegrationInput,modifyIntegrationInput)
REGISTER_CLASS_2(CAction,CModifyIntegrationValues,modifyIntegrationValues)
REGISTER_CLASS_2(CAction,CModifyParamTask,modifyParamTask)
REGISTER_CLASS_2(CAction,CModifyParamNetwork,modifyParamNetwork)
REGISTER_CLASS_2(CAction,CModifyParamExecution,modifyParamExecution)

} //end namespace CORINET

