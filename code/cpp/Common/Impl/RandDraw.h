/*********************************************************************************************
 * Name      :  RandDraw.h
 *
 * Purpose   :  The "real" random number generator.
 *
 * Notes	 :	Adapted from "Numerical Recipes in C", Chapter 7,
 *				and "C++ Programming Language" Chapter 22.
 *				The actual method for generating numbers (in RandDraw::draw()) is not 
 *				guaranteed machine-independent and may not work on all processors.
 *				See file "RandTest.h" for compatibility testing.
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

#ifndef CORINET_RANDDRAW
#define CORINET_RANDDRAW

#include <Platform/Platform.h>
#include <cstdlib>
#include <ctime>

namespace CORINET {

class RandDraw {
	static unsigned int seedBase;
	unsigned int randx;
public:
	RandDraw() {randx = 0;}	
	int mask(int x) {return x&0x7fffffff;}
	int draw() {return randx = randx*1664525 + 1013904223;}
	double fdraw() {return mask(draw())/2147483648.0;}	//uniform random double in [0,1]
	void seed() {srand(time(0)); randx = seedBase + rand(); seedBase += 2938201;}
	void seed(size_t s) {randx = s;}
};

} //end namespace CORINET

#endif //CORINET_RANDDRAW


