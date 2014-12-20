/*********************************************************************************************
 * Name      :  DOMDefinitionImpl.cpp
 *
 * Purpose   :  Implementation class handling <languageDefinition> DOM.
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


#include "DOMDefinitionImpl.h"
#include <DOMSetup/Misc/DOMHelperFunctions.h>
#include <XMLUtil/XMLFileUtil.h>
#include <fstream>
#include <istream>
#include <cstdio>
#include <ctime>
#include <cctype>

namespace CORINET {
	XERCES_CPP_NAMESPACE_USE
	
CDOMDefinitionImpl::CDOMDefinitionImpl()
{

}

CDOMDefinitionImpl::~CDOMDefinitionImpl()
{
	ReleaseAll();
}

void CDOMDefinitionImpl::ReleaseAll()
{

}

void CDOMDefinitionImpl::Handle(DOMDocument* defDoc,const DOMDocument* codeDoc,DOMErrorHandler* eHandler,bool create)
{
	//check that param names within one element are not defined twice
	CheckParamNames(defDoc,XMLStrDefs::randGen,eHandler);
	CheckParamNames(defDoc,XMLStrDefs::attenuation,eHandler);
	CheckParamNames(defDoc,XMLStrDefs::noiseFunction,eHandler);
	CheckParamNames(defDoc,XMLStrDefs::initialisation,eHandler);
	CheckParamNames(defDoc,XMLStrDefs::normalisation,eHandler);
	CheckParamNames(defDoc,XMLStrDefs::outputFunction,eHandler);
	CheckParamNames(defDoc,XMLStrDefs::integrationSite,eHandler);
	CheckParamNames(defDoc,XMLStrDefs::block,eHandler);
	CheckParamNames(defDoc,XMLStrDefs::network,eHandler);
	CheckParamNames(defDoc,XMLStrDefs::dataSource,eHandler);
	CheckParamNames(defDoc,XMLStrDefs::task,eHandler);
	CheckParamNames(defDoc,XMLStrDefs::compositeTask,eHandler);
	//check the <part> elements
	const DOMNodeList* pDOMpartList = GetElementList(defDoc,XMLStrDefs::part);
	for(XMLSize_t i=0,is=pDOMpartList->getLength();i<is;++i) {
		const DOMElement* pDOMpart = GetElement(pDOMpartList,i);
		const XMLCh* partTypeXCh = pDOMpart->getAttribute(XMLStrDefs::type);
		if (!XMLStringUtil::Equals(XMLStrDefs::network,defDoc->getElementById(partTypeXCh)->getTagName())) {
			CErrorHandler::PrepareError("No corresponding <network> element specified.",pDOMpart,eHandler);
		}
		for(XMLSize_t j=i+1;j<is;++j) {
			if (XMLStringUtil::Equals(partTypeXCh,GetElement(pDOMpartList,j)->getAttribute(XMLStrDefs::type))) {
				CErrorHandler::PrepareError("Same type defined multiple times in <languageDefinition>.",pDOMpart,eHandler);
			}
		}
		//check the two parameters that should be present
		const DOMNodeList* pDOMparamList = GetElementList(pDOMpart,XMLStrDefs::param);
		const XMLSize_t pl = pDOMparamList->getLength();
		if (pl > 2) {
			CErrorHandler::PrepareError("Too many parameters specified.",pDOMpart,eHandler);
		}
		else if (pl < 2) {
			CErrorHandler::PrepareError("Not enough parameters specified.",pDOMpart,eHandler);
		}
		else {
			const DOMElement* pDOMtimePerPattern = GetElement(pDOMparamList,0);
			std::string param1Name = XMLStringUtil::XML2Str(pDOMtimePerPattern->getAttribute(XMLStrDefs::name));
			if (param1Name != "timePerPattern") {
				CErrorHandler::PrepareError("Wrong parameter name \"" + param1Name + "\".",pDOMpart,eHandler);
			}
			const DOMElement* pDOMzeroTime = GetElement(pDOMparamList,1);
			std::string param2Name = XMLStringUtil::XML2Str(pDOMzeroTime->getAttribute(XMLStrDefs::name));
			if (param2Name != "zeroTime") {
				CErrorHandler::PrepareError("Wrong parameter name \"" + param2Name + "\".",pDOMpart,eHandler);
			}
		}
	}
	//check if any networks are unaccounted for in parts definition
	const DOMNodeList* pDOMnetList = GetElementList(defDoc,XMLStrDefs::network);
	XMLSize_t nl = pDOMnetList->getLength();
	XMLSize_t pl = pDOMpartList->getLength();
	if (nl > pl) {
		for(XMLSize_t n=0;n<nl;++n) {
			const DOMElement* pDOMnet = GetElement(pDOMnetList,n);
			const XMLCh* netTypeXCh = pDOMnet->getAttribute(XMLStrDefs::type);
			XMLSize_t p;
			for(p=0;p<pl;++p) {
				if (XMLStringUtil::Equals(netTypeXCh,GetElement(pDOMpartList,p)->getAttribute(XMLStrDefs::type))) { 
					break;
				}
			}
			if (p == pl) {
				CErrorHandler::PrepareError("No corresponding <part> element specified.",pDOMnet,eHandler);
			}
		}
	}

	if (create) {//generate c++ code
		//check the location
		if (!defDoc->getDocumentElement()->hasAttribute(XMLStrDefs::location)) {
			CErrorHandler::PrepareError("Attribute \"location\" missing; specify path to existing directory.",0,eHandler);
		}
		const XMLCh* XMLChlocation = defDoc->getDocumentElement()->getAttribute(XMLStrDefs::location);
		if (!(*XMLChlocation)) {
			CErrorHandler::PrepareError("Attribute \"location\" empty; specify path to existing directory.",0,eHandler);
		}
		
		std::string fullLocation = XMLFileUtil::GetFullPath(XMLChlocation);
		if (fullLocation[fullLocation.size()-1] != '/') {
			fullLocation.append(1,'/');
		}

		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::randGen,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::attenuation,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::noiseFunction,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::initialisation,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::normalisation,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::outputFunction,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::integrationSite,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::block,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::network,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::dataSource,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::insert,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::task,fullLocation);
		HandleType(defDoc,codeDoc,eHandler,XMLStrDefs::compositeTask,fullLocation);
	}
}

SEngineMaker* CDOMDefinitionImpl::GetEngineMaker()
{
	return 0;
}

void CDOMDefinitionImpl::CheckParamNames(const DOMDocument* defDoc,const XMLCh* elName,DOMErrorHandler* eHandler)
{
	const DOMNodeList* pDOMelemList = GetElementList(defDoc,elName);
	for(XMLSize_t i=0,is=pDOMelemList->getLength();i<is;++i) {
		const DOMElement* pDOMelem = GetElement(pDOMelemList,i);
		const DOMNodeList* pDOMparamList = GetElementList(pDOMelem,XMLStrDefs::param);
		for(XMLSize_t j=0,js=pDOMparamList->getLength();j<js;++j) {
			const XMLCh* paramName = GetElement(pDOMparamList,j)->getAttribute(XMLStrDefs::name);
			for(XMLSize_t k=j+1;k<js;++k) {
				if (XMLStringUtil::Equals(paramName,GetElement(pDOMparamList,k)->getAttribute(XMLStrDefs::name))) {
					CErrorHandler::PrepareError("Param name \"" + XMLStringUtil::XML2Str(paramName) + "\" used twice in element.",pDOMelem,eHandler);
				}
			}
		}
	}
}

void CDOMDefinitionImpl::HandleType(const DOMDocument* defDoc,const DOMDocument* codeDoc,DOMErrorHandler* eHandler,
									const XMLCh* elName,const std::string& fullLocation)
{
	const DOMNodeList* pDOMelemList = GetElementList(defDoc,elName);
	for(XMLSize_t i1=0,is1=pDOMelemList->getLength();i1<is1;++i1) {
		const DOMElement* pDOMelem = GetElement(pDOMelemList,i1);
		const DOMNodeList* pDOMparamList = GetElementList(pDOMelem,XMLStrDefs::param);
		XMLSize_t pls = pDOMparamList->getLength();
		const XMLCh* typeNameXCh = pDOMelem->getAttribute(XMLStrDefs::type);
		std::string typeNameStr = XMLStringUtil::XML2Str(typeNameXCh);
		std::string typeNameUpper = "";
		for(size_t t1=0,ts1=typeNameStr.size();t1<ts1;++t1) {
			typeNameUpper.append(1,static_cast<char>(toupper(typeNameStr[t1])));
		}
		typeNameStr[0] = static_cast<char>(toupper(typeNameStr[0]));
		//construct the filenames
		std::string hFileNameStr;
		std::string cppFileNameStr;
		if (XMLStringUtil::Equals(elName,XMLStrDefs::randGen)) {
			hFileNameStr = "RandDouble";
		}
		else {
			hFileNameStr = XMLStringUtil::XML2Str(elName);
			hFileNameStr[0] = static_cast<char>(toupper(hFileNameStr[0]));
		}
		cppFileNameStr = hFileNameStr + typeNameStr + ".cpp";
		hFileNameStr += (typeNameStr + ".h");
		
		//write the h file
		std::string tempStr1 = fullLocation + hFileNameStr; 
		//check if file already exists
		std::ifstream instr1(tempStr1.c_str(),std::ios_base::in);
		if (instr1) {
			CErrorHandler::NonFatalMessage("File " + tempStr1 + " already exists. Skipping...",eHandler);
			instr1.close();
		}
		else {
			instr1.close();
			std::ofstream ostr1(tempStr1.c_str(),std::ios_base::out);
			//now check if file can be created
			if (!ostr1) {
				CErrorHandler::PrepareError("File " + tempStr1 + " could not be created.",0,eHandler);
			}
			WriteIntro(ostr1,codeDoc,hFileNameStr);
			const DOMElement* pDOMmainType = GetElement(codeDoc,elName,0);
			const DOMNodeList* pDOMlineList = GetElementList(GetElement(pDOMmainType,XMLStrDefs::hFile,0),XMLStrDefs::line);
			for(XMLSize_t k1=0,ks1=pDOMlineList->getLength();k1<ks1;++k1) {
				const DOMElement* pDOMline = GetElement(pDOMlineList,k1);
				const DOMNodeList* pDOMchildren = pDOMline->getChildNodes();
				for(XMLSize_t j1=0,js1=pDOMchildren->getLength();j1<js1;++j1) {
					DOMNode* pDOMchild = pDOMchildren->item(j1);
					if (pDOMchild->getNodeType() == DOMNode::TEXT_NODE) {
						ostr1 << XMLStringUtil::XML2Str(pDOMchild->getNodeValue());
					}
					else if (pDOMchild->getNodeType() == DOMNode::ELEMENT_NODE) {
						const DOMElement* pDOMchildElem = static_cast<DOMElement*>(pDOMchild);
						const XMLCh* elemType = pDOMchildElem->getTagName();
						if (XMLStringUtil::Equals(elemType,XMLStrDefs::tab)) {
							ostr1 << '\t';
						}
						else if (XMLStringUtil::Equals(elemType,XMLStrDefs::insertText)) {
							std::string typestr = XMLStringUtil::XML2Str(pDOMchildElem->getAttribute(XMLStrDefs::type));
							if (typestr == "typeNameUpper") {
								ostr1 << typeNameUpper;
							}
							else if (typestr == "typeName") {
								ostr1 << typeNameStr;
							}
							else if (typestr == "params") {
								if (pls) {
									std::string paramStr = "double ";
									for(XMLSize_t p1=0;p1<pls;++p1) {
										const DOMElement* pDOMparam = GetElement(pDOMparamList,p1);
										std::string paramname = XMLStringUtil::XML2Str(pDOMparam->getAttribute(XMLStrDefs::name));
										paramStr += "m";
										paramStr.append(1,static_cast<char>(toupper(paramname[0])));
										paramStr += paramname.substr(1);
										paramStr += ",";
									}
									paramStr[paramStr.size()-1] = ';';
									ostr1 << paramStr;
								}
							}
						}
					}
				}
				ostr1 << '\n';
			}
			ostr1.close();
		}

		//write the cpp file
		std::string tempStr2 = fullLocation + cppFileNameStr; 
		//check if file already exists
		std::ifstream instr2(tempStr2.c_str(),std::ios_base::in);
		if (instr2) {
			CErrorHandler::NonFatalMessage("File " + tempStr2 + " already exists. Skipping...",eHandler);
			instr2.close();
		}
		else {
			instr2.close();
			std::ofstream ostr2(tempStr2.c_str(),std::ios_base::out);
			//now check if file can be created
			if (!ostr2) {
				CErrorHandler::PrepareError("File " + tempStr2 + " could not be created.",0,eHandler);
			}
			WriteIntro(ostr2,codeDoc,cppFileNameStr);
			const DOMElement* pDOMmainType = GetElement(codeDoc,elName,0);
			const DOMNodeList* pDOMlineList = GetElementList(GetElement(pDOMmainType,XMLStrDefs::cppFile,0),XMLStrDefs::line);
			for(XMLSize_t k1=0,ks1=pDOMlineList->getLength();k1<ks1;++k1) {
				const DOMElement* pDOMline = GetElement(pDOMlineList,k1);
				const DOMNodeList* pDOMchildren = pDOMline->getChildNodes();
				for(XMLSize_t j1=0,js1=pDOMchildren->getLength();j1<js1;++j1) {
					DOMNode* pDOMchild = pDOMchildren->item(j1);
					if (pDOMchild->getNodeType() == DOMNode::TEXT_NODE) {
						ostr2 << XMLStringUtil::XML2Str(pDOMchild->getNodeValue());
					}
					else if (pDOMchild->getNodeType() == DOMNode::ELEMENT_NODE) {
						const DOMElement* pDOMchildElem = static_cast<DOMElement*>(pDOMchild);
						const XMLCh* elemType = pDOMchildElem->getTagName();
						if (XMLStringUtil::Equals(elemType,XMLStrDefs::tab)) {
							ostr2 << '\t';
						}
						else if (XMLStringUtil::Equals(elemType,XMLStrDefs::insertText)) {
							std::string typestr = XMLStringUtil::XML2Str(pDOMchildElem->getAttribute(XMLStrDefs::type));
							if (typestr == "typeNameUpper") {
								ostr2 << typeNameUpper;
							}
							else if (typestr == "typeName") {
								ostr2 << typeNameStr;
							}
							else if (typestr == "key") {
								ostr2 << XMLStringUtil::XML2Str(typeNameXCh);
							}
							else if (typestr == "fileName") {
								ostr2 << hFileNameStr;
							}
							else if (typestr == "params") {
								if (pls) {
									for(XMLSize_t p1=0;p1<pls;++p1) {
										const DOMElement* pDOMparam = GetElement(pDOMparamList,p1);
										std::string paramname = XMLStringUtil::XML2Str(pDOMparam->getAttribute(XMLStrDefs::name));
										ostr2 << "\tm" << static_cast<char>(toupper(paramname[0])) << paramname.substr(1) << " = params[" << p1 <<"];";
										if (p1 < pls-1) {
											ostr2 << "\n";
										}
									}
								}
							}
							else if (typestr == "setParams") {
								if (pls) {
									ostr2 << "\tswitch (p) {\n";
									for(XMLSize_t p1=0;p1<pls;++p1) {
										const DOMElement* pDOMparam = GetElement(pDOMparamList,p1);
										std::string paramname = XMLStringUtil::XML2Str(pDOMparam->getAttribute(XMLStrDefs::name));
										ostr2 << "\tcase " << p1 << ":\n";
										ostr2 << "\t\tm" << static_cast<char>(toupper(paramname[0])) << paramname.substr(1) << " = v;\n";
										ostr2 << "\t\tbreak;\n";
									}
									ostr2 << "\t}";
								}
								else {
									ostr2 << "\t/*you may delete this function here and in .h if there are no parameters*/";
								}
							}
							else if (typestr == "getParams") {
								if (pls) {
									ostr2 << "\tdouble v = 0.0;\n\tswitch (p) {\n";
									for(XMLSize_t p1=0;p1<pls;++p1) {
										const DOMElement* pDOMparam = GetElement(pDOMparamList,p1);
										std::string paramname = XMLStringUtil::XML2Str(pDOMparam->getAttribute(XMLStrDefs::name));
										ostr2 << "\tcase " << p1 << ":\n";
										ostr2 << "\t\tv = m" << static_cast<char>(toupper(paramname[0])) << paramname.substr(1) << ";\n";
										ostr2 << "\t\tbreak;\n";
									}
									ostr2 << "\t}\n\treturn v;";
								}
								else {
									ostr2 << "\t/*you may delete this function here and in .h if there are no parameters*/\n";
									ostr2 << "\treturn 0.0;";
								}
							}
						}
					}
				}
				ostr2 << '\n';
			}
			ostr2.close();
		}
	}
}

