#ifndef _COMMON_H_
#define _COMMON_H_

#define MODULE_NAME "application"


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
#include <map>
#include <fstream>
#include <ctime>


// toml11
#include <toml.hpp>


// uap
#include <uap.h>
#include <uapcomponent.h>
#include "fileloggerimpl.h"
#include "applicationimpl.h"
#include "eventimpl.h"
#include "tomlimpl.h"
#include "attributesimpl.h"
#include "logtraceimpl.h"




#endif // _COMMON_H_




