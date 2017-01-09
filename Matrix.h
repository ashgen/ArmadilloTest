/*
 * Matrix.h
 *
 *  Created on: 06-Jan-2017
 *      Author: ashishsachan
 */

#ifndef INCLUDE_MATRIX_H_
#define INCLUDE_MATRIX_H_
#pragma once
#include <cassert>
#include <iostream>
#include <boost/assert.hpp>
/*
 * Matrix Class for storing arbitary 1 or 2 or 3 dimension objects
 */
namespace mat{
template<class T>
class Matrix{
public:
	Matrix<T>():nrow(0),ncol(0),nslice(0),nelements(0),data(nullptr){
	}
	Matrix<T>(const int i):nrow(i),ncol(0),nslice(0),data(nullptr){
		nelements=nrow;
	}
	Matrix<T>(const int i,const int j):nrow(i),ncol(j),nslice(0),data(nullptr){
		nelements=nrow*ncol;
	}
	~Matrix<T>(){
		if(data == nullptr) return;
			delete[] data;
	}
	Matrix<T>(const int i,const int j,const int k):nrow(i),ncol(j),nslice(k),data(nullptr){
		nelements=nrow*ncol*nslice;
	}
	Matrix<T>(const int i,const int j,const T* p):nrow(i),ncol(j),nslice(0){
		nelements=nrow*ncol;
		init(p);
	}
	Matrix<T>(const int i,const int j,const int k,T* p):nrow(i),ncol(j),nslice(k){
		nelements=nrow*ncol*nslice;
		init(p);
	}
	inline void init(const T* p){
			data =new(std::nothrow) T[nelements];
			std::fill(data ,data+nelements,p);//Should have a copy contructor for the class
	}
	inline T* operator() (const int i,const int j) const {
		BOOST_VERIFY_MSG(i<nrow,"row greater than nrows");
		BOOST_VERIFY_MSG(j<ncol,"row greater than ncol");
		return data==nullptr?nullptr:data+i*nrow+j;
	}
	inline T* operator() (const int i,const int j,const int k) const {
		BOOST_VERIFY_MSG(i<nrow,"row greater than nrows");
		BOOST_VERIFY_MSG(j<ncol,"row greater than ncol");
		BOOST_VERIFY_MSG(k<nslice,"row greater than ncol");
		return data==nullptr?nullptr:data+i*nrow+j*ncol+k;
	}
private:
	const int nrow;
	const int ncol;
	const int nslice;

	int nelements;
	T* data;
};




}
#endif /* INCLUDE_MATRIX_H_ */
