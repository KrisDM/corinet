/*********************************************************************************************
 * Name      :  XMLStrDefs.cpp
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

#include <XMLUtil/XMLStrDefs.h>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//root element + attributes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::experiment[] = 
{
	chLatin_e,chLatin_x,chLatin_p,chLatin_e,chLatin_r,chLatin_i,chLatin_m,chLatin_e,chLatin_n,chLatin_t,chNull
};

const XMLCh XMLStrDefs::definitionFile[] =
{
	chLatin_d,chLatin_e,chLatin_f,chLatin_i,chLatin_n,chLatin_i,chLatin_t,chLatin_i,chLatin_o,chLatin_n,
	chLatin_F,chLatin_i,chLatin_l,chLatin_e,chNull
};

const XMLCh XMLStrDefs::sandBoxFiles[] =
{
	chLatin_s,chLatin_a,chLatin_n,chLatin_d,
	chLatin_B,chLatin_o,chLatin_x,
	chLatin_F,chLatin_i,chLatin_l,chLatin_e,chLatin_s,chNull
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//inputSection
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::inputBlock[] =
{
	chLatin_i,chLatin_n,chLatin_p,chLatin_u,chLatin_t,
	chLatin_B,chLatin_l,chLatin_o,chLatin_c,chLatin_k,chNull
};

const XMLCh XMLStrDefs::id[] =
{
	chLatin_i,chLatin_d,chNull
};

const XMLCh XMLStrDefs::inputIndices[] = 
{
	chLatin_i,chLatin_n,chLatin_p,chLatin_u,chLatin_t,
	chLatin_I,chLatin_n,chLatin_d,chLatin_i,chLatin_c,chLatin_e,chLatin_s,chNull
};

const XMLCh XMLStrDefs::inputRange[] =
{
	chLatin_i,chLatin_n,chLatin_p,chLatin_u,chLatin_t,
	chLatin_R,chLatin_a,chLatin_n,chLatin_g,chLatin_e,chNull
};

const XMLCh XMLStrDefs::begin[] =
{
	chLatin_b,chLatin_e,chLatin_g,chLatin_i,chLatin_n,chNull
};

const XMLCh XMLStrDefs::end[] =
{
	chLatin_e,chLatin_n,chLatin_d,chNull
};

const XMLCh XMLStrDefs::step[] =
{
	chLatin_s,chLatin_t,chLatin_e,chLatin_p,chNull
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//networkSection
///////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::network[] = 
{
	chLatin_n,chLatin_e,chLatin_t,chLatin_w,chLatin_o,chLatin_r,chLatin_k,chNull
};

const XMLCh XMLStrDefs::inputs[] = 
{
	chLatin_i,chLatin_n,chLatin_p,chLatin_u,chLatin_t,chLatin_s,chNull
};

const XMLCh XMLStrDefs::type[] =
{
	chLatin_t,chLatin_y,chLatin_p,chLatin_e,chNull
};

const XMLCh XMLStrDefs::netParams[] = 
{
	chLatin_n,chLatin_e,chLatin_t,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chLatin_s,chNull
};

const XMLCh XMLStrDefs::param[] =
{
	chLatin_p,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chNull
};

const XMLCh XMLStrDefs::name[] =
{
	chLatin_n,chLatin_a,chLatin_m,chLatin_e,chNull
};

const XMLCh XMLStrDefs::value[] =
{
	chLatin_v,chLatin_a,chLatin_l,chLatin_u,chLatin_e,chNull
};

const XMLCh XMLStrDefs::loopParam[] =
{
	chLatin_l,chLatin_o,chLatin_o,chLatin_p,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chNull
};

const XMLCh XMLStrDefs::values[] =
{
	chLatin_v,chLatin_a,chLatin_l,chLatin_u,chLatin_e,chLatin_s,chNull
};

const XMLCh XMLStrDefs::block[] =
{
	chLatin_b,chLatin_l,chLatin_o,chLatin_c,chLatin_k,chNull
};

const XMLCh XMLStrDefs::blockNormal[] =
{
	chLatin_b,chLatin_l,chLatin_o,chLatin_c,chLatin_k,
	chLatin_N,chLatin_o,chLatin_r,chLatin_m,chLatin_a,chLatin_l,chNull
};

const XMLCh XMLStrDefs::nodes[] =
{
	chLatin_n,chLatin_o,chLatin_d,chLatin_e,chLatin_s,chNull
};

const XMLCh XMLStrDefs::outputBlock[] =
{
	chLatin_o,chLatin_u,chLatin_t,chLatin_p,chLatin_u,chLatin_t,
	chLatin_B,chLatin_l,chLatin_o,chLatin_c,chLatin_k,chNull
};

const XMLCh XMLStrDefs::blockParams[] =
{
	chLatin_b,chLatin_l,chLatin_o,chLatin_c,chLatin_k,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chLatin_s,chNull
};

const XMLCh XMLStrDefs::integrationSite[] = 
{
	chLatin_i,chLatin_n,chLatin_t,chLatin_e,chLatin_g,chLatin_r,chLatin_a,chLatin_t,chLatin_i,chLatin_o,chLatin_n,
	chLatin_S,chLatin_i,chLatin_t,chLatin_e,chNull
};

const XMLCh XMLStrDefs::location[] =
{
	chLatin_l,chLatin_o,chLatin_c,chLatin_a,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::inputRefs[] =
{
	chLatin_i,chLatin_n,chLatin_p,chLatin_u,chLatin_t,
	chLatin_R,chLatin_e,chLatin_f,chLatin_s,chNull
};

const XMLCh XMLStrDefs::siteParams[] =
{
	chLatin_s,chLatin_i,chLatin_t,chLatin_e,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chLatin_s,chNull
};

const XMLCh XMLStrDefs::weights[] =
{
	chLatin_w,chLatin_e,chLatin_i,chLatin_g,chLatin_h,chLatin_t,chLatin_s,chNull
};

const XMLCh XMLStrDefs::normalisation[] =
{
	chLatin_n,chLatin_o,chLatin_r,chLatin_m,chLatin_a,chLatin_l,chLatin_i,chLatin_s,chLatin_a,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::normParams[] =
{
	chLatin_n,chLatin_o,chLatin_r,chLatin_m,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chLatin_s,chNull
};

const XMLCh XMLStrDefs::initialisation[] =
{
	chLatin_i,chLatin_n,chLatin_i,chLatin_t,chLatin_i,chLatin_a,chLatin_l,chLatin_i,chLatin_s,chLatin_a,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::initParams[] =
{
	chLatin_i,chLatin_n,chLatin_i,chLatin_t,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chLatin_s,chNull
};

const XMLCh XMLStrDefs::randGen[] =
{
	chLatin_r,chLatin_a,chLatin_n,chLatin_d,
	chLatin_G,chLatin_e,chLatin_n,chNull
};

const XMLCh XMLStrDefs::seed[] =
{
	chLatin_s,chLatin_e,chLatin_e,chLatin_d,chNull
};

const XMLCh XMLStrDefs::w[] =
{
	chLatin_w,chNull
};

const XMLCh XMLStrDefs::n[] =
{
	chLatin_n,chNull
};

const XMLCh XMLStrDefs::i[] =
{
	chLatin_i,chNull
};

const XMLCh XMLStrDefs::outputFunction[] = 
{
	chLatin_o,chLatin_u,chLatin_t,chLatin_p,chLatin_u,chLatin_t,
	chLatin_F,chLatin_u,chLatin_n,chLatin_c,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::outputParams[] = 
{
	chLatin_o,chLatin_u,chLatin_t,chLatin_p,chLatin_u,chLatin_t,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chLatin_s,chNull
};

const XMLCh XMLStrDefs::noiseFunction[] = 
{
	chLatin_n,chLatin_o,chLatin_i,chLatin_s,chLatin_e,
	chLatin_F,chLatin_u,chLatin_n,chLatin_c,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::noiseParams[] = 
{
	chLatin_n,chLatin_o,chLatin_i,chLatin_s,chLatin_e,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chLatin_s,chNull
};

const XMLCh XMLStrDefs::attenuation[] =
{
	chLatin_a,chLatin_t,chLatin_t,chLatin_e,chLatin_n,chLatin_u,chLatin_a,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//taskSection
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::task[] =
{
	chLatin_t,chLatin_a,chLatin_s,chLatin_k,chNull
};

const XMLCh XMLStrDefs::taskParams[] = 
{
	chLatin_t,chLatin_a,chLatin_s,chLatin_k,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chLatin_s,chNull
};

const XMLCh XMLStrDefs::patternSet[] =
{
	chLatin_p,chLatin_a,chLatin_t,chLatin_t,chLatin_e,chLatin_r,chLatin_n,
	chLatin_S,chLatin_e,chLatin_t,chNull
};

const XMLCh XMLStrDefs::patterns[] =
{
	chLatin_p,chLatin_a,chLatin_t,chLatin_t,chLatin_e,chLatin_r,chLatin_n,chLatin_s,chNull
};

const XMLCh XMLStrDefs::dataSource[] = 
{
	chLatin_d,chLatin_a,chLatin_t,chLatin_a,
	chLatin_S,chLatin_o,chLatin_u,chLatin_r,chLatin_c,chLatin_e,chNull
};

const XMLCh XMLStrDefs::sourceParams[] = 
{
	chLatin_s,chLatin_o,chLatin_u,chLatin_r,chLatin_c,chLatin_e,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chLatin_s,chNull
};

const XMLCh XMLStrDefs::p[] = 
{
	chLatin_p,chNull
};

const XMLCh XMLStrDefs::c[] = 
{
	chLatin_c,chNull
};

const XMLCh XMLStrDefs::r[] = 
{
	chLatin_r,chNull
};

const XMLCh XMLStrDefs::rows[] =
{
	chLatin_r,chLatin_o,chLatin_w,chLatin_s,chNull
};

const XMLCh XMLStrDefs::columns[] =
{
	chLatin_c,chLatin_o,chLatin_l,chLatin_u,chLatin_m,chLatin_n,chLatin_s,chNull
};

const XMLCh XMLStrDefs::store[] =
{
	chLatin_s,chLatin_t,chLatin_o,chLatin_r,chLatin_e,chNull
};

const XMLCh XMLStrDefs::sampleMethod[] = 
{
	chLatin_s,chLatin_a,chLatin_m,chLatin_p,chLatin_l,chLatin_e,
	chLatin_M,chLatin_e,chLatin_t,chLatin_h,chLatin_o,chLatin_d,chNull
};

const XMLCh XMLStrDefs::withReplacement[] = 
{
	chLatin_w,chLatin_i,chLatin_t,chLatin_h,
	chLatin_R,chLatin_e,chLatin_p,chLatin_l,chLatin_a,chLatin_c,chLatin_e,chLatin_m,chLatin_e,chLatin_n,chLatin_t,chNull
};

const XMLCh XMLStrDefs::withoutReplacement[] = 
{
	chLatin_w,chLatin_i,chLatin_t,chLatin_h,chLatin_o,chLatin_u,chLatin_t,
	chLatin_R,chLatin_e,chLatin_p,chLatin_l,chLatin_a,chLatin_c,chLatin_e,chLatin_m,chLatin_e,chLatin_n,chLatin_t,chNull
};

const XMLCh XMLStrDefs::compositeTask[] = 
{
	chLatin_c,chLatin_o,chLatin_m,chLatin_p,chLatin_o,chLatin_s,chLatin_i,chLatin_t,chLatin_e,
	chLatin_T,chLatin_a,chLatin_s,chLatin_k,chNull
};

const XMLCh XMLStrDefs::insert[] =
{
	chLatin_i,chLatin_n,chLatin_s,chLatin_e,chLatin_r,chLatin_t,chNull
};

const XMLCh XMLStrDefs::insertParams[] =
{
	chLatin_i,chLatin_n,chLatin_s,chLatin_e,chLatin_r,chLatin_t,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chLatin_s,chNull
};

const XMLCh XMLStrDefs::inColumn[] =
{
	chLatin_i,chLatin_n,
	chLatin_C,chLatin_o,chLatin_l,chLatin_u,chLatin_m,chLatin_n,chNull
};

const XMLCh XMLStrDefs::inRow[] =
{
	chLatin_i,chLatin_n,
	chLatin_R,chLatin_o,chLatin_w,chNull
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
//executionSection
////////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::execution[] = 
{
	chLatin_e,chLatin_x,chLatin_e,chLatin_c,chLatin_u,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::executionSection[] = 
{
	chLatin_e,chLatin_x,chLatin_e,chLatin_c,chLatin_u,chLatin_t,chLatin_i,chLatin_o,chLatin_n,
	chLatin_S,chLatin_e,chLatin_c,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::networks[] = 
{
	chLatin_n,chLatin_e,chLatin_t,chLatin_w,chLatin_o,chLatin_r,chLatin_k,chLatin_s,chNull
};

const XMLCh XMLStrDefs::runs[] =
{
	chLatin_r,chLatin_u,chLatin_n,chLatin_s,chNull
};

const XMLCh XMLStrDefs::loop[] = 
{
	chLatin_l,chLatin_o,chLatin_o,chLatin_p,chNull
};

const XMLCh XMLStrDefs::targets[] = 
{
	chLatin_t,chLatin_a,chLatin_r,chLatin_g,chLatin_e,chLatin_t,chLatin_s,chNull
};

const XMLCh XMLStrDefs::numValues[] =
{
	chLatin_n,chLatin_u,chLatin_m,
	chLatin_V,chLatin_a,chLatin_l,chLatin_u,chLatin_e,chLatin_s,chNull
};

const XMLCh XMLStrDefs::sequence[] = 
{
	chLatin_s,chLatin_e,chLatin_q,chLatin_u,chLatin_e,chLatin_n,chLatin_c,chLatin_e,chNull
};

const XMLCh XMLStrDefs::repeat[] = 
{
	chLatin_r,chLatin_e,chLatin_p,chLatin_e,chLatin_a,chLatin_t,chNull
};

const XMLCh XMLStrDefs::part[] = 
{
	chLatin_p,chLatin_a,chLatin_r,chLatin_t,chNull
};

const XMLCh XMLStrDefs::phase[] =
{
	chLatin_p,chLatin_h,chLatin_a,chLatin_s,chLatin_e,chNull
};

const XMLCh XMLStrDefs::learnDuringReset[] =
{
	chLatin_l,chLatin_e,chLatin_a,chLatin_r,chLatin_n,
	chLatin_D,chLatin_u,chLatin_r,chLatin_i,chLatin_n,chLatin_g,
	chLatin_R,chLatin_e,chLatin_s,chLatin_e,chLatin_t,chNull
};

const XMLCh XMLStrDefs::iterations[] = 
{
	chLatin_i,chLatin_t,chLatin_e,chLatin_r,chLatin_a,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chLatin_s,chNull
};

const XMLCh XMLStrDefs::test[] =
{
	chLatin_t,chLatin_e,chLatin_s,chLatin_t,chNull
};

const XMLCh XMLStrDefs::tasks[] =
{
	chLatin_t,chLatin_a,chLatin_s,chLatin_k,chLatin_s,chNull
};

const XMLCh XMLStrDefs::random[] =
{
	chLatin_r,chLatin_a,chLatin_n,chLatin_d,chLatin_o,chLatin_m,chNull
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//defaultSection
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::typeDefaults[] =
{
	chLatin_t,chLatin_y,chLatin_p,chLatin_e,
	chLatin_D,chLatin_e,chLatin_f,chLatin_a,chLatin_u,chLatin_l,chLatin_t,chLatin_s,chNull
};

const XMLCh XMLStrDefs::xmldefault[] =
{
	chLatin_d,chLatin_e,chLatin_f,chLatin_a,chLatin_u,chLatin_l,chLatin_t,chNull
};

const XMLCh XMLStrDefs::types[] =
{
	chLatin_t,chLatin_y,chLatin_p,chLatin_e,chLatin_s,chNull
};

const XMLCh XMLStrDefs::numSites[] =
{
	chLatin_n,chLatin_u,chLatin_m,
	chLatin_S,chLatin_i,chLatin_t,chLatin_e,chLatin_s,chNull
};

const XMLCh XMLStrDefs::targetDefaults[] =
{
	chLatin_t,chLatin_a,chLatin_r,chLatin_g,chLatin_e,chLatin_t,
	chLatin_D,chLatin_e,chLatin_f,chLatin_a,chLatin_u,chLatin_l,chLatin_t,chLatin_s,chNull
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//eventSection
////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::event[] =
{
	chLatin_e,chLatin_v,chLatin_e,chLatin_n,chLatin_t,chNull
};

const XMLCh XMLStrDefs::parts[] = 
{
	chLatin_p,chLatin_a,chLatin_r,chLatin_t,chLatin_s,chNull
};

const XMLCh XMLStrDefs::eventTime[] =
{
	chLatin_e,chLatin_v,chLatin_e,chLatin_n,chLatin_t,
	chLatin_T,chLatin_i,chLatin_m,chLatin_e,chNull
};

const XMLCh XMLStrDefs::condition[] =
{
	chLatin_c,chLatin_o,chLatin_n,chLatin_d,chLatin_i,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::variable[] = 
{
	chLatin_v,chLatin_a,chLatin_r,chLatin_i,chLatin_a,chLatin_b,chLatin_l,chLatin_e,chNull
};

const XMLCh XMLStrDefs::record[] =
{
	chLatin_r,chLatin_e,chLatin_c,chLatin_o,chLatin_r,chLatin_d,chNull
};

const XMLCh XMLStrDefs::precision[] =
{
	chLatin_p,chLatin_r,chLatin_e,chLatin_c,chLatin_i,chLatin_s,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::report[] =
{
	chLatin_r,chLatin_e,chLatin_p,chLatin_o,chLatin_r,chLatin_t,chNull
};

const XMLCh XMLStrDefs::modify[] =
{
	chLatin_m,chLatin_o,chLatin_d,chLatin_i,chLatin_f,chLatin_y,chNull
};

const XMLCh XMLStrDefs::operation[] = 
{
	chLatin_o,chLatin_p,chLatin_e,chLatin_r,chLatin_a,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::nodeIndices[] = 
{
	chLatin_n,chLatin_o,chLatin_d,chLatin_e,
	chLatin_I,chLatin_n,chLatin_d,chLatin_i,chLatin_c,chLatin_e,chLatin_s,chNull
};

const XMLCh XMLStrDefs::modifyParam[] =
{
	chLatin_m,chLatin_o,chLatin_d,chLatin_i,chLatin_f,chLatin_y,
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chNull
};

const XMLCh XMLStrDefs::paramName[] =
{
	chLatin_p,chLatin_a,chLatin_r,chLatin_a,chLatin_m,
	chLatin_N,chLatin_a,chLatin_m,chLatin_e,chNull
};

const XMLCh XMLStrDefs::xmlstdout[] =
{
	chLatin_s,chLatin_t,chLatin_d,chLatin_o,chLatin_u,chLatin_t,chNull
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//from languageDefinition
////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::languageDefinition[] =
{
	chLatin_l,chLatin_a,chLatin_n,chLatin_g,chLatin_u,chLatin_a,chLatin_g,chLatin_e,
	chLatin_D,chLatin_e,chLatin_f,chLatin_i,chLatin_n,chLatin_i,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::codeFile[] =
{
	chLatin_c,chLatin_o,chLatin_d,chLatin_e,
	chLatin_F,chLatin_i,chLatin_l,chLatin_e,chNull
};

const XMLCh XMLStrDefs::nr[] =
{
	chLatin_n,chLatin_r,chNull
};

const XMLCh XMLStrDefs::Section[] =
{
	chLatin_S,chLatin_e,chLatin_c,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::use[] =
{
	chLatin_u,chLatin_s,chLatin_e,chNull
};

const XMLCh XMLStrDefs::state[] =
{
	chLatin_s,chLatin_t,chLatin_a,chLatin_t,chLatin_e,chNull
};

const XMLCh XMLStrDefs::optional[] = 
{
	chLatin_o,chLatin_p,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chLatin_a,chLatin_l,chNull
};

const XMLCh XMLStrDefs::required[] = 
{
	chLatin_r,chLatin_e,chLatin_q,chLatin_u,chLatin_i,chLatin_r,chLatin_e,chLatin_d,chNull
};

const XMLCh XMLStrDefs::prohibited[] =
{
	chLatin_p,chLatin_r,chLatin_o,chLatin_h,chLatin_i,chLatin_b,chLatin_i,chLatin_t,chLatin_e,chLatin_d,chNull
};

const XMLCh XMLStrDefs::ignored[] = 
{
	chLatin_i,chLatin_g,chLatin_n,chLatin_o,chLatin_r,chLatin_e,chLatin_d,chNull
};

const XMLCh XMLStrDefs::annotation[] = 
{
	chLatin_a,chLatin_n,chLatin_n,chLatin_o,chLatin_t,chLatin_a,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::documentation[] =
{
	chLatin_d,chLatin_o,chLatin_c,chLatin_u,chLatin_m,chLatin_e,chLatin_n,chLatin_t,chLatin_a,chLatin_t,chLatin_i,chLatin_o,chLatin_n,chNull
};

const XMLCh XMLStrDefs::appinfo[] = 
{
	chLatin_a,chLatin_p,chLatin_p,chLatin_i,chLatin_n,chLatin_f,chLatin_o,chNull
};

const XMLCh XMLStrDefs::source[] = 
{
	chLatin_s,chLatin_o,chLatin_u,chLatin_r,chLatin_c,chLatin_e,chNull
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//from codeGenerator
////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::codeGenerator[] =
{
	chLatin_c,chLatin_o,chLatin_d,chLatin_e,
	chLatin_G,chLatin_e,chLatin_n,chLatin_e,chLatin_r,chLatin_a,chLatin_t,chLatin_o,chLatin_r,chNull
};
	
const XMLCh XMLStrDefs::intro[] = 
{
	chLatin_i,chLatin_n,chLatin_t,chLatin_r,chLatin_o,chNull
};

const XMLCh XMLStrDefs::hFile[] = 
{
	chLatin_h,chLatin_F,chLatin_i,chLatin_l,chLatin_e,chNull
};

const XMLCh XMLStrDefs::cppFile[] = 
{
	chLatin_c,chLatin_p,chLatin_p,chLatin_F,chLatin_i,chLatin_l,chLatin_e,chNull
};

const XMLCh XMLStrDefs::line[] = 
{
	chLatin_l,chLatin_i,chLatin_n,chLatin_e,chNull
};
	
const XMLCh XMLStrDefs::tab[] = 
{
	chLatin_t,chLatin_a,chLatin_b,chNull
};

const XMLCh XMLStrDefs::insertText[] =
{
	chLatin_i,chLatin_n,chLatin_s,chLatin_e,chLatin_r,chLatin_t,
	chLatin_T,chLatin_e,chLatin_x,chLatin_t,chNull
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//from results
////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::results[] =
{
	chLatin_r,chLatin_e,chLatin_s,chLatin_u,chLatin_l,chLatin_t,chLatin_s,chNull
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//from experimentList
////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::experimentList[] =
{
	chLatin_e,chLatin_x,chLatin_p,chLatin_e,chLatin_r,chLatin_i,chLatin_m,chLatin_e,chLatin_n,chLatin_t,
	chLatin_L,chLatin_i,chLatin_s,chLatin_t,chNull
};

const XMLCh XMLStrDefs::file[] =
{
	chLatin_f,chLatin_i,chLatin_l,chLatin_e,chNull
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//from patternGenerator
////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::patternGenerator[] =
{
	chLatin_p,chLatin_a,chLatin_t,chLatin_t,chLatin_e,chLatin_r,chLatin_n,
	chLatin_G,chLatin_e,chLatin_n,chLatin_e,chLatin_r,chLatin_a,chLatin_t,chLatin_o,chLatin_r,chNull
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//from randTest
////////////////////////////////////////////////////////////////////////////////////////////////////
const XMLCh XMLStrDefs::randTest[] =
{
	chLatin_r,chLatin_a,chLatin_n,chLatin_d,
	chLatin_T,chLatin_e,chLatin_s,chLatin_t,chNull
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//various
////////////////////////////////////////////////////////////////////////////////////////////////////

const XMLCh XMLStrDefs::LS[] = 
{
	chLatin_L,chLatin_S,chNull
};

const XMLCh XMLStrDefs::Params[] = 
{
	chLatin_P,chLatin_a,chLatin_r,chLatin_a,chLatin_m,chLatin_s,chNull
};

} //end namespace CORINET


