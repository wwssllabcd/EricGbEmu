#pragma once


#ifdef _UNICODE
#include <Tchar.h>
#define _ET(str)                _T(str)
#define TFOPEN                  _wfopen_s
#define t_vprintf               _vtprintf
#define t_vfprintf              _vftprintf


#else
#define _ET(str)                (str)
#define TFOPEN                  fopen_s
#define t_vprintf               vprintf
#define t_vfprintf              vfprintf
#endif 





