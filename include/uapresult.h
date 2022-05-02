#ifndef _UAP_RESULT_H_
#define _UAP_RESULT_H_


#ifndef _UAP_BASE_H_
#error uapresult.h requires uapbase.h to be included first
#endif

namespace uap
{

// Global basic data type
enum Result
{
    R_OK=0,
    R_ERROR=1,
    R_INVALID_PARAMETERS=100,
    R_NOT_IMPLEMENTED,
    R_ERROR_LOAD_LIBRARY,
    R_FILE_NOT_EXIST,
    R_NO_SUCH_INTERFACE,
    R_NO_MEMORY,
};

// Global functions


};



#endif //_UAP_RESULT_H_
