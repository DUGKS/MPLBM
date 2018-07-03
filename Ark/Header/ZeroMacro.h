#ifndef _ARK_MACRO_H
#define _ARK_MACRO_H

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