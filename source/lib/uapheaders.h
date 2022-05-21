#ifndef _UAP_HEADERS_H_
#define _UAP_HEADERS_H_


#define MODULE_NAME "uap"

#if defined(_WIN32)

#include <windows.h>
#include <strsafe.h>
#include <tchar.h>
#include <stdarg.h>
#include <crtdbg.h>

#elif defined(__linux__)

#include <stdio.h>

#else

#endif

#include <uap.h>
#include "uapinternal.h"
using namespace uap;


#endif //_UAP_HEADERS_H_