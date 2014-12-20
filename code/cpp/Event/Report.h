/*********************************************************************************************
 * Name      :  Report.h
 *
 * Purpose   :  Abstract interface for report writers.
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

#ifndef CORINET_REPORT
#define CORINET_REPORT

#include <Platform/Platform.h>
#include <string>

namespace CORINET {
	class CExTimeInfo;
	class SubArrayIteratorConst;
	class SliceIteratorConst;
	class IndirectIteratorConst;
	class MultipleSubArrayIteratorConst;
	class MatrixIteratorConst;
	class SynapseWrapper;
	
class CReport {
public:
	virtual ~CReport() {}
	virtual void Initialise(void*,CExTimeInfo*) =0;
	virtual void Write(size_t,SubArrayIteratorConst*,CExTimeInfo*) =0;
	virtual void Write(size_t,SliceIteratorConst*,CExTimeInfo*) =0;
	virtual void Write(size_t,IndirectIteratorConst*,CExTimeInfo*) =0;
	virtual void Write(size_t,MultipleSubArrayIteratorConst*,CExTimeInfo*) =0;
	virtual void Write(size_t,MatrixIteratorConst*,CExTimeInfo*,size_t =0) =0;//weights or patterns
	virtual void Write(size_t,SynapseWrapper*,CExTimeInfo*) =0;//per-synapse activation values 
	virtual void Finalise(void*,CExTimeInfo*) =0;

	virtual void MakeTargetNode(void*,const std::string&,const std::string&,const std::string&) =0;
};

} //end namespace CORINET	

#endif //CORINET_REPORT
