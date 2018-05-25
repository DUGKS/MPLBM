#ifndef _ZERO_NAMESPACE_H
#define _ZERO_NAMESPACE_H
//
namespace PhaseFieldAC
{
	double const

	M_Phi = 0.02,

	Pe = U0*::ChLength/M_Phi,

	Cn = 5/::ChLength,

	wI = ::ChLength*Cn,

	Sigma = 1E-3,

	Beta = 12.0*Sigma/wI,

	Kappa = 3.0*Sigma*wI/2;

	double const 

	PhiL = 1.0, PhiV = 0.0,

	RhoL = 10,  RhoV = 1.0,

	aPhi = (RhoL-RhoV)/(PhiL-PhiV), bPhi = RhoV-aPhi*PhiV,

	NuL  = ::Nu0,NuV = ::Nu0,

	TauPhi = M_Phi/RT + 0.5,

	radius = 30;
}

#endif