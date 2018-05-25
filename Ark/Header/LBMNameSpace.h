#include "Node2D.h"
#include "ZeroConstant.h"

extern Node2D **NodeArray;

extern int step;

extern double SumRho;

template <typename T>
void AllocateArk(T **&ptr,int const Qx,int const Qy)
{
	ptr = new T* [Qx];
	for(int k = 0;k < Qx;++k)
		ptr[k] = new T [Qy]();
}

template <typename T>
void DeallocateArk(T **&ptr,int const Qx,int const Qy)
{
	for(int k = 0;k < Qx;++k)
	{
		delete[] ptr[k];
		ptr[k] = nullptr;
	}
	delete[] ptr;
	ptr = nullptr;
}
//
inline 
void setZero(double &d)
{
	if(d < Tiny && d > -Tiny) d = 0;
}
#include <iostream>
using std::cout;