void CDOMDefinitionImpl::WriteIntro(std::ostream& ostr,const DOMDocument* codeDoc,const std::string& fileName)
{
	const DOMElement* pDOMintro = GetElement(codeDoc,XMLStrDefs::intro,0);
	const DOMNodeList* pDOMlineList = GetElementList(pDOMintro,XMLStrDefs::line);
	for(XMLSize_t i1=0,is1=pDOMlineList->getLength();i1<is1;++i1) {
		const DOMElement* pDOMline = GetElement(pDOMlineList,i1);
		const DOMNodeList* pDOMchildren = pDOMline->getChildNodes();
		for(XMLSize_t j1=0,js1=pDOMchildren->getLength();j1<js1;++j1) {
			DOMNode* pDOMchild = pDOMchildren->item(j1);
			if (pDOMchild->getNodeType() == DOMNode::TEXT_NODE) {
				ostr << XMLStringUtil::XML2Str(pDOMchild->getNodeValue());
			}
			else if (pDOMchild->getNodeType() == DOMNode::ELEMENT_NODE) {
				const DOMElement* pDOMelem = static_cast<DOMElement*>(pDOMchild);
				const XMLCh* elemType = pDOMelem->getTagName();
				if (XMLStringUtil::Equals(elemType,XMLStrDefs::tab)) {
					ostr << '\t';
				}
				else if (XMLStringUtil::Equals(elemType,XMLStrDefs::insertText)) {
					std::string typestr = XMLStringUtil::XML2Str(pDOMelem->getAttribute(XMLStrDefs::type));
					if (typestr == "fileName") {
						ostr << fileName;
					}
					else if (typestr == "date") {
						time_t creationtime;
						time(&creationtime);
						struct tm* newtime = localtime(&creationtime);
						std::string datestr = asctime(newtime);
						datestr[datestr.size()-1] = ' ';
						ostr << datestr;
					}
				}
			}
		}
		ostr << '\n';
	}
}

} //end namespace CORINET





