/*********************************************************************************************
 * Name      :  AttenuationRegister.cpp
 *
 * Purpose   :  This file registers the available concrete types of attenuation functions with
 *				the factory manager for the abstract FAttenuation type. The name used here should
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

#include <Common/Concr/ConcreteAttenuation.h>
#include <Util/Factory.h>

namespace CORINET {

GET_REGISTER(FAttenuation)

REGISTER_CLASS_1(FAttenuation,FAttenuationClipLow,clipLow)
REGISTER_CLASS_1(FAttenuation,FAttenuationClip,clip)
REGISTER_CLASS_1(FAttenuation,FAttenuationTime1,time1)

} //end namespace CORINET
