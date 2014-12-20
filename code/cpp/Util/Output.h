/*********************************************************************************************
 * Name      :  Output.h
 *
 * Purpose   :  Output operators for CORINET iterators.
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

#ifndef CORINET_OUTPUT
#define CORINET_OUTPUT

#include <Util/Iterator.h>
#include <ostream>
#include <iomanip>
#include <cmath>

namespace CORINET {

std::ostream& operator<<(std::ostream& s,SubArrayIteratorConst& pv)
{
	int prec = s.precision();
	double mult = pow(10.0,prec);
	for(pv.begin();!pv.end();++pv) {
		s << std::setw(prec + 4) << static_cast<long>((*pv)*mult)/mult;
	}
	return s;
}

std::ostream& operator<<(std::ostream& s,SliceIteratorConst& pv)
{
	int prec = s.precision();
	double mult = static_cast<size_t>(pow(10.0,prec));
	for(pv.begin();!pv.end();++pv) {
		s << std::setw(prec + 4) << static_cast<long>((*pv)*mult)/mult;
	}
	return s;
}

std::ostream& operator<<(std::ostream& s,IndirectIteratorConst& pv)
{
	int prec = s.precision();
	double mult = static_cast<size_t>(pow(10.0,prec));
	for(pv.begin();!pv.end();++pv) {
		s << std::setw(prec + 4) << static_cast<long>((*pv)*mult)/mult;
	}
	return s;
}

std::ostream& operator<<(std::ostream& s,MultipleSubArrayIteratorConst& pv)
{
	int prec = s.precision();
	double mult = static_cast<size_t>(pow(10.0,prec));
	for(pv.begin();!pv.end();++pv) {
		s << std::setw(prec + 4) << static_cast<long>((*pv)*mult)/mult;
	}
	return s;
}

std::ostream& operator<<(std::ostream& s,MatrixIteratorConst& pv)
{
	const size_t r = pv.rows();
	for(size_t i=0;i<r;++i) {
		SliceIteratorConst rowit = pv.GetRow(i);
		s << rowit << '\n';
	}
	return s;
}

} //end namespace CORINET

#endif //CORINET_OUTPUT

