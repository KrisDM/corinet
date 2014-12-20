/*********************************************************************************************
 * Name      :  TaskRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of tasks with
 *				the factory manager for the abstract CTask type. The name used here should
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

#include <Util/Factory.h>
#include <Task/Concr/ConcreteTasks.h>

namespace CORINET {

GET_REGISTER(CTask)

REGISTER_CLASS_1(CTask,CTaskSet1,set1)
REGISTER_CLASS_1(CTask,CTaskSet2,set2)
REGISTER_CLASS_1(CTask,CTaskSet3,set3)
REGISTER_CLASS_1(CTask,CTaskAddExtraBits1,addExtraBits1)
REGISTER_CLASS_1(CTask,CTaskBits1,bits1)
REGISTER_CLASS_1(CTask,CTaskBits2,bits2)
REGISTER_CLASS_1(CTask,CTaskBars1,bars1)
REGISTER_CLASS_1(CTask,CTaskBars2,bars2)
REGISTER_CLASS_1(CTask,CTaskBars3,bars3)
REGISTER_CLASS_1(CTask,CTaskBars4,bars4)
REGISTER_CLASS_1(CTask,CTaskBars5,bars5)
REGISTER_CLASS_1(CTask,CTaskInsertIndependent,insertIndependent);

} //end namespace CORINET
