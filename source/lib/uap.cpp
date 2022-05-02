#include <uap.h>
#include "uapheaders.h"
#include "uapinternal.h"

namespace uap
{

    struct uapPfn global_Pfn;

#if defined(_MSC_VER)
    static Result uapInitializeWindows()
    {
        Result r = R_OK;

        HMODULE hDll = LoadLibrary(_T("uapbe.dll"));
        if (hDll)
        {

            global_Pfn.pfn_beInitialize = (PFN_beInitialize)GetProcAddress(hDll, "uapbeInitialize");
            global_Pfn.pfn_vPrint = (PFN_vPrint)GetProcAddress(hDll, "uapbeVPrint");
            global_Pfn.pfn_GetInterface = (PFN_GetInterface)GetProcAddress(hDll, "uapbeGetInterface");

            TRACE("uapbeInitialize address: %p\n", global_Pfn.pfn_beInitialize);
            TRACE("uapbeVPrint address: %p\n", global_Pfn.pfn_vPrint);
            TRACE("uapbeGetInterface address: %p\n", global_Pfn.pfn_GetInterface);


            r = global_Pfn.pfn_beInitialize();
        }
        else
        {
            r = R_ERROR_LOAD_LIBRARY;
        }


        // TODO: when to FreeLibrary(hDll) ?
        return r;
    }
#endif

    Result uapInitialize()
    {
        Result r = R_OK;

        TRACE(_T("uapInitialize\n"));

#if defined(_MSC_VER)
        r = uapInitializeWindows();

#elif defined(__linux__)

        r = R_NOT_IMPLEMENTED;
#else
        r = R_NOT_IMPLEMENTED;
#endif

        return r;
    }

    
    Result uapGetInterface(const Uuid &uuid, IUnknown **ppiUnknown)
    {
        Result r = R_OK;
        ASSERT(global_Pfn.pfn_GetInterface);
        r = global_Pfn.pfn_GetInterface(uuid, ppiUnknown);
        return r;
    }

};
