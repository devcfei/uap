#ifndef _UAP_RESULT_H_
#define _UAP_RESULT_H_

#ifndef _UAP_TYPES_H_
#error uapresult.h requires uaptypes.h to be included first
#endif



namespace uap
{

    // Global basic data type
    enum Result
    {
        R_SUCCESS = 0,
        R_ERROR,
        R_NOT_IMPL,
        R_INVALID_PARAMETERS,
        R_ERROR_LOAD_LIBRARY,
        R_FILE_NOT_EXIST,
        R_NO_SUCH_INTERFACE,
        R_NO_MEMORY,
        R_BUFFER_TOO_SMALL,
        R_NOT_FOUND,
        R_INTERNEL_FAILURE,
        R_END
    };

    // Global functions

} // @namespace uap

#endif //_UAP_RESULT_H_
