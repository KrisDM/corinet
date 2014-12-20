/*********************************************************************************************
 * Name      :  XMLStringUtil.cpp
 *
 * Purpose   :  Utility functions for maninpulation of XMLCh strings. Wrapping useful functions
 *				of the xerces-c XMLString class and providing a few extra.
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

#include <XMLUtil/XMLStringUtil.h>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/BaseRefVectorOf.hpp>
#include <xercesc/util/Janitor.hpp>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

int XMLStringUtil::XML2Int(const XMLCh* const str)
{
	return XMLString::parseInt(str);
}

double XMLStringUtil::XML2Dbl(const XMLCh* const str)
{
	char* strch = XMLString::transcode(str);
	double val = atof(strch);
	XMLString::release(&strch);
	return val;
}

std::string XMLStringUtil::XML2Str(const XMLCh* const strXCh)
{
	char* strch = XMLString::transcode(strXCh);
	std::string str(strch);
	XMLString::release(&strch);
	return str;
}

XMLCh* XMLStringUtil::Str2XML(const std::string& str)
{
	XMLCh* strXCh = XMLString::transcode(str.c_str());
	return strXCh;
}

void XMLStringUtil::Str2XML(const std::string& str,XMLCh* const dest,size_t maxSize)
{
	XMLString::transcode(str.c_str(),dest,maxSize);
}

void XMLStringUtil::Int2XML(int num,XMLCh* const dest,size_t maxSize)
{
	XMLString::binToText(num,dest,maxSize,10);
}

std::vector<XMLCh*> XMLStringUtil::Tokenise(const XMLCh* const str)
{
	BaseRefVectorOf<XMLCh>* parts = XMLString::tokenizeString(str);
	std::vector<XMLCh*> partsVec(parts->size());
	for(size_t i=0,is=parts->size();i<is;++i) {
		partsVec[i] = parts->elementAt(i);
	}
	return partsVec;
}

XMLCh* XMLStringUtil::Replicate(const XMLCh* const str)
{
	return XMLString::replicate(str);
}

void XMLStringUtil::Copy(XMLCh* const target,const XMLCh* const src)
{
	XMLString::copyString(target,src);
}
	
void XMLStringUtil::Append(XMLCh* const target,const XMLCh* const src)
{
	XMLString::catString(target,src);
}
	
void XMLStringUtil::AppendWSpace(XMLCh* const target,const XMLCh* const src)
{
	XMLCh XMLSpace[2] = {chSpace,chNull};
	XMLString::catString(target,XMLSpace);
	XMLString::catString(target,src);
}

bool XMLStringUtil::Equals(const XMLCh* const str1,const XMLCh* const str2)
{
	return XMLString::equals(str1,str2);
}

bool XMLStringUtil::EndsWith(const XMLCh* const str1,const XMLCh* const str2)
{
	return XMLString::endsWith(str1,str2);
}

bool XMLStringUtil::Contains(const XMLCh* const str1,XMLCh ch)
{
	bool contains = false;
	if (XMLString::indexOf(str1,ch) != -1) {
		contains = true;
	}
	return contains;
}

void XMLStringUtil::FixURI(XMLCh* const str)
{
	XMLCh tempBuf[512];
	XMLString::copyString(tempBuf,str);
	XMLStringUtil::Space2Hex(tempBuf);
	XMLString::fixURI(tempBuf,str);
}

void XMLStringUtil::Space2Hex(XMLCh* const str)
{
	XMLCh hexVal[4] = {chPercent,chDigit_2,chDigit_0,chNull};
	XMLCh tempBuf[512];
	XMLString::copyString(tempBuf,str);
	BaseRefVectorOf<XMLCh>*  parts = XMLString::tokenizeString(tempBuf);
	Janitor<BaseRefVectorOf<XMLCh> > jan(parts);
	if (parts->size()) {
		XMLString::copyString(str,parts->elementAt(0));
		for(size_t i=1,is=parts->size();i<is;++i) {
			XMLString::catString(str,hexVal);
			XMLString::catString(str,parts->elementAt(i));
		}
	}
}

void XMLStringUtil::CollapseWS(XMLCh* const str)
{
	XMLString::collapseWS(str);
}

void XMLStringUtil::Release(XMLCh* buff)
{
	XMLString::release(&buff);
}

void XMLStringUtil::Release(std::vector<XMLCh*>& vec)
{
	for(size_t i=0,is=vec.size();i<is;++i) {
		XMLString::release(&(vec[i]));
	}
	vec.clear();
}

} //end namespace CORINET


