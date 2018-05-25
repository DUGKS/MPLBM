#include "LBMNameSpace.h"
//
Node2D **NodeArray = nullptr;

int step = 0;

double SumRho = 0.0;
//

extern void uniform();

extern void AC_Drop();

extern void SLBMSolver();

void AllocateResource();

void DeallocateResource();

void MeshConstruct();

void ShadowNodeConstruct();

//---------------------Output-------------------

extern void OutputCase();

int main()
{
	OutputCase();
//	
	AllocateResource();
	MeshConstruct();
	ShadowNodeConstruct();
//
//	uniform();

	AC_Drop();

	SLBMSolver();
	DeallocateResource();
}
//
void AllocateResource()
{
	AllocateArk(NodeArray,Lx2,Ly2);
}
void DeallocateResource()
{
	DeallocateArk(NodeArray,Lx2,Ly2);
}
void MeshConstruct()
{
	for(int i = 0;i < Lx2;++i)
	for(int j = 0;j < Ly2;++j)
	{
		NodeArray[i][j].xn = i - 1;
		NodeArray[i][j].yn = j - 1;
		NodeArray[i][j].in = i;
		NodeArray[i][j].jn = j;
	}
	for(int i = 0;i < Lx2;++i)
	for(int j = 0;j < Ly2;++j)
	{
		if(0 ==  i || 0 == j || Lx1 == i || Ly1 == j)
		{
			NodeArray[i][j].NodeType = Node2D::Ghost;
		}
		else
		{
			NodeArray[i][j].NodeType = Node2D::Inner;
		}
	}
}
void ShadowNodeConstruct()
{
	for(int i = 1;i < Lx1;++i)
	{
		NodeArray[i][0] = NodeArray[i][Ly];
		NodeArray[i][Ly1] = NodeArray[i][1];
	}
	for(int j = 1;j < Ly1;++j)
	{
		NodeArray[0][j] = NodeArray[Lx][j];
		NodeArray[Lx1][j] = NodeArray[1][j];
	}
	NodeArray[0][0]      = NodeArray[Lx][Ly];
	NodeArray[0][Ly1]    = NodeArray[Lx][1];
	NodeArray[Lx1][0]    = NodeArray[1][Ly];
	NodeArray[Lx1][Ly1]  = NodeArray[1][1];
}