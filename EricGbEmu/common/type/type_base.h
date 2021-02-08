#pragma once


// gen 3 type -- normal, save, un-save pointer
#define ERIC_GEN_POINTER_TYPE(T)        \
	typedef const T* const T##_sp;      \
	typedef T* const T##_p;             \
	typedef T* T##_usp;                 \
    typedef volatile T  v##T;         


typedef char                  es8;
ERIC_GEN_POINTER_TYPE(es8);

typedef unsigned char         eu8;
ERIC_GEN_POINTER_TYPE(eu8);

typedef unsigned short        eu16;
ERIC_GEN_POINTER_TYPE(eu16);

typedef unsigned long         eu32;
ERIC_GEN_POINTER_TYPE(eu32);

typedef unsigned long long    eu64;
ERIC_GEN_POINTER_TYPE(eu64);

#ifdef _UNICODE
#include <string.h>
typedef wchar_t               echar;
#else
typedef char                  echar;
#endif
ERIC_GEN_POINTER_TYPE(echar);


