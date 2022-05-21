#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_


#include <windows.h>
#include <tchar.h>



// uap
#define MODULE_NAME "demo"
#include <uap.h>
#include <uapuiengine.h>
using namespace uap;


#include "app.h"





#define RESULT_CHECK(r, _message_) \
        if(!UAP_SUCCESS(r)) \
        { \
            UAP_TRACE( _message_ ## " failed! r = 0x%8.8x\n",r); \
            return r; \
        } 





#endif //@_FRAMEWORK_H_
