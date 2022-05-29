#include "uapheaders.h"

namespace uap
{
    static const Char *g_szResult[R_END]{
        "R_SUCCESS",
        "R_ERROR",
        "R_NOT_IMPL",
        "R_INVALID_PARAMETERS",
        "R_ERROR_LOAD_LIBRARY",
        "R_FILE_NOT_EXIST",
        "R_NO_SUCH_INTERFACE",
        "R_NO_MEMORY",
        "R_BUFFER_TOO_SMALL",
        "R_NOT_FOUND",
        "R_INTERNEL_FAILURE",
    };

    const Char *uapGetResultString(Result r)
    {
        if (r < R_END)
        {
            return g_szResult[r];
        }
        return "Result code undefined";
    }

} // @namespace uap
