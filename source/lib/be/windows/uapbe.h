#ifndef _UAPBE_H_
#define _UAPBE_H_

// windows
#include <windows.h>
#include <strsafe.h>
#include <tchar.h>

// stdc
#include <stdarg.h>

// stl
#include <vector>
#include <map>
#include <fstream>

// toml11

#include <toml.hpp>


// uap
#define MODULE_NAME "uapbe"
#include <uap.h>
using namespace uap;

#include "uapbeappimpl.h"
#include "uapbeattributesimpl.h"
#include "uaplogtraceimpl.h"
#include "uaptomlimpl.h"




#ifdef UAPBE_EXPORTS
#define DLL_EXPORTS _declspec(dllexport)
#else
#define DLL_EXPORTS _declspec(dllimport)
#endif

// Internel functions
Result TraceMessage(LPCTSTR pszFormat, ...);


// Export functions
extern "C" DLL_EXPORTS Result uapbeInitialize();
extern "C" DLL_EXPORTS Result uapbeCreateApplication(IApplication** ppiApp);

#endif //_UAPBE_H_
