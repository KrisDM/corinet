/*********************************************************************************************
 * Name      :  XMLSchemaLocations.cpp
 *
 * Purpose   :  Schema locations from CORINET Markup Language defined in Xerces-C XMLCh format.
 *				The locations are defined relative to the CORINETROOT environment variable.
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

#include <XMLUtil/XMLSchemaDefs.h>
#include <xercesc/util/XMLUniDefs.hpp>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

const XMLCh XMLSchemaNames::CORINETSetup[] = 
{
	chLatin_h,chLatin_t,chLatin_t,chLatin_p,chColon,chForwardSlash,chForwardSlash,
	chLatin_w,chLatin_w,chLatin_w,chPeriod,
	chLatin_c,chLatin_o,chLatin_r,chLatin_i,chLatin_n,chLatin_e,chLatin_t,chPeriod,
	chLatin_o,chLatin_r,chLatin_g,chForwardSlash,
	chLatin_n,chLatin_a,chLatin_m,chLatin_e,chLatin_s,chLatin_p,chLatin_a,chLatin_c,chLatin_e,chLatin_s,chForwardSlash,
	chLatin_C,chLatin_O,chLatin_R,chLatin_I,chLatin_N,chLatin_E,chLatin_T,
	chLatin_S,chLatin_e,chLatin_t,chLatin_u,chLatin_p,chNull
};

const XMLCh XMLSchemaNames::CORINETSetupList[] = 
{
	chLatin_h,chLatin_t,chLatin_t,chLatin_p,chColon,chForwardSlash,chForwardSlash,
	chLatin_w,chLatin_w,chLatin_w,chPeriod,
	chLatin_c,chLatin_o,chLatin_r,chLatin_i,chLatin_n,chLatin_e,chLatin_t,chPeriod,
	chLatin_o,chLatin_r,chLatin_g,chForwardSlash,
	chLatin_n,chLatin_a,chLatin_m,chLatin_e,chLatin_s,chLatin_p,chLatin_a,chLatin_c,chLatin_e,chLatin_s,chForwardSlash,
	chLatin_C,chLatin_O,chLatin_R,chLatin_I,chLatin_N,chLatin_E,chLatin_T,
	chLatin_S,chLatin_e,chLatin_t,chLatin_u,chLatin_p,chForwardSlash,
	chLatin_L,chLatin_i,chLatin_s,chLatin_t,chNull
};

const XMLCh XMLSchemaNames::CORINETDefinition[] = 
{
	chLatin_h,chLatin_t,chLatin_t,chLatin_p,chColon,chForwardSlash,chForwardSlash,
	chLatin_w,chLatin_w,chLatin_w,chPeriod,
	chLatin_c,chLatin_o,chLatin_r,chLatin_i,chLatin_n,chLatin_e,chLatin_t,chPeriod,
	chLatin_o,chLatin_r,chLatin_g,chForwardSlash,
	chLatin_n,chLatin_a,chLatin_m,chLatin_e,chLatin_s,chLatin_p,chLatin_a,chLatin_c,chLatin_e,chLatin_s,chForwardSlash,
	chLatin_C,chLatin_O,chLatin_R,chLatin_I,chLatin_N,chLatin_E,chLatin_T,
	chLatin_D,chLatin_e,chLatin_f,chLatin_i,chLatin_n,chLatin_i,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLSchemaNames::CORINETGenerator[] = 
{
	chLatin_h,chLatin_t,chLatin_t,chLatin_p,chColon,chForwardSlash,chForwardSlash,
	chLatin_w,chLatin_w,chLatin_w,chPeriod,
	chLatin_c,chLatin_o,chLatin_r,chLatin_i,chLatin_n,chLatin_e,chLatin_t,chPeriod,
	chLatin_o,chLatin_r,chLatin_g,chForwardSlash,
	chLatin_n,chLatin_a,chLatin_m,chLatin_e,chLatin_s,chLatin_p,chLatin_a,chLatin_c,chLatin_e,chLatin_s,chForwardSlash,
	chLatin_C,chLatin_O,chLatin_R,chLatin_I,chLatin_N,chLatin_E,chLatin_T,
	chLatin_D,chLatin_e,chLatin_f,chLatin_i,chLatin_n,chLatin_i,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chForwardSlash,
	chLatin_G,chLatin_e,chLatin_n,chLatin_e,chLatin_r,chLatin_a,chLatin_t,chLatin_o,chLatin_r,chNull
};

const XMLCh XMLSchemaNames::CORINETResults[] = 
{
	chLatin_h,chLatin_t,chLatin_t,chLatin_p,chColon,chForwardSlash,chForwardSlash,
	chLatin_w,chLatin_w,chLatin_w,chPeriod,
	chLatin_c,chLatin_o,chLatin_r,chLatin_i,chLatin_n,chLatin_e,chLatin_t,chPeriod,
	chLatin_o,chLatin_r,chLatin_g,chForwardSlash,
	chLatin_n,chLatin_a,chLatin_m,chLatin_e,chLatin_s,chLatin_p,chLatin_a,chLatin_c,chLatin_e,chLatin_s,chForwardSlash,
	chLatin_C,chLatin_O,chLatin_R,chLatin_I,chLatin_N,chLatin_E,chLatin_T,
	chLatin_R,chLatin_e,chLatin_s,chLatin_u,chLatin_l,chLatin_t,chLatin_s,chNull
};

const XMLCh XMLSchemaNames::XSI[] = 
{
	chLatin_h,chLatin_t,chLatin_t,chLatin_p,chColon,chForwardSlash,chForwardSlash,
	chLatin_w,chLatin_w,chLatin_w,chPeriod,
	chLatin_w,chDigit_3,chPeriod,
	chLatin_o,chLatin_r,chLatin_g,chForwardSlash,
	chDigit_2,chDigit_0,chDigit_0,chDigit_1,chForwardSlash,
	chLatin_X,chLatin_M,chLatin_L,chLatin_S,chLatin_c,chLatin_h,chLatin_e,chLatin_m,chLatin_a,chDash,
	chLatin_i,chLatin_n,chLatin_s,chLatin_t,chLatin_a,chLatin_n,chLatin_c,chLatin_e,chNull
};

const XMLCh XMLSchemaNames::xsi[] =
{
	chLatin_x,chLatin_m,chLatin_l,chLatin_n,chLatin_s,chColon,chLatin_x,chLatin_s,chLatin_i,chNull
};

const XMLCh XMLSchemaNames::xmlns[] =
{
	chLatin_x,chLatin_m,chLatin_l,chLatin_n,chLatin_s,chNull
};

const XMLCh XMLSchemaNames::schemaLocation[] =
{
	chLatin_x,chLatin_s,chLatin_i,chColon,
	chLatin_s,chLatin_c,chLatin_h,chLatin_e,chLatin_m,chLatin_a,
	chLatin_L,chLatin_o,chLatin_c,chLatin_a,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLSchemaLocations::CORINETSetup[] = 
{
	chPeriod,chForwardSlash,
	chLatin_c,chLatin_o,chLatin_d,chLatin_e,chForwardSlash,
	chLatin_x,chLatin_m,chLatin_l,chForwardSlash,
	chLatin_S,chLatin_e,chLatin_t,chLatin_u,chLatin_p,chForwardSlash,
	chLatin_e,chLatin_x,chLatin_p,chLatin_e,chLatin_r,chLatin_i,chLatin_m,chLatin_e,chLatin_n,chLatin_t,
	chLatin_S,chLatin_e,chLatin_t,chLatin_u,chLatin_p,chPeriod,
	chLatin_x,chLatin_s,chLatin_d,chNull
};

const XMLCh XMLSchemaLocations::CORINETSetupList[] = 
{
	chPeriod,chForwardSlash,
	chLatin_c,chLatin_o,chLatin_d,chLatin_e,chForwardSlash,
	chLatin_x,chLatin_m,chLatin_l,chForwardSlash,
	chLatin_S,chLatin_e,chLatin_t,chLatin_u,chLatin_p,chForwardSlash,
	chLatin_e,chLatin_x,chLatin_p,chLatin_e,chLatin_r,chLatin_i,chLatin_m,chLatin_e,chLatin_n,chLatin_t,
	chLatin_L,chLatin_i,chLatin_s,chLatin_t,chPeriod,
	chLatin_x,chLatin_s,chLatin_d,chNull
};

const XMLCh XMLSchemaLocations::CORINETDefinition[] = 
{
	chPeriod,chForwardSlash,
	chLatin_c,chLatin_o,chLatin_d,chLatin_e,chForwardSlash,
	chLatin_x,chLatin_m,chLatin_l,chForwardSlash,
	chLatin_D,chLatin_e,chLatin_f,chLatin_i,chLatin_n,chLatin_i,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chForwardSlash,
	chLatin_l,chLatin_a,chLatin_n,chLatin_g,chLatin_u,chLatin_a,chLatin_g,chLatin_e,
	chLatin_D,chLatin_e,chLatin_f,chLatin_i,chLatin_n,chLatin_i,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chPeriod,
	chLatin_x,chLatin_s,chLatin_d,chNull
};

const XMLCh XMLSchemaLocations::CORINETGenerator[] = 
{
	chPeriod,chForwardSlash,
	chLatin_c,chLatin_o,chLatin_d,chLatin_e,chForwardSlash,
	chLatin_x,chLatin_m,chLatin_l,chForwardSlash,
	chLatin_D,chLatin_e,chLatin_f,chLatin_i,chLatin_n,chLatin_i,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chForwardSlash,
	chLatin_c,chLatin_o,chLatin_d,chLatin_e,
	chLatin_G,chLatin_e,chLatin_n,chLatin_e,chLatin_r,chLatin_a,chLatin_t,chLatin_o,chLatin_r,chPeriod,
	chLatin_x,chLatin_s,chLatin_d,chNull
};

const XMLCh XMLSchemaLocations::CORINETResults[] = 
{
	chPeriod,chForwardSlash,
	chLatin_c,chLatin_o,chLatin_d,chLatin_e,chForwardSlash,
	chLatin_x,chLatin_m,chLatin_l,chForwardSlash,
	chLatin_R,chLatin_e,chLatin_s,chLatin_u,chLatin_l,chLatin_t,chLatin_s,chForwardSlash,
	chLatin_r,chLatin_e,chLatin_s,chLatin_u,chLatin_l,chLatin_t,chLatin_s,
	chLatin_F,chLatin_i,chLatin_l,chLatin_e,chPeriod,
	chLatin_x,chLatin_s,chLatin_d,chNull
};

} //end namespace CORINET


