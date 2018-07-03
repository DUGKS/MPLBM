#include "LBMNameSpace.h"
#include "nonidealEoS.h"
//
double const K = 0.1;

extern double updatePhi_x(int i,int j);

extern double updatePhi_y(int i,int j);

void updateSourcePP(Node2D &node)
{
	double pIdeal = node.MsQ().Rho*RT;
	//node.MsQ().p = K*VanderWaals(node.Rho);
	node.MsQ().p = CarnahanStarling(node.MsQ().Rho);
	//node.MsQ().p = K * reduced_mKM(node.Rho);
	node.MsQ().scG = (node.MsQ().p > pIdeal) - (node.MsQ().p < pIdeal);
	node.MsQ().Phi = sqrt(2*(node.MsQ().p - pIdeal)/(node.MsQ().scG));
}
void updateForce(Node2D &node)
{
	node.MsQ().Fx = -node.MsQ().scG * node.MsQ().Phi*updatePhi_x(node.in,node.jn);
	node.MsQ().Fy = -node.MsQ().scG * node.MsQ().Phi*updatePhi_y(node.in,node.jn);
}