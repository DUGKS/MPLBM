#include "LBMNameSpace.h"
//
namespace PF = PhaseFieldAC;
using PF::aPhi;
using PF::bPhi;
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
double const K_hSo = 1.0-1.0/(2.0*PF::TauPhi);
double const K_fSo = 1.0-1.0/(2.0*Tau0);
//
double VectorDot(const double *const first,const double *const second)
{
	double sum = 0;
	for(int j = 0;j < Q;++j)
		sum += first[j]*second[j];
	return sum;
}
double VectorDot(const double *const first)
{
	double sum = 0;
	for(int j = 0;j < Q;++j)
		sum += first[j];
	return sum;
}
//
void update_Eq(Node2D &node)
{
	double uu,u1;
	uu = node.MsQ().SqrtUV();
	for(int k = 0;k < Q;++k)
	{
		u1 = (xi_u[k]*node.MsQ().U + xi_v[k]*node.MsQ().V)/RT;
		double Gamma = u1 + 0.5*u1*u1 - uu*Lambda0; 
		//
		node.h.Eq[k] = omega[k]*node.msq->Phi*(1.0+u1);
		node.h.So[k] = K_hSo*omega[k]*(xi_u[k]*node.msq->Phi_x + xi_v[k]*node.msq->Phi_y);
		//
		node.f.Eq[k] = omega[k]*(node.msq->p/RT + node.msq->Rho*Gamma)-(!k)*node.msq->p/RT;
		node.f.So[k] = K_fSo*omega[k]*
		(
			(xi_u[k]*(node.msq->Fx) + xi_v[k]*(node.msq->Fy))/RT
		+	u1*(xi_u[k]*(node.msq->Rho_x) + xi_v[k]*(node.msq->Rho_y))
		);
	}
}
void MacroVars(Node2D &node)
{
	// for(int k = 0;k < Q;++k)
	// {
	// 	cout <<node.fplus[k]<<'\n';
	// }
	// getchar();
	node.msq->Phi = VectorDot(node.h.F);
	node.msq->Rho = aPhi*node.msq->Phi + bPhi;
//
	// node.msq->U = 0.0;
	// node.msq->V = 0.0;
	node.msq->U = (VectorDot(node.f.F,xi_u) + (node.msq->Fx)/2)/node.MsQ().Rho;
	node.msq->V = (VectorDot(node.f.F,xi_v) + (node.msq->Fy)/2)/node.MsQ().Rho;
	double uu = node.MsQ().SqrtUV();
//
	node.MsQ().p = VectorDot(node.f.F)-node.f.F[0]
			 + 0.5*(node.msq->Rho_x*node.msq->U + node.msq->Rho_y*node.msq->V)
			 -node.msq->Rho*(uu*Lambda0);
	node.MsQ().p *= Kp;
}
void Collision(Node2D &node)
{
	for(int k = 0;k < Q;++k)
	{
		node.h.FNext[k] = node.h.F[k]-1.0/PF::TauPhi*(node.h.F[k]-node.h.Eq[k]) + node.h.So[k];
		node.f.FNext[k] = node.f.F[k]-1.0/Tau0      *(node.f.F[k]-node.f.Eq[k]) + node.f.So[k];
		{
			// if(step == 1)
			// {
			// 	cout << node.h.FNext[k]<<"    "<<<<nl;
			// 	getchar();
			// }
		}
	}
}
void Stream(Node2D &node)
{
	for(int k = 0;k < Q;++k)
	{
		int ip = node.in - xi_u[k],jp = node.jn - xi_v[k];
		node.h.F[k] = NodeArray[ip][jp].h.FNext[k];
		node.f.F[k] = NodeArray[ip][jp].f.FNext[k];
	} 
}