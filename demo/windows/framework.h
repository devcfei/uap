#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_


#include <windows.h>
#include <strsafe.h>
#include <tchar.h>



// uap
#define MODULE_NAME "demo"
#include <uap.h>
#include <uapuiengine.h>
using namespace uap;


#include <IconsForkAwesome.h>

#include "app.h"






#define INFO(_message_, ...) \
        do{ \
            ILogTrace* p= App::getLogTrace(); \
            if(p) \
                p->output(LT_INFO, _message_, __VA_ARGS__ ); \
        } while(0)


#define WARN(_message_, ...) \
        do{ \
            ILogTrace* p= App::getLogTrace(); \
            if(p) \
                p->output(LT_WARN, _message_, __VA_ARGS__ ); \
        } while(0)



#define VERIFY(r, _message_) \
        do{ \
            ILogTrace* p= App::getLogTrace(); \
            if(!UAP_SUCCESS(r)) \
            { \
                if(p) \
                    p->output(LT_ERROR, _message_ ## " failed! r = 0x%8.8x\n",r); \
                return r; \
            } \
            else \
            { \
                if(p) \
                    p->output(LT_INFO, _message_ ## " success! r = 0x%8.8x\n",r); \
            } \
        }while(0)


#endif //@_FRAMEWORK_H_
