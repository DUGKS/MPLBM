#include "LBMNameSpace.h"

namespace PF = PhaseFieldAC;
using PF::aPhi;
using PF::bPhi;
using PF::PhiL;
using PF::PhiV;
using PF::wI;
using PF::radius;

extern void update_Eq(Node2D &node);
//
void uniform()
{
	for(int i = 1;i < Lx1;++i)
	for(int j = 1;j < Ly1;++j)
	{
		NodeArray[i][j].MsQ().Phi = Rho0;
		NodeArray[i][j].MsQ().Rho = aPhi*Rho0 + bPhi;
		NodeArray[i][j].MsQ().U   = U0;
		NodeArray[i][j].MsQ().V   = V0;
		NodeArray[i][j].MsQ().p   = p0;
		update_Eq(NodeArray[i][j]);
		for(int k = 0;k < Q;++k)
		{
			NodeArray[i][j].h.F[k] = NodeArray[i][j].h.Eq[k];
			NodeArray[i][j].f.F[k] = NodeArray[i][j].f.Eq[k];
		}
	}
}
void AC_Drop()
{
	LoopPS(Lx1,Ly1)
	{
		//NodeArray[i][j].Rho = 0.5*(Rho_liquid + Rho_gas) + 0.5*(-Rho_liquid + Rho_gas)
		// 						*tanh(2*(sqrt((i-64)*(i-64)+(j-64)*(j-64))-radius)/5.0);
		//NodeArray[i][j].Rho = 0.3*(Rho_liquid + Rho_gas) + (i+j)/1000.0;
		NodeArray[i][j].MsQ().Phi = 0.5*(PhiL+PhiV) + 0.5*(-PhiL + PhiV)
		 						*tanh(2*(sqrt((i-64)*(i-64)+(j-64)*(j-64))-radius)/wI);
		NodeArray[i][j].MsQ().Rho = aPhi*NodeArray[i][j].MsQ().Phi + bPhi;
		NodeArray[i][j].MsQ().U   = U0;
		NodeArray[i][j].MsQ().V   = V0;
		NodeArray[i][j].MsQ().p   = p0;
		update_Eq(NodeArray[i][j]);
		for(int k = 0;k < Q;++k)
		{
			NodeArray[i][j].h.F[k] = NodeArray[i][j].h.Eq[k];
			NodeArray[i][j].f.F[k] = NodeArray[i][j].f.Eq[k];
		}
	}
}