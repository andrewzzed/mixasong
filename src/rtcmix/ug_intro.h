/* RTcmix  - Copyright (C) 2004  The RTcmix Development Team
   See ``AUTHORS'' for a list of contributors. See ``LICENSE'' for
   the license to this software and for a DISCLAIMER OF ALL WARRANTIES.
*/
#ifndef _UG_INTRO_H_ 
#define _UG_INTRO_H_ 1
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>        /* for NULL */

void ug_intro(void);       /* called by RTcmix main and RTcmix.C */


#include "rtcmix_types.h"

void addfunc(char *func_label, Float (*func_ptr_number)(),
   String (*func_ptr_string)(), Handle (*func_ptr_handle)(),
   RTcmixType return_type, int legacy);


#define UG_INTRO(flabel, func) \
   { \
      extern Float func(); \
      addfunc(flabel, func, NULL, NULL, FloatType, 1); \
   }

#define UG_INTRO_FLOAT_RETURN(flabel, func) \
   { \
      extern Float func(); \
      addfunc(flabel, func, NULL, NULL, FloatType, 0); \
   }

#define UG_INTRO_STRING_RETURN(flabel, func) \
   { \
      extern String func(); \
      addfunc(flabel, NULL, func, NULL, StringType, 0); \
   }

#define UG_INTRO_HANDLE_RETURN(flabel, func) \
   { \
      extern Handle func(); \
      addfunc(flabel, NULL, NULL, func, HandleType, 0); \
   }

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* _UG_INTRO_H_ */
