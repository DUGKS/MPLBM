#include "LBMNameSpace.h"

using PhaseFieldAC::PhiL;
using PhaseFieldAC::PhiV;
using PhaseFieldAC::wI;

inline double SourcePhi(double phi)
{
	return -4*(phi-PhiL)*(phi-PhiV)/(wI*(PhiL-PhiV));
}

inline double ChemicalPotential(double Phi,double laplacianPhi)
{
	return
	(
	2*PhaseFieldAC::Beta*(Phi-PhiL)*(Phi-PhiV)*(2*Phi-PhiL-PhiV)
	-PhaseFieldAC::Kappa*laplacianPhi
	);
}

double const 

apsi = 4,

bpsi = 1;

//

double updatePhi_x(int i,int j)
{
	return
	(apsi*
	(
		NodeArray[i+1][j].MsQ().Phi - NodeArray[i-1][j].MsQ().Phi
	)
+   bpsi*
	(
		NodeArray[i+1][j+1].MsQ().Phi - NodeArray[i-1][j+1].MsQ().Phi
	+	NodeArray[i+1][j-1].MsQ().Phi - NodeArray[i-1][j-1].MsQ().Phi
	))/12;
}
double updatePhi_y(int i,int j)
{
	return
	(apsi*
	(
		NodeArray[i][j+1].MsQ().Phi - NodeArray[i][j-1].MsQ().Phi
	)
+	bpsi*
	(
		NodeArray[i+1][j+1].MsQ().Phi - NodeArray[i+1][j-1].MsQ().Phi
	+	NodeArray[i-1][j+1].MsQ().Phi - NodeArray[i-1][j-1].MsQ().Phi
	))/12;
}
double updatelaplacianPhi(int i,int j)
{
	return
	(
		apsi*(
				NodeArray[i][j+1].MsQ().Phi + NodeArray[i][j-1].MsQ().Phi
			 +	NodeArray[i+1][j].MsQ().Phi + NodeArray[i-1][j].MsQ().Phi
			 )
	+	bpsi*(
				NodeArray[i+1][j+1].MsQ().Phi + NodeArray[i+1][j-1].MsQ().Phi
			 +	NodeArray[i-1][j+1].MsQ().Phi + NodeArray[i-1][j-1].MsQ().Phi
			 )
	-	20*NodeArray[i][j].MsQ().Phi
	)/6;

}
void SourceMomentum(Node2D &node)
{
	node.MsQ().Rho_x = PhaseFieldAC::aPhi*node.MsQ().Phi_x;
	node.MsQ().Rho_y = PhaseFieldAC::aPhi*node.MsQ().Phi_y;
	double F = ChemicalPotential(node.MsQ().Phi,node.MsQ().laplacianPhi);
	node.MsQ().Fx = F*node.MsQ().Phi_x;
	node.MsQ().Fy = F*node.MsQ().Phi_y;
}
void updateSource(Node2D &node)
{
	node.MsQ().Phi_x = updatePhi_x(node.in,node.jn);
	node.MsQ().Phi_y = updatePhi_y(node.in,node.jn);
//	cout <<node.MsQ().Phi_x<<"    "<<node.MsQ().Phi_y<<nl;
	node.MsQ().laplacianPhi = updatelaplacianPhi(node.in,node.jn);
//
	SourceMomentum(node);
//
	double PhiU_t = 0.0,PhiV_t = 0.0;
	PhiU_t = (node.MsQ().Phi*node.MsQ().U - node.MsQ().prevPhiU)/RT;
	PhiV_t = (node.MsQ().Phi*node.MsQ().V - node.MsQ().prevPhiV)/RT;
	node.MsQ().prevPhiU = node.MsQ().Phi*node.MsQ().U;
	node.MsQ().prevPhiV = node.MsQ().Phi*node.MsQ().V;
//
	double L = sqrt(node.MsQ().SqrtPhi());
	setZero(L);
//
//
	if(L != 0)
	{
		node.MsQ().Phi_x = SourcePhi(node.MsQ().Phi)*node.MsQ().Phi_x/L + PhiU_t;
		node.MsQ().Phi_y = SourcePhi(node.MsQ().Phi)*node.MsQ().Phi_y/L + PhiV_t;
	}


}