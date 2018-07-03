#include "DVDF.h"

void AllocateARK(double* __restrict__ &f,int const Q)
{
	f = new double [Q];
}
void DeallocateARK(double* __restrict__ &f,int const Q)
{
	delete[] f;
	f = nullptr;
}
void DVDF::alloc()
{
	AllocateARK(F,Q);
	AllocateARK(M,Q);
	AllocateARK(FNext,Q);
	AllocateARK(Eq,Q);
	AllocateARK(So,Q);
}
void DVDF::deAlloc()
{
	DeallocateARK(F,Q);
	DeallocateARK(M,Q);
	DeallocateARK(FNext,Q);
	DeallocateARK(Eq,Q);
	DeallocateARK(So,Q);
}
void DVDF::assign(const DVDF &rhs)
{
	F = rhs.F;
	M = rhs.M;
	FNext = rhs.FNext;
	Eq = rhs.Eq;
	So = rhs.So;
	token = rhs.token;
	++*token;
}
//!constructor
DVDF::DVDF():token(new int(1))
{
	alloc();
}
//!copy constructor
DVDF::DVDF(const DVDF &rhs)
{
	assign(rhs);
}
//!destructor
DVDF::~DVDF()
{
	if(--*token == 0)
	{
		deAlloc();
	}
}
//!assignment operator
DVDF& DVDF::operator=(const DVDF &rhs)
{
	if(token != rhs.token)
	{
		if(--*token == 0)
		{
			deAlloc();
			delete token;
		}
		assign(rhs);
	}
	return *this;
}