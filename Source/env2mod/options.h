#ifndef OPTIONS_H_DEFINED
#define OPTIONS_H_DEFINED

#include "options_common.h"

//*** uncomment the following two lines to force all versions to be beta
//#undef pp_BETA
//#define pp_BETA

//*** define env2mod title

#ifdef pp_BETA
#define PROGVERSION "Test"
#else
#define PROGVERSION "0.1"
#endif

#endif
