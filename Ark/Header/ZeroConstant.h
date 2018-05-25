#ifndef _ZERO_CONSTANT_H
#define _ZERO_CONSTANT_H
//
#include "ZeroFlip.h"
#include <cmath>
#include "D2Q9.h"
using D2Q9::Q;
//-----------------Mesh------------------
int const 

nD = 2,//number of dimension

Lx = 128,

Ly = 128,

Lx1 = Lx + 1,

Ly1 = Ly + 1,

Lx2 = Lx + 2,

Ly2 = Ly + 2;

double const 

ChLength = 128.0;

double const

Dt = 1,

hDt = 0.5*Dt;

//-------------dimensionless parameter-------------------

double const

T0 = 1.0/3.0,

R0 = 1.0,

RT = R0*T0,

Lambda0 = 1.0/(2*RT),

Rho0 = 1,//CS 4.5435E-2,

U0 = 0.0,

V0 = 0.0,

p0 = 1.0,

Ma = U0/sqrt(RT),

Re = 0,

Mu0 = Rho0*U0*ChLength/Re,

// Nu0 = Mu0/Rho0,

Nu0 = 0.1,

Tau0 = 0.5 + Nu0/RT;

#include "ZeroNamespace.h"

//------------------------output control------------------
int const 

EndStep = 10000000,

ConvergeStep = 1000,

writeFileStep = 50000;

double const 

RESIDUAL = 1E-8;
#endif