/*********************************************************************************************
 * Name      :  Nodes.h
 *
 * Purpose   :  Two classes to provide access to node values in a network's nodepool.
 *				The first one is to be used to address the output of blocks,
 *				the second one to address the input to integrationSites.
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

#ifndef CORINET_NODES
#define CORINET_NODES

#include <Util/Iterator.h>

namespace CORINET {

class HIntegrationInput : public IndirectIteratorConst {//input to integrationSite, only read access thus const iterator
private:
	//unimplemented copy constructor
	HIntegrationInput(const HIntegrationInput&); 
public:
	//constructor
	HIntegrationInput(std::valarray<double>* nodepool,std::valarray<size_t>* indices) : IndirectIteratorConst(nodepool,indices) {}

	//destructor
	~HIntegrationInput() {}
	
	double max() {
		double m = operator[](0);
		for(begin();!end();operator++()) {
			if (**this > m) m = (**this);
		}
		return m;
	}
	double min() {
		double m = operator[](0);
		for(begin();!end();operator++()) {
			if (**this < m) m = (**this);
		}
		return m;
	}
	double sum() {
		double su = 0.0;
		for(begin();!end();operator++()) {
			su += (**this);
		}
		return su;
	}
};

class HBlockOutput : public SubArrayIterator {//class implementing output of blocks, write access thus non-const
private:
	//unimplemented copy constructor
	HBlockOutput(const HBlockOutput&);
public:
	//constructor
	HBlockOutput(std::valarray<double>* nodepool,size_t b,size_t s) : SubArrayIterator(nodepool,b,s) {}

	//destructor
	~HBlockOutput() {}

	//operations for first s nodes (so that it works in conjunction with constructive versions of the algorithms)
	double max(size_t s) {
		double m = operator[](0);
		for(size_t i=1;i<s;++i) {
			if (operator[](i) > m) m = operator[](i);
		}
		return m;
	}
	double min(size_t s) {
		double m = operator[](0);
		for(size_t i=1;i<s;++i) {
			if (operator[](i) < m) m = operator[](i);
		}
		return m;
	}
	double sum(size_t s) {
		double su = 0.0;
		for(size_t i=0;i<s;++i) {
			su += operator[](i);
		}
		return su;
	}
};

} //end namespace CORINET

#endif //CORINET_NODES
