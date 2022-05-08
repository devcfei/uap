#include <uap.h>
#include "uapheaders.h"
#include "uapinternal.h"
namespace uap
{

// Global functions

Result logPrint(Char* format, ...)
{
    Result r = R_OK;


    //TRACE("logPrint\n");
    va_list pArgs;
    va_start(pArgs, format);
    r = global_Pfn.pfn_vPrint(format, pArgs);
    va_end(pArgs);

    return r;
}

};
