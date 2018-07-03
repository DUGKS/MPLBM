#include "LBMNameSpace.h"
#include <string>
using std::string;

string caseName;

namespace PF = PhaseFieldAC;


extern void update_Eq(Node2D &node);
//
void uniform()
{
	using PF::aPhi;
	using PF::bPhi;
	using PF::PhiL;
	using PF::PhiV;
	using PF::wI;
	using PF::radius;
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
double AnalyticalAC_Drop(double x,double y)
{
	using PF::aPhi;
	using PF::bPhi;
	using PF::PhiL;
	using PF::PhiV;
	using PF::wI;
	using PF::centerX;
	using PF::centerY;
	using PF::radius;
	int const slotL = centerX - 10;
	int const slotR = centerX + 10;

	double phi = 0.0;

	phi = 
	(
	0.5*(PhiL+PhiV) + 0.5*(-PhiL + PhiV)
	*tanh(2*(sqrt((x-centerX)*(x-centerX)+(y-centerY)*(y-centerY))-radius)/wI)
	);

	// if(sqrt((x-centerX)*(x-centerX) + (y-centerY)*(y-centerY)) > radius)
	// {
	// 	phi = PhiV;
	// }
	// else if(x > slotL && x < slotR && y < centerY)
	// {
	// 	phi = PhiV;
	// }
	// else
	// {
	// 	phi = PhiL;
	// }
	return phi;
}
double Sharingan(double const &xn,double const &yn)
{
	using PF::PhiL;
	using PF::PhiV;
	using PF::wI;
	using PF::centerX;
	using PF::centerY;
	using PF::radius;
	double phi = 0;
	double const sR = 212.5;
	double const dR = sR - 25;
	double xL = centerX - dR,yL = centerY;
	double xR = centerX + dR,yR = centerY;

	if
	(  
		sqrt((xn-xL)*(xn-xL) + (yn-yL)*(yn-yL))<sR
		 &&
		sqrt((xn-xR)*(xn-xR) + (yn-yR)*(yn-yR))<sR
	)
	{
		return PhiL;
	}
	xL = centerX-dR/2.0,yL = centerY + 1.732*dR/2.0;
	xR = centerX+dR/2.0,yR = centerY - 1.732*dR/2.0;
	if
	(  
		sqrt((xn-xL)*(xn-xL) + (yn-yL)*(yn-yL))<sR
		 &&
		sqrt((xn-xR)*(xn-xR) + (yn-yR)*(yn-yR))<sR
	)
	{
		return PhiL;
	}
	xL = centerX-dR/2.0,yL = centerY - 1.732*dR/2.0;
	xR = centerX+dR/2.0,yR = centerY + 1.732*dR/2.0;
	if
	(  
		sqrt((xn-xL)*(xn-xL) + (yn-yL)*(yn-yL))<sR
		 &&
		sqrt((xn-xR)*(xn-xR) + (yn-yR)*(yn-yR))<sR
	)
	{
		return PhiL;
	}

	return PhiV;
}
void Sharingan()
{
	using PF::aPhi;
	using PF::bPhi;
	using PF::PhiL;
	using PF::PhiV;
	using PF::wI;
	using PF::centerX;
	using PF::centerY;
	using PF::radius;

	LoopPS(Lx1,Ly1)
	{
		double const &xn = NodeArray[i][j].xn, &yn = NodeArray[i][j].yn;
		NodeArray[i][j].MsQ().Phi = Sharingan(xn,yn);
		if
		(
		sqrt((xn-centerX)*(xn-centerX) + (yn-centerY)*(yn-centerY))<10
		)
		{
			NodeArray[i][j].MsQ().Phi =  PhiV;
		}
		NodeArray[i][j].MsQ().Rho = aPhi*NodeArray[i][j].MsQ().Phi + bPhi;
		NodeArray[i][j].MsQ().U   = 
		-U0*PI/ChLength*(yn-centerY);
		NodeArray[i][j].MsQ().V   = 
	    U0*PI/ChLength*(xn-centerX);

		NodeArray[i][j].MsQ().p   = p0;
		update_Eq(NodeArray[i][j]);
		for(int k = 0;k < Q;++k)
		{
			NodeArray[i][j].h.F[k] = NodeArray[i][j].h.Eq[k];
			NodeArray[i][j].f.F[k] = NodeArray[i][j].f.Eq[k];
		}
	}
}
void AC_ZalesakDisk()
{
	using PF::aPhi;
	using PF::bPhi;
	using PF::PhiL;
	using PF::PhiV;
	using PF::wI;
	using PF::centerX;
	using PF::centerY;
	using PF::radius;

	LoopPS(Lx1,Ly1)
	{
		double const &xn = NodeArray[i][j].xn, &yn = NodeArray[i][j].yn;
		NodeArray[i][j].MsQ().Phi = AnalyticalAC_Drop(xn,yn);
		NodeArray[i][j].MsQ().Rho = aPhi*NodeArray[i][j].MsQ().Phi + bPhi;
		NodeArray[i][j].MsQ().U   = 
		-U0*PI/ChLength*(yn-centerY);
		NodeArray[i][j].MsQ().V   = 
	    U0*PI/ChLength*(xn-centerX);

		NodeArray[i][j].MsQ().p   = p0;
		update_Eq(NodeArray[i][j]);
		for(int k = 0;k < Q;++k)
		{
			NodeArray[i][j].h.F[k] = NodeArray[i][j].h.Eq[k];
			NodeArray[i][j].f.F[k] = NodeArray[i][j].f.Eq[k];
		}
	}
}
void AC_Smoothed()
{
	caseName = __func__;
	using PF::aPhi;
	using PF::bPhi;
	using PF::PhiL;
	using PF::PhiV;
	using PF::wI;
	using PF::radius;
	LoopPS(Lx1,Ly1)
	{
		NodeArray[i][j].MsQ().Phi = AnalyticalAC_Drop(NodeArray[i][j].xn,NodeArray[i][j].yn);
		NodeArray[i][j].MsQ().Rho = aPhi*NodeArray[i][j].MsQ().Phi + bPhi;

		double &xn = NodeArray[i][j].xn, &yn = NodeArray[i][j].yn;
		NodeArray[i][j].MsQ().U   = 
		-U0*sin(4*PI*xn/ChLength)*sin(4*PI*yn/ChLength);
		NodeArray[i][j].MsQ().V   = 
	    -U0*cos(4*PI*xn/ChLength)*cos(4*PI*yn/ChLength);

		NodeArray[i][j].MsQ().p   = p0;
		update_Eq(NodeArray[i][j]);
		for(int k = 0;k < Q;++k)
		{
			NodeArray[i][j].h.F[k] = NodeArray[i][j].h.Eq[k];
			NodeArray[i][j].f.F[k] = NodeArray[i][j].f.Eq[k];
		}
	}
}
void AC_ShearFlow_PRE2016Ren()
{
	caseName = __func__;
	using PF::aPhi;
	using PF::bPhi;
	using PF::PhiL;
	using PF::PhiV;
	using PF::wI;
	using PF::radius;
	LoopPS(Lx1,Ly1)
	{
		double const &xn = NodeArray[i][j].xn, &yn = NodeArray[i][j].yn;
		NodeArray[i][j].MsQ().Phi = AnalyticalAC_Drop(NodeArray[i][j].xn,NodeArray[i][j].yn);
		NodeArray[i][j].MsQ().Rho = aPhi*NodeArray[i][j].MsQ().Phi + bPhi;

	
		NodeArray[i][j].MsQ().U   = 
		U0*PI*sin(PI*xn/ChLength)*cos(PI*yn/ChLength);
		NodeArray[i][j].MsQ().V   = 
		-U0*PI*cos(PI*xn/ChLength)*sin(PI*yn/ChLength);

		// NodeArray[i][j].MsQ().U   = 
		// U0*sin(PI*xn/ChLength)*sin(PI*xn/ChLength)*sin(2*PI*yn/ChLength);
		// NodeArray[i][j].MsQ().V   = 
		// -U0*sin(PI*yn/ChLength)*sin(PI*yn/ChLength)*sin(2*PI*xn/ChLength);

		NodeArray[i][j].MsQ().p   = p0;
		update_Eq(NodeArray[i][j]);
		for(int k = 0;k < Q;++k)
		{
			NodeArray[i][j].h.F[k] = NodeArray[i][j].h.Eq[k];
			NodeArray[i][j].f.F[k] = NodeArray[i][j].f.Eq[k];
		}
	}
}
void AC_DiagTrans()
{
	caseName = __func__;
	using PF::aPhi;
	using PF::bPhi;
	using PF::PhiL;
	using PF::PhiV;
	using PF::wI;
	using PF::radius;
	LoopPS(Lx1,Ly1)
	{
		double const &xn = NodeArray[i][j].xn, &yn = NodeArray[i][j].yn;
		NodeArray[i][j].MsQ().Phi = AnalyticalAC_Drop(xn,yn);
		NodeArray[i][j].MsQ().Rho = aPhi*NodeArray[i][j].MsQ().Phi + bPhi;
		NodeArray[i][j].MsQ().U   = U0;
		NodeArray[i][j].MsQ().V   = U0;
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
	using PF::aPhi;
	using PF::bPhi;
	using PF::PhiL;
	using PF::PhiV;
	using PF::wI;
	using PF::radius;
	LoopPS(Lx1,Ly1)
	{
		//NodeArray[i][j].Rho = 0.5*(Rho_liquid + Rho_gas) + 0.5*(-Rho_liquid + Rho_gas)
		// 						*tanh(2*(sqrt((i-64)*(i-64)+(j-64)*(j-64))-radius)/5.0);
		//NodeArray[i][j].Rho = 0.3*(Rho_liquid + Rho_gas) + (i+j)/1000.0;
		NodeArray[i][j].MsQ().Phi = AnalyticalAC_Drop(i,j);
		NodeArray[i][j].MsQ().Rho = aPhi*NodeArray[i][j].MsQ().Phi + bPhi;
		NodeArray[i][j].MsQ().U   = 0;
		NodeArray[i][j].MsQ().V   = 0;
		NodeArray[i][j].MsQ().p   = p0;
		update_Eq(NodeArray[i][j]);
		for(int k = 0;k < Q;++k)
		{
			NodeArray[i][j].h.F[k] = NodeArray[i][j].h.Eq[k];
			NodeArray[i][j].f.F[k] = NodeArray[i][j].f.Eq[k];
		}
	}
}
void selfCheck()
{
	#if defined _ARK_PSEUDOP_FLIP && defined _ARK_ALLENCAHN_FLIP
	#error "multiphase model collision"
	#endif
	//
	#if defined _ARK_MRT_FLIP && defined _ARK_SLBM_FLIP
	#error "LBM model collision"
	#endif

	if(PhaseFieldAC::iT%10 != 0 )
	{
		cout <<"error : EndStep%10 != 0, EndStep = "<<EndStep<<nl;
		exit(-1);
	}
}