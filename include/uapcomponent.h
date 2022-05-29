#ifndef _UAP_COMPONENT_
#define _UAP_COMPONENT_

#ifndef _UAP_H_
#error uapcomponent.h requires uap.h to be included first
#endif

#if defined(_WIN32)
#ifdef COMPONENT_EXPORTS
#define DLL_EXPORTS _declspec(dllexport)
#else
#define DLL_EXPORTS _declspec(dllimport)
#endif

#elif defined(__linux__)

#define DLL_EXPORTS

#endif

namespace uap
{
    // Component functions
    typedef Result (*PFN_RegisterComponent)(const Uuid *iidArr, Ulong *count);
    typedef Result (*PFN_CreateInstance)(const Uuid &iid, void **ppv);

    extern "C" DLL_EXPORTS Result RegisterComponent(const Uuid *iidArr, Ulong *count);
    extern "C" DLL_EXPORTS Result CreateInstance(const Uuid &iid, void **ppv);

} // @namespace uap

#endif //_UAP_COMPONENT_