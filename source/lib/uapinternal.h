#ifndef _UAP_INTERNAL_H_
#define _UAP_INTERNAL_H_

namespace uap
{

// Global functions

typedef Result (*PFN_beInitialize)();
typedef Result (*PFN_vPrint)(Char* format, va_list vaList);
typedef Result (*PFN_GetInterface)(const Uuid &rUuid, IUnknown** ppiUnknown);

struct uapPfn
{
    PFN_beInitialize pfn_beInitialize;
    PFN_vPrint pfn_vPrint;
    PFN_GetInterface pfn_GetInterface;
};





extern struct uapPfn global_Pfn;


Result TraceMessage(LPCTSTR pszFormat, ...);



};




#if defined (_DEBUG)
#define TRACE(fmt, ...) TraceMessage(TEXT("uap.lib!") fmt, __VA_ARGS__)
#define ASSERT(_expr_)
#else
#define TRACE(fmt, ...) 
#define ASSERT(_expr_)
#endif


#endif //_UAP_INTERNAL_H_