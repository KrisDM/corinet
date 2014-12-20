/*********************************************************************************************
 * Name      :  Weights.h
 *
 * Purpose   :  Class defining the weights of an integration site. 
 *
 * Notes	 :	2D structure to contain weights; rows are mapped to inputs, columns to nodes.
 *				There are four different groups of access functions: the first set provides normal
 *				access to weight values; the second set maintains max weight values for each node;
 *				the third set maintains max weight values for each input; the fourth set maintains
 *				max weight values for nodes and inputs. These three alternatives to the normal 
 *				access functions can be used when max operations during integration are performed
 *				frequently relative to weight adjustments (which invalidate stored max values).
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

#ifndef CORINET_WEIGHTS
#define CORINET_WEIGHTS

#include <Util/Iterator.h>
#include <limits>

namespace CORINET {

class HWeights {
	std::valarray<double> mWeightVals; //the weight values proper
	std::valarray<size_t> mMaxWForInput; //max over all weights leaving input i, for all inputs
	std::valarray<size_t> mMaxWForNode; //max over all weights arriving in node j, for all nodes
	MatrixIterator mMatrix; //provides access to the weight values
	MatrixIteratorConst mConstMatrix;
public:
	//constructor
	HWeights(size_t inputs,size_t nodes) 
		: mWeightVals(0.0,inputs*nodes),mMaxWForInput(std::numeric_limits<size_t>::max(),inputs),
		mMaxWForNode(std::numeric_limits<size_t>::max(),nodes),mMatrix(&mWeightVals,inputs),mConstMatrix(&mWeightVals,inputs) {}

	//destructor
	~HWeights() {}

	//size functions
	size_t NumInputs() const {return mMatrix.rows();}
	size_t NumNodes() const {return mMatrix.columns();}

	//subscripting operator, const; use AddX and SetX functions for changing weightvalues
	double operator()(size_t input,size_t node) const {return mConstMatrix(input,node);}

	//operations for adjusting weights, there are four sets, as explained above
	void Add1(double val,size_t input,size_t node) {
		mMatrix(input,node)+=val;
	}
	void Div1(double val,size_t input,size_t node) {
		mMatrix(input,node)/=val;
	}
	void Prod1(double val,size_t input,size_t node) {
		mMatrix(input,node)*=val;
	}
	void Set1(double val,size_t input,size_t node) {
		mMatrix(input,node)=val;
	}
	void Add2(double val,size_t input,size_t node) {
		mMatrix(input,node)+=val;
		mMaxWForNode[node] = std::numeric_limits<size_t>::max();
	}
	void Div2(double val,size_t input,size_t node) {
		mMatrix(input,node)/=val;
		mMaxWForNode[node] = std::numeric_limits<size_t>::max();
	}
	void Prod2(double val,size_t input,size_t node) {
		mMatrix(input,node)*=val;
		mMaxWForNode[node] = std::numeric_limits<size_t>::max();
	}
	void Set2(double val,size_t input,size_t node) {
		mMatrix(input,node)=val;
		mMaxWForNode[node] = std::numeric_limits<size_t>::max();
	}
	void Add3(double val,size_t input,size_t node) {
		mMatrix(input,node)+=val;
		mMaxWForInput[input] = std::numeric_limits<size_t>::max();
	}
	void Div3(double val,size_t input,size_t node) {
		mMatrix(input,node)/=val;
		mMaxWForInput[input] = std::numeric_limits<size_t>::max();
	}
	void Prod3(double val,size_t input,size_t node) {
		mMatrix(input,node)*=val;
		mMaxWForInput[input] = std::numeric_limits<size_t>::max();
	}
	void Set3(double val,size_t input,size_t node) {
		mMatrix(input,node)=val;
		mMaxWForInput[input] = std::numeric_limits<size_t>::max();
	}
	void Add4(double val,size_t input,size_t node) {
		mMatrix(input,node)+=val;
		mMaxWForNode[node] = std::numeric_limits<size_t>::max();
		mMaxWForInput[input] = std::numeric_limits<size_t>::max();
	}
	void Div4(double val,size_t input,size_t node) {
		mMatrix(input,node)/=val;
		mMaxWForNode[node] = std::numeric_limits<size_t>::max();
		mMaxWForInput[input] = std::numeric_limits<size_t>::max();
	}
	void Prod4(double val,size_t input,size_t node) {
		mMatrix(input,node)*=val;
		mMaxWForNode[node] = std::numeric_limits<size_t>::max();
		mMaxWForInput[input] = std::numeric_limits<size_t>::max();
	}
	void Set4(double val,size_t input,size_t node) {
		mMatrix(input,node)=val;
		mMaxWForNode[node] = std::numeric_limits<size_t>::max();
		mMaxWForInput[input] = std::numeric_limits<size_t>::max();
	}

	//max functions, two versions each: one performing the true max operation, one checking stored max values first
	double MaxWForInput(size_t input,size_t s) {
		MatrixIterator::RowIterator inputW = mMatrix.GetRow(input);
		double m = inputW[0];
		for(size_t j=1;j<s;++j) {
			if (inputW[j] > m) m = inputW[j];
		}
		return m;
	}

	double MaxWForInputSpecial(size_t input,size_t s) {
		if (mMaxWForInput[input]==std::numeric_limits<size_t>::max()) {
			MatrixIterator::RowIterator inputW = mMatrix.GetRow(input);
			double m = inputW[0];
			size_t mj = 0;
			for(size_t j=1;j<s;++j) {
				if (inputW[j] >= m) {
					m = inputW[j];
					mj = j;
				}
			}
			mMaxWForInput[input] = mj;
		}
		return mMatrix(input,mMaxWForInput[input]);
	}

	double MaxWForNode(size_t node) {
		MatrixIterator::ColIterator nodeW = mMatrix.GetCol(node);
		double m = nodeW[0];
		for(nodeW.begin();!(nodeW.end());++nodeW) {
			if (*nodeW > m) m = *nodeW;
		}
		return m;
	}

	double MaxWForNodeSpecial(size_t node) {
		if (mMaxWForNode[node]==std::numeric_limits<size_t>::max()) { 
			MatrixIterator::ColIterator nodeW = mMatrix.GetCol(node);
			double m = nodeW[0];
			size_t mi = 0;
			nodeW.begin();
			for(size_t i=0;!(nodeW.end());++i,++nodeW) {
				if (*nodeW >= m) {
					m = *nodeW;
					mi = i;
				}
			}
			mMaxWForNode[node] = mi;
		} 
		return mMatrix(mMaxWForNode[node],node);
	}

	//Invalidate all current stored maxima
	void InvalMaxWForNodes() {mMaxWForNode = std::numeric_limits<size_t>::max();}
	void InvalMaxWForInputs() {mMaxWForInput = std::numeric_limits<size_t>::max();}	

	//Get the raw weight values
	std::valarray<double>* GetVals() {return &mWeightVals;}
};

} //end namespace CORINET

#endif //CORINET_WEIGHTS
