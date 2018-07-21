#ifndef _ZERO_NAMESPACE_H
#define _ZERO_NAMESPACE_H
//
namespace PhaseFieldAC
{
	double const

	M_Phi = 0.1,

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

	centerX = 0.5*ChLength,centerY = 0.5*ChLength,

	radius = 0.25*ChLength;

	// radius = 30;

	#ifdef _ARK_ENDTIME_FLIP

	int const iT = (ChLength/U0)+1;

	#endif
}

namespace PseudoPotential{}

//------------------------output control------------------
#ifdef _ARK_ENDTIME_FLIP

int const 

EndStep = PhaseFieldAC::iT+100;

#endif

int const

ConvergeStep = 10000,

writeFileStep = 10000;

double const 

RESIDUAL = 1E-13;
#endif