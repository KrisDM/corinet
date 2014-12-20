/*********************************************************************************************
 * Name      :  Factory.h
 *
 * Purpose   :  Template classes that can be used as factories for all objects in the project.
 *				 
 *
 * Notes	 :	Concrete classes for each abstract class type need to be registered
 *				with a CFactoryManager class for that abstract type by initialising the
 *				static bool bRegistered variable using the string literal for that type from the XML 
 *				language definition. At the end of this file, macros for an easier initialisation
 *				of the static variables are provided. GET_REGISTER explicitly
 *				instantiates the GetRegister function of CFactoryManager.
 *				REGISTER_CLASS_1 and REGISTER_CLASS_2 provide the registration code.
 *				Use: GET_REGISTER(BASE) and REGISTER_CLASS_X(BASE,CONCRETE,ID)
 *				Use X=1 for classes from the Common, Model and Task parts,
 *				use X=2 for classes from the Event and Engine parts.
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

#include <Platform/Platform.h>

#ifndef CORINET_FACTORY
#define CORINET_FACTORY

#include <map>
#include <string>

namespace CORINET {

template<typename BaseType>
class CBaseFactory {
public:
	virtual ~CBaseFactory() {}
	virtual BaseType* CreateInstance(size_t*,double*) =0;
};

template<typename BaseType>
class CFactoryManager {
private:
	typedef std::map<const std::string,CBaseFactory<BaseType>*> LFactoryRegister;
	static LFactoryRegister* GetRegister();
public:
	CFactoryManager() {}
	~CFactoryManager() {}
	static bool RegisterFactory(const std::string& key,CBaseFactory<BaseType>* factory) {
		typename LFactoryRegister::value_type vt(key,factory);
		GetRegister()->insert(vt);
		return true;
	}
	static BaseType* CreateInstance(const std::string& key,size_t* s =0,double* p =0) {
		typename LFactoryRegister::const_iterator it = GetRegister()->find(key);
		if (it != GetRegister()->end()) {
			return GetRegister()->operator[](key)->CreateInstance(s,p);
		}
		return 0;
	}

};

template<typename BaseType,typename ConcreteType>
class CConcreteFactory1 : public CBaseFactory<BaseType> {//CreateInstance takes size and parameter arguments
public:
	CConcreteFactory1() {}
	virtual ~CConcreteFactory1() {}
	BaseType* CreateInstance(size_t* s,double* p) {return new ConcreteType(s,p);}
	static CConcreteFactory1<BaseType,ConcreteType> mFactory;
	static bool bRegistered;
};

template<typename BaseType,typename ConcreteType>
class CConcreteFactory2 : public CBaseFactory<BaseType> {//CreateInstance takes no arguments
public:
	CConcreteFactory2() {}
	virtual ~CConcreteFactory2() {}
	BaseType* CreateInstance(size_t*,double*) {return new ConcreteType;}
	static CConcreteFactory2<BaseType,ConcreteType> mFactory;
	static bool bRegistered;
};

} //end namespace CORINET

/////////////////////////////////////////////////////////////////////////////////////////////////
//These macros declare the necessary static members for registration of concrete classes with
//the factory manager for the abstract base class. 
/////////////////////////////////////////////////////////////////////////////////////////////////

#define GET_REGISTER(BASE) template<> CFactoryManager<BASE>::LFactoryRegister* CFactoryManager<BASE>::GetRegister()\
{\
	static LFactoryRegister mRegister;\
	return &mRegister;\
}\

#define REGISTER_CLASS_1(BASE,CONCRETE,ID) template<> CConcreteFactory1<BASE,CONCRETE> CConcreteFactory1<BASE,CONCRETE>::mFactory = CConcreteFactory1<BASE,CONCRETE>();\
	template<> bool CConcreteFactory1<BASE,CONCRETE>::bRegistered = CFactoryManager<BASE>::RegisterFactory(#ID,&CConcreteFactory1<BASE,CONCRETE>::mFactory);\

#define REGISTER_CLASS_2(BASE,CONCRETE,ID) template<> CConcreteFactory2<BASE,CONCRETE> CConcreteFactory2<BASE,CONCRETE>::mFactory = CConcreteFactory2<BASE,CONCRETE>();\
	template<> bool CConcreteFactory2<BASE,CONCRETE>::bRegistered = CFactoryManager<BASE>::RegisterFactory(#ID,&CConcreteFactory2<BASE,CONCRETE>::mFactory);\


#endif //CORINET_FACTORY
