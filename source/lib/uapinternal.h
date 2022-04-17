#ifndef _UAP_INTERNAL_H_
#define _UAP_INTERNAL_H_

namespace uap
{

// Global functions
typedef Result (*PFN_vPrint)(Char* format, va_list vaList);

struct uapPfn
{
    PFN_vPrint pfn_vPrint;
};





extern struct uapPfn global_Pfn;


Result TraceMessage(LPCTSTR pszFormat, ...);



};




#if defined (_DEBUG)
#define TRACE(fmt, ...) TraceMessage(TEXT("uap.lib!") fmt, __VA_ARGS__)
#else
#define TRACE(fmt, ...) 
#endif


#endif //_UAP_INTERNAL_H_