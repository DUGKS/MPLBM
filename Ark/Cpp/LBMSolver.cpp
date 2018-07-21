#include "LBMNameSpace.h"
#include <omp.h>

int const ThreadNum = omp_get_max_threads();
//
double ResidualPer1k = 1.0;


extern void Output_flowfield(int step);

extern void updateResidual();

extern void Output_Midx(int);

extern void Output_Midy(int);

extern void Output_Diag(int);

//--------------------------------------------

extern void update_Eq(Node2D &node);

extern void update_So(Node2D &node);

extern void MacroVars(Node2D &node);

extern void Collision(Node2D &node);

extern void Stream(Node2D &node);

//----------------------------------------------
//extern void updatePseudoPsi(Node2D &node);

extern void updateSourcePF(Node2D &node);

extern void updateSourcePP(Node2D &node);

extern void updateSumRho(int const &step);

extern void Output_L2Norm(int step,double &L2Norm);
//----------------------------------------------

void updateResidual();

void updateSumRho();

void LBMSolver()
{
	Output_flowfield(step);

	cout << "iteration start    ThreadNum : "<<ThreadNum<<nl;

  omp_set_num_threads(ThreadNum);
  #pragma omp parallel
  {
	//while(step < EndStep)
	while(ResidualPer1k > RESIDUAL)
	{
		#pragma omp for schedule(guided) 
		LoopPS(Lx1,Ly1)
		{
			update_Eq(NodeArray[i][j]);
			update_So(NodeArray[i][j]);
		}
		#pragma omp for schedule(guided)
		LoopPS(Lx1,Ly1)
		{
			Collision(NodeArray[i][j]);
		}
		#pragma omp for schedule(guided)
		LoopPS(Lx1,Ly1)
		{
			Stream(NodeArray[i][j]);
		}
		#pragma omp for schedule(guided)
		LoopPS(Lx1,Ly1)
		{
			MacroVars(NodeArray[i][j]);
		}
		//!------------------Allen-Cahn------------------
		#if defined _ARK_ALLENCAHN_FLIP
		#pragma omp for schedule(guided)
		LoopPS(Lx1,Ly1)
		{
			updateSourcePF(NodeArray[i][j]);
		}
		#endif
		//!-----------------pseudopotential--------------
		#ifdef _ARK_PSEUDOP_FLIP
		LoopPS(Lx1,Ly1)
		{
			updateSourcePP(NodeArray[i][j]);
		}
		#endif

		#pragma omp single
		{
			++step;
			if(step%ConvergeStep == 0)
			{
				updateResidual();
				updateSumRho(step);
				#ifdef _ARK_L2NORM_FLIP
				Output_L2Norm(step,L2Norm);
				#endif
			}
		}
	}
	Output_flowfield(step);
	// Output_Midx(step);
	// Output_Midy(step);
	Output_Diag(step);
  }
}
