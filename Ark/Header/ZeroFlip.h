#ifndef _ARK_SLBM_FLIP
#define _ARK_SLBM_FLIP

#ifndef _CASE_NAME_ARK
#define _CASE_NAME_ARK "ACLBM"//_LBM
#endif

#define LoopPS(NUMX,NUMY)	\
for(int i=1;i<NUMX;++i)		\
for(int j=1;j<NUMY;++j)

#define nl '\n'

#ifndef _PRINT_ERROR_MSG_FLIP
#define _PRINT_ERROR_MSG_FLIP  cout<<"File : "<<__FILE__<<"  Line : "\
<<__LINE__<<"  fun : "<<__func__<<'\n';
#endif

double const PI = 3.141592653589793;

double const Tiny = 1E-15;
#endif