/*********************************************************************************************
 * Name      :  DOMTaskImpl.h
 *
 * Purpose   :  Implementation class handling tasks and child elements.
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

#ifndef CORINET_DOMTASKIMPL
#define CORINET_DOMTASKIMPL

#include <DOMSetup/DOMTask.h>

namespace CORINET {
	struct SDataSourceMaker;
	struct SInsertMaker;
	class CDOMDefaults;
	class CDOMCommon;

class CDOMTaskImpl : public CDOMTask {
	typedef std::map<const DOMElement*,std::vector<const std::valarray<double>*>*> LPatternSets;
	typedef std::map<const DOMElement*,SDataSourceMaker*> LDataMakers;
	typedef std::map<const DOMElement*,SInsertMaker*> LInsertMakers;
	typedef std::map<const DOMElement*,STaskMaker*> LTaskMakers;
	LPatternSets mPatternSets;
	LDataMakers mDataMakers;
	LInsertMakers mInsertMakers;
	LTaskMakers mTaskMakers;
	CDOMDefaults* pDefaultsHandler;
	CDOMCommon* pCommonHandler;
public:
	CDOMTaskImpl();
	virtual ~CDOMTaskImpl();

	//initialise functions
	void SetDefaultsHandler(CDOMDefaults*);
	void SetCommonHandler(CDOMCommon*);


	void Handle(const XERCES_CPP_NAMESPACE::DOMDocument* setupDoc,const XERCES_CPP_NAMESPACE::DOMDocument* valDoc,
		XERCES_CPP_NAMESPACE::DOMErrorHandler* eHandler,bool create);

	//access functions
	STaskMaker* GetTaskMaker(const XERCES_CPP_NAMESPACE::DOMElement*);
	SMaker* GetMaker(const XERCES_CPP_NAMESPACE::DOMElement*);

	//cleanup
	void ReleaseAll();
};

} //end namespace CORINET

#endif //CORINET_DOMTASKIMPL

