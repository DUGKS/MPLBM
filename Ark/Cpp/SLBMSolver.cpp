#include "LBMNameSpace.h"
#include <omp.h>

int const ThreadNum = omp_get_max_threads();
//
double ResidualPer1k = 1.0;


extern void Output_flowfield(int step);

extern void updateResidual();

extern void Output_MidxP();

extern void Output_MidyP();

//--------------------------------------------

extern void update_Eq(Node2D &node);

extern void MacroVars(Node2D &node);

extern void Collision(Node2D &node);

extern void Stream(Node2D &node);

//----------------------------------------------
//extern void updatePseudoPsi(Node2D &node);

extern void updateSource(Node2D &node);

extern void Output_SumRho(int step);

extern void Output_Residual(int step,double Residual);
//----------------------------------------------

void updateResidual();

void updateSumRho();

void SLBMSolver()
{
	Output_flowfield(step);

	cout << "iteration start    ThreadNum : "<<ThreadNum<<nl;

  omp_set_num_threads(ThreadNum);
  #pragma omp parallel
  {
	while(step < EndStep)
	//while(ResidualPer1k > RESIDUAL)
	{
		#pragma omp for schedule(guided) 
		LoopPS(Lx1,Ly1)
		{
			update_Eq(NodeArray[i][j]);
//			update_So(NodeArray[i][j]);
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
		#pragma omp for schedule(guided)
		LoopPS(Lx1,Ly1)
		{
			updateSource(NodeArray[i][j]);
		}
		#pragma omp single
		{
			++step;
			if(step%ConvergeStep == 0)
			{
				updateResidual();
				Output_SumRho(step);
				Output_Residual(step,ResidualPer1k);
				if(step%writeFileStep == 0)
				Output_flowfield(step);
			}
		}
	}
	Output_MidxP();
	Output_MidyP();
  }
}
