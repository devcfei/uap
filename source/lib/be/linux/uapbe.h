#ifndef _UAPBE_H_
#define _UAPBE_H_

#include <stdio.h>
#include <stdarg.h>
#include <uap.h>
using namespace uap;




extern "C" Result uapbeVPrint(Char* pszFormat, va_list vaList);

#endif //_UAPBE_H_
