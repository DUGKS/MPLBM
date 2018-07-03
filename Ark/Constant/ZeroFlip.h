#ifndef _ARK_ZEROFLIP_H
#define _ARK_ZEROFLIP_H

//---------------------------LBM model--------------------------
#ifndef _ARK_SLBM_FLIP
#define _ARK_SLBM_FLIP "SLBM"
#define _ARK_LBM_FLIP _ARK_SLBM_FLIP
#endif

#ifndef _CASE_NAME_ARK
#define _CASE_NAME_ARK "ACSLBM"
#endif

// #ifndef _ARK_RLBM_FLIP
// #define _ARK_RLBM_FLIP "RLBM"
// #define _ARK_LBM_FLIP _ARK_RLBM_FLIP 
// #endif

// #ifndef _ARK_MRT_FLIP
// #define _ARK_MRT_FLIP "MRT"
// #define _ARK_LBM_FLIP _ARK_LBM_FLIP
// #endif
//-----------------------multiphase model--------------------
// #ifndef _ARK_PSEUDOP_FLIP
// #define _ARK_PSEUDOP_FLIP
// #endif

#ifndef _ARK_ALLENCAHN_FLIP
#define _ARK_ALLENCAHN_FLIP
#endif

// #ifndef _ARK_MOMENTUM_FLIP
// #define _ARK_MOMENTUM_FLIP
// #endif

#ifndef _ARK_ENDTIME_FLIP
#define _ARK_ENDTIME_FLIP
#endif

#ifndef _ARK_L2NORM_FLIP
#define _ARK_L2NORM_FLIP
#endif

#include "ZeroMacro.h"

#endif