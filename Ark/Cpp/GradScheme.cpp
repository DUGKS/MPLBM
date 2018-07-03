#include "LBMNameSpace.h"


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