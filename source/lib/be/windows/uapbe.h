#ifndef _UAPBE_H_
#define _UAPBE_H_

#include <windows.h>
#include <strsafe.h>
#include <tchar.h>
#include <stdarg.h>
#include <uap.h>
using namespace uap;


#ifdef UAPBE_EXPORTS  
#define DLL_EXPORTS _declspec( dllexport )  
#else  
#define DLL_EXPORTS _declspec(dllimport)  
#endif

extern "C" DLL_EXPORTS Result uapbeVPrint(Char* pszFormat, va_list vaList);

#endif //_UAPBE_H_
