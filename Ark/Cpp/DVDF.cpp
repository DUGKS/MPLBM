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
DVDF::DVDF():token(new int(1))
{
	AllocateARK(F,Q);
	AllocateARK(FNext,Q);
	AllocateARK(Eq,Q);
	AllocateARK(So,Q);
}
DVDF::~DVDF()
{
	if(--*token == 0)
	{
		DeallocateARK(F,Q);
		DeallocateARK(FNext,Q);
		DeallocateARK(Eq,Q);
		DeallocateARK(So,Q);
	}
}
DVDF::DVDF(const DVDF &rhs)
{
	F = rhs.F;
	FNext = rhs.FNext;
	Eq = rhs.Eq;
	So = rhs.So;
	token = rhs.token;
	++*token;
}
DVDF& DVDF::operator=(const DVDF &rhs)
{
	if(token != rhs.token)
	{
		if(--*token == 0)
		{
			DeallocateARK(F,Q);
			DeallocateARK(FNext,Q);
			DeallocateARK(Eq,Q);
			DeallocateARK(So,Q);
			delete token;
		}
	//
		F = rhs.F;
		FNext = rhs.FNext;
		Eq = rhs.Eq;
		So = rhs.So;
		token = rhs.token;
	//
		++*token;
	}
	return *this;
}