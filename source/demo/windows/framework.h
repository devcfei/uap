#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_


#include <windows.h>
#include <tchar.h>

#include <uap.h>
#include <uapuiengine.h>


#include "app.h"

using namespace uap;

#if defined (_DEBUG)
#define TRACE(fmt, ...) uap::logPrint("demo.exe!" fmt, __VA_ARGS__)
#define ASSERT(_expr_)
#else
#define TRACE(fmt, ...) 
#define ASSERT(_expr_)
#endif



#define RESULT_CHECK(r, _message_) \
        if(!UAP_SUCCESS(r)) \
        { \
            TRACE( _message_ ## " failed! r = 0x%8.8x\n",r); \
            return r; \
        } 





#endif //@_FRAMEWORK_H_
