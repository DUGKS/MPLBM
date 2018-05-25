#ifndef _ARK_DVDF_H
#define _ARK_DVDF_H

class DVDF
{
public:
	static int const Q = 9;
//	enum VDF{F,FNext,Eq,So,Num};
//-----------constructor and destructor-----------------
	DVDF();
	DVDF(const DVDF &rhs);
	DVDF& operator=(const DVDF &rhs);
	~DVDF();
	double Tau = 0.0;
//--------------------data------------------------------
	double * __restrict__ F  = nullptr;
	double * __restrict__ FNext = nullptr;
	double * __restrict__ Eq = nullptr;
	double * __restrict__ So = nullptr;
//private:
	int *token = nullptr;
};

#endif