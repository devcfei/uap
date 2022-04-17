#ifndef _UAP_LOG_H_
#define _UAP_LOG_H_


#ifndef _UAP_RESULT_H_
#error uaplog.h requires uapresult.h to be included first
#endif

namespace uap
{

// Global functions

Result logPrint(Char* format, ...);

};



#endif //_UAP_LOG_H_