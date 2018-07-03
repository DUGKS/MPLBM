#include "LBMNameSpace.h"
//
namespace D2Q9MRT{
double diagS[Q] = {S0,Se,Sepsilon,Sj,Sq,Sj,Sq,Sp,Sp};

double diagSForce[Q] =
{
	1.0-S0/2,
	1.0-Se/2,
	1.0-Sepsilon/2,
	1.0-Sj/2,
	1.0-Sq/2,
	1.0-Sj/2,
	1.0-Sq/2,
	1.0-Sp/2,
	1.0-Sp/2,
};
double M[Q][Q] = 
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{-4,-1,-1,-1,-1, 2, 2, 2, 2},
	{ 4,-2,-2,-2,-2, 1, 1, 1, 1},			
	{ 0, 1, 0,-1, 0, 1,-1,-1, 1},
	{ 0,-2, 0, 2, 0, 1,-1,-1, 1},
	{ 0, 0, 1, 0,-1, 1, 1,-1,-1},
	{ 0, 0,-2, 0, 2, 1, 1,-1,-1},
	{ 0, 1,-1, 1,-1, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 1,-1, 1,-1}
};
double InverseM[Q][Q] = 
{
	{ C,-C, C, 0, 0, 0, 0, 0, 0},
	{ C,-F,-E, B,-B, 0, 0, A, 0},
	{ C,-F,-E, 0, 0, B,-B,-A, 0},
	{ C,-F,-E,-B, B, 0, 0, A, 0},
	{ C,-F,-E, 0, 0,-B, B,-A, 0},
	{ C, E, F, B, D, B, D, 0, A},
	{ C, E, F,-B,-D, B, D, 0,-A},
	{ C, E, F,-B,-D,-B,-D, 0, A},
	{ C, E, F, B, D,-B,-D, 0,-A}
};
double xi_u[Q] = {0, 1, 0,-1, 0, 1,-1,-1, 1};
double xi_v[Q] = {0, 0, 1, 0,-1, 1, 1,-1,-1};
}
using D2Q9MRT::M;
using D2Q9MRT::InverseM;
using D2Q9MRT::xi_u;
using D2Q9MRT::xi_v; 
//
void update_Eq(Node2D &node)
{
	double const &Rho = node.MsQ().Rho;
	double const &U   = node.MsQ().U;
	double const &V   = node.MsQ().V;
	node.f.Eq[0] = Rho;
	node.f.Eq[1] = (-2.0 + 3.0*(U*U + V*V))*Rho;
	node.f.Eq[2] = (D2Q9::Alpha - 3.0*(U*U + V*V))*Rho;
	node.f.Eq[3] =  Rho*U;
	node.f.Eq[4] = -Rho*U;
	node.f.Eq[5] =  Rho*V;
	node.f.Eq[6] = -Rho*V;
	node.f.Eq[7] = Rho*(U*U - V*V);
	node.f.Eq[8] = Rho*U*V;
}
void update_So(Node2D &node)
{
	double const &U    = node.MsQ().U;
	double const &V    = node.MsQ().V;
	double const &Fx   = node.MsQ().Fx;
	double const &Fy   = node.MsQ().Fy;
	node.f.So[0] = 0;
	node.f.So[1] = 6.0*(Fx*U+Fy*V);
	node.f.So[2] = -node.f.So[1];
	node.f.So[3] = Fx;
	node.f.So[4] = -Fx;
	node.f.So[5] = Fy;
	node.f.So[6] = -Fy;
	node.f.So[7] = 2.0*(Fx*U - Fy*V);
	node.f.So[8] = (Fx*V + Fy*U);
}
void Collision(Node2D &node)
{
	for(int k = 0;k < Q;++k)
	{
		node.f.M[k] = VectorDot(M[k],node.f.F); 
	}
	for(int k = 0;k < Q;++k)
	{
		node.f.M[k] = node.f.M[k] - diagS[k]*(node.f.M[k] - node.f.Eq[k])
					+ diagSForce[k]*node.f.So[k];
	}
	for(int k = 0;k < Q;++k)
	{
		node.f.FNext[k] = VectorDot(InverseM[k],node.f.M);
	}
}
void Stream(Node2D &node)
{
	for(int k = 0;k < Q;++k)
	{
		int ip = node.in - xi_u[k],jp = node.jn - xi_v[k];
		node.f.F[k] = NodeArray[ip][jp].f.FNext[k];
	} 
}
void MacroVars(Node2D &node)
{
	node.MsQ().Rho = VectorDot(node.f.F);
	node.MsQ().U = (VectorDot(node.f.F,xi_u) + node.MsQ().Fx/2)/node.MsQ().Rho;
	node.MsQ().V = (VectorDot(node.f.F,xi_v) + node.MsQ().Fy/2)/node.MsQ().Rho;
}