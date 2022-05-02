#ifndef _UAPBE_H_
#define _UAPBE_H_

#include <windows.h>
#include <strsafe.h>
#include <tchar.h>
#include <stdarg.h>
#include <uap.h>
#include "uapbedefs.h"
#include "uapbeattributesimpl.h"

using namespace uap;

#ifdef UAPBE_EXPORTS
#define DLL_EXPORTS _declspec(dllexport)
#else
#define DLL_EXPORTS _declspec(dllimport)
#endif

// Internel functions
Result TraceMessage(LPCTSTR pszFormat, ...);

// Export functions
extern "C" DLL_EXPORTS Result uapbeInitialize();
extern "C" DLL_EXPORTS Result uapbeVPrint(Char *pszFormat, va_list vaList);
extern "C" DLL_EXPORTS Result uapbeGetInterface(const uap::Uuid &uuid, uap::IUnknown **ppiUnknown);

#endif //_UAPBE_H_
