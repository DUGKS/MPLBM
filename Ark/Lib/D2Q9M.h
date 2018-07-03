#ifndef _D2Q9_MRT_H
#define _D2Q9_MRT_H
namespace D2Q9MRT
{
	int const Q = 9;
	//---------------------------------MRT model----------------------------
	double const

	Tau0 = 0.8,

	Alpha = 1.0;

	double const

	S0 = 1.0/Tau0,

	Se = 1.0/Tau0,

	Sepsilon = 1.0/Tau0,

	Sj = 1.0/Tau0,

	Sq = 1.0/Tau0,

	Sp = 1.0/Tau0;

	double const 
	A = 1.0/4.0,
	B = 1.0/6.0,
	C = 1.0/9.0,
	D = 1.0/12.0,
	E = 1.0/18.0,
	F = 1.0/36.0;
//
	extern double diagS[Q];

	extern double diagSForce[Q];

	extern double M[Q][Q];

	extern double InverseM[Q][Q];

	extern double xi_u[Q];

	extern double xi_v[Q];
}
#endif