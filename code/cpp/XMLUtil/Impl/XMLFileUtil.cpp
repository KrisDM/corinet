/*********************************************************************************************
 * Name      :  XMLFileUtil.cpp
 *
 * Purpose   :  File utility functions.
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

#include <Util/Util.h>
#include <XMLUtil/XMLFileUtil.h>
#include <XMLUtil/XMLStringUtil.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <iostream>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE

void XMLFileUtil::GetFullPath(XMLCh* const fullPath,const XMLCh* const fileName)
{
	if ((*fileName != chForwardSlash) && (*fileName != chBackSlash) &&
		(*fileName != chPeriod) && XMLPlatformUtils::isRelative(fileName)) {
		XMLCh* curDir = XMLPlatformUtils::getCurrentDirectory();
		XMLStringUtil::Copy(fullPath,curDir);
		XMLCh tmp[2] = {chForwardSlash,chNull};
		if (XMLStringUtil::Contains(curDir,chBackSlash)) //windows style path
			tmp[0] = chBackSlash;
		XMLStringUtil::Append(fullPath,tmp);
		XMLStringUtil::Append(fullPath,fileName);
		XMLStringUtil::Release(curDir);
	}
	else if (XMLPlatformUtils::isRelative(fileName)) {
		XMLCh* tmpRoot = XMLStringUtil::Str2XML(GetRoot());
		XMLCh* tmpBuf = XMLPlatformUtils::weavePaths(tmpRoot,fileName);
		XMLStringUtil::Copy(fullPath,tmpBuf);
		XMLStringUtil::Release(tmpBuf);
		XMLStringUtil::Release(tmpRoot);
	}
	else {
		XMLCh* tmpBuf = XMLStringUtil::Replicate(fileName);
		XMLPlatformUtils::removeDotSlash(tmpBuf);
		XMLPlatformUtils::removeDotDotSlash(tmpBuf);
		XMLStringUtil::Copy(fullPath,tmpBuf);
		XMLStringUtil::Release(tmpBuf);
	}
}

void XMLFileUtil::GetFullPath(XMLCh* const fullPath,const std::string& fileName)
{
	XMLCh* tmpBuf = XMLStringUtil::Str2XML(fileName.c_str());
	GetFullPath(fullPath,tmpBuf);
	XMLStringUtil::Release(tmpBuf);
}

std::string XMLFileUtil::GetFullPath(const XMLCh* const fileName)
{
	std::string fullpathstr;
	if ((*fileName != chForwardSlash) && (*fileName != chBackSlash) &&
		(*fileName != chPeriod) && XMLPlatformUtils::isRelative(fileName)) {
		XMLCh* curDir = XMLPlatformUtils::getCurrentDirectory();
		fullpathstr = XMLStringUtil::XML2Str(curDir);
		if (fullpathstr.find('\\') != fullpathstr.npos) {
			fullpathstr += '\\';
		}
		else
			fullpathstr += '/';
		fullpathstr += XMLStringUtil::XML2Str(fileName);
		XMLStringUtil::Release(curDir);
	}
	else if (XMLPlatformUtils::isRelative(fileName)) {
		XMLCh* tmpRoot = XMLStringUtil::Str2XML(GetRoot());
		XMLCh* tmpBuf = XMLPlatformUtils::weavePaths(tmpRoot,fileName);
		fullpathstr = XMLStringUtil::XML2Str(tmpBuf);
		XMLStringUtil::Release(tmpBuf);
		XMLStringUtil::Release(tmpRoot);
	}
	else {
		XMLCh* tmpBuf = XMLStringUtil::Replicate(fileName);
		XMLPlatformUtils::removeDotSlash(tmpBuf);
		XMLPlatformUtils::removeDotDotSlash(tmpBuf);
		fullpathstr = XMLStringUtil::XML2Str(tmpBuf);
		XMLStringUtil::Release(tmpBuf);
	}
	return fullpathstr;
}

void XMLFileUtil::WriteToTarget(char* str,size_t numchars,XERCES_CPP_NAMESPACE::XMLFormatTarget* target)
{
	XMLFormatter format(XMLUni::fgUTF8EncodingString,XMLUni::fgVersion1_0,target);
	target->writeChars(reinterpret_cast<XMLByte*>(str),numchars,&format);
}

} //end namespace CORINET

