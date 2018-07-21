#include "LBMNameSpace.h"
#include "Integral.h"
//
namespace PF = PhaseFieldAC;
using PF::aPhi;
using PF::bPhi;
using PF::TauPhi;
//
namespace D2Q9
{
double xi_u[Q] = {0, 1, 0,-1, 0, 1,-1,-1, 1};

double xi_v[Q] = {0, 0, 1, 0,-1, 1, 1,-1,-1};

double omega[Q] = {4.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/36,1.0/36,1.0/36,1.0/36};

}
using D2Q9::xi_u;
using D2Q9::xi_v;
using D2Q9::omega;

double const Kp = RT*9/5.0;
double const K_hSo = 1.0-1.0/(2.0*TauPhi);
double const K_fSo = 1.0-1.0/(2.0*Tau0);
//
void update_Eq(Node2D &node)
{
	double uu,u1;
	uu = node.MsQ().SqrtUV();
	for(int k = 0;k < Q;++k)
	{
		u1 = (xi_u[k]*node.MsQ().U + xi_v[k]*node.MsQ().V)/RT;
		//
		#ifdef _ARK_ALLENCAHN_FLIP
		node.h.Eq[k] = omega[k]*node.msq->Phi*(1.0+u1);
		#endif
		
		//
		#ifdef _ARK_MOMENTUM_FLIP
		double Gamma = u1 + 0.5*u1*u1 - uu*Lambda0; 
		node.f.Eq[k] = omega[k]*(node.msq->p/RT + node.msq->Rho*Gamma)-(!k)*node.msq->p/RT;
		#endif
		
	}
}
void update_So(Node2D &node)
{
	double uu,u1;
	uu = node.MsQ().SqrtUV();
	for(int k = 0;k < Q;++k)
	{
		#ifdef _ARK_ALLENCAHN_FLIP
		node.h.So[k] = K_hSo*omega[k]*(xi_u[k]*node.msq->Phi_x + xi_v[k]*node.msq->Phi_y);
		#endif

		#ifdef _ARK_MOMENTUM_FLIP
		u1 = (xi_u[k]*node.MsQ().U + xi_v[k]*node.MsQ().V)/RT;

		// node.f.So[k] = K_fSo*omega[k]*
		// (
		// 	(xi_u[k]*(node.msq->Fx) + xi_v[k]*(node.msq->Fy))/RT
		// +	u1*(xi_u[k]*(node.msq->Rho_x) + xi_v[k]*(node.msq->Rho_y))
		// );

		double Gamma = u1 + 0.5*u1*u1 - uu*Lambda0;
		node.f.So[k] = K_fSo*omega[k]*
		(
			(1+Gamma)*(
				(xi_u[k]-node.MsQ().U)*(node.msq->Fx)
			 	+ 
				(xi_v[k]-node.MsQ().V)*(node.msq->Fy)
					  )/RT
			+
			Gamma*(
				(xi_u[k]-node.MsQ().U)*(node.msq->Rho_x)
			 	+ 
				(xi_v[k]-node.MsQ().V)*(node.msq->Rho_y)
				)
		);
		#endif
	}
}
void MacroVars(Node2D &node)
{
	node.msq->Phi = VectorDot(node.h.F);
	node.msq->Rho = aPhi*node.msq->Phi + bPhi;
//
	// node.msq->U = 0.0;
	// node.msq->V = 0.0;
	double &xn = node.xn, &yn = node.yn;
	//---------------Smoothed Flow------------------
	// node.MsQ().U = 
	// -U0*sin(4*PI*xn/ChLength)*sin(4*PI*yn/ChLength)*cos(PI*(step+1.0)/PhaseFieldAC::iT);
	// node.MsQ().V = 
	// -U0*cos(4*PI*xn/ChLength)*cos(4*PI*yn/ChLength)*cos(PI*(step+1.0)/PhaseFieldAC::iT);
	//---------------------------------
	// node.MsQ().U   = 
	// U0*sin(PI*xn/ChLength)*cos(PI*yn/ChLength)
	// *cos(PI*(step+1.0)/PhaseFieldAC::iT);
	// node.MsQ().V   = 
	// -U0*cos(PI*xn/ChLength)*sin(PI*yn/ChLength)
	// *cos(PI*(step+1.0)/PhaseFieldAC::iT);
	//-------------------------------shear flow PRE2016-----------------
	// if(PhaseFieldAC::iT/2 == step)
	// {
	// 	node.MsQ().U   = 
	// 	-U0*PI*sin(PI*xn/ChLength)*cos(PI*yn/ChLength);
	// 	node.MsQ().V   = 
	// 	U0*PI*cos(PI*xn/ChLength)*sin(PI*yn/ChLength);
	// }
	//-------------------------------shear flow PRE2014------------------
	// if(PhaseFieldAC::iT/2 == step)
	// {
	// 	node.MsQ().U   = 
	// 	-U0*sin(PI*xn/ChLength)*sin(PI*xn/ChLength)*sin(2*PI*yn/ChLength);
	// 	node.MsQ().V   = 
	// 	U0*sin(PI*yn/ChLength)*sin(PI*yn/ChLength)*sin(2*PI*xn/ChLength);
	// }

	#ifdef _ARK_MOMENTUM_FLIP
	node.msq->U = (VectorDot(node.f.F,xi_u) + (node.msq->Fx)/2)/node.MsQ().Rho;
	node.msq->V = (VectorDot(node.f.F,xi_v) + (node.msq->Fy)/2)/node.MsQ().Rho;
	double uu = node.MsQ().SqrtUV();
//
	node.MsQ().p = VectorDot(node.f.F)-node.f.F[0]
			 + 0.5*(node.msq->Rho_x*node.msq->U + node.msq->Rho_y*node.msq->V)
			 -node.msq->Rho*(uu*Lambda0)*omega[0];
	node.MsQ().p *= Kp;
	#endif
}
void Collision(Node2D &node)
{
	for(int k = 0;k < Q;++k)
	{
		
		#ifdef _ARK_ALLENCAHN_FLIP
		node.h.FNext[k] = node.h.F[k]-1.0/TauPhi*(node.h.F[k]-node.h.Eq[k]) + node.h.So[k];
		#endif

		#ifdef _ARK_MOMENTUM_FLIP
		node.f.FNext[k] = node.f.F[k]-1.0/Tau0*(node.f.F[k]-node.f.Eq[k]) + node.f.So[k];
		#endif
	}
}
void Stream(Node2D &node)
{
	for(int k = 0;k < Q;++k)
	{
		int ip = node.in - xi_u[k],jp = node.jn - xi_v[k];
		#ifdef _ARK_ALLENCAHN_FLIP
		node.h.F[k] = NodeArray[ip][jp].h.FNext[k];
		#endif

		#ifdef _ARK_MOMENTUM_FLIP
		node.f.F[k] = NodeArray[ip][jp].f.FNext[k];
		#endif
	} 
}