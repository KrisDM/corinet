/*********************************************************************************************
 * Name      :  Patterns.h
 *
 * Purpose   :  Auxiliary classes used in tasks.
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

#ifndef CORINET_PATTERNS
#define CORINET_PATTERNS

#include <Util/Iterator.h>
#include <valarray>

namespace CORINET {

class HPattern2D : public MatrixIterator {//wrapper around valarray for 2D patterns such as in the bars problems
	//unimplemented copy constructor
	HPattern2D(const HPattern2D&);
public:
	//constructor
	HPattern2D(std::valarray<double>* const pv,size_t r) : MatrixIterator(pv,r) {}
	
	//destructor
	~HPattern2D() {}

	//set a row, a column or a diagonal to a certain value
	void SetRow(size_t r,double val) {size_t c = columns(); for(size_t j=0;j<c;++j) (*this)(r,j) = val;}
	void SetCol(size_t c,double val) {size_t r = rows(); for(size_t i=0;i<r;++i) (*this)(i,c) = val;}
	//main diagonal = 0, diagonals below main diagonal are negative, above main diagonal are positive
	void SetDiagLRUp(int d,double val) {//up going diagonal from left to right
		int r = rows();
		int c = columns();
		if (d<0) 
			for(int i=r-1,j=-d;(i>=0 && j<c);--i,++j) (*this)(i,j) = val;
		else 
			for(int i=r-1-d,j=0;(i>=0 && j<c);--i,++j) (*this)(i,j) = val;
	}
	void SetDiagLRDown(int d,double val) {//down going diagonal from left to right
		int r = rows();
		int c = columns();
		if (d<0) 
			for(int i=-d,j=0;(i<r && j<c);++i,++j) (*this)(i,j) = val;
		else 
			for(int i=0,j=d;(i<r && j<c);++i,++j) (*this)(i,j) = val;
	}
}; 

} //namespace CORINET

#endif //CORINET_PATTERNS
