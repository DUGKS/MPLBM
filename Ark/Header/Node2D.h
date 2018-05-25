#ifndef _NODE2D_RLBM_H
#define _NODE2D_RLBM_H

#include "DVDF.h"

class MacroQuantity
{
public:
	double Phi = 0.0,Phi_x = 0.0,Phi_y = 0.0,laplacianPhi = 0.0;
	double prevPhiU = 0.0,prevPhiV = 0.0;
	double Rho = 0.0,Rho_x = 0.0,Rho_y = 0.0;
	double U = 0.0,V = 0.0;
	double Fx = 0.0,Fy = 0.0;
	double p = 0.0;
//	double scG = 0.0,PseudoP = 0.0;
	double Rho_1K = 0.0,U_1K = 0.0,V_1K = 0.0;
//
	inline double SqrtPhi(){return Phi_x*Phi_x + Phi_y*Phi_y;}
	inline double SqrtUV(){return U*U+V*V;}
};
class Node2D
{

public:
	friend class DVDF;
	friend class MacroV;
//
	Node2D();
	Node2D(const Node2D &rhs);
	Node2D& operator=(const Node2D &rhs);
	~Node2D();
//
	enum {Ghost,Inner} NodeType;
	Node2D *ShadowN = nullptr;
//
	int in = 0,jn = 0; 
	double xn = 0.0,yn = 0.0;
//---------------discrete velocity distribution function-----------------
	DVDF h;
	DVDF f;
//----------------macroscopic quantity--------------------
	MacroQuantity * __restrict__ msq = nullptr;
//
	inline 
	MacroQuantity& MsQ(){return *msq;}

//private:
	int *use = nullptr;
};
#endif