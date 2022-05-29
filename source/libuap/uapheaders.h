#ifndef _UAP_HEADERS_H_
#define _UAP_HEADERS_H_


// headers sequence
// 1. global defines
// 2. OS specific header
// 3. C/C++ standard librarys
// 4. UAP headers
// 5. private headers

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


// STL
#include <vector>



#include <uap.h>
#include <uapcomponent.h>
#include "uapinternal.h"


#endif //_UAP_HEADERS_H_