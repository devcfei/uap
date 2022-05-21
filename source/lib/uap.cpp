#include "uapheaders.h"

namespace uap
{
    /// print message 
    Result uapPrintMessage(Char* format, ...)
    {
#if defined(_WIN32)
        Result r = R_SUCCESS;
        HRESULT hr;
        CHAR szMessageBuffer[16380] = {0};
        va_list valist;

        va_start(valist, format);
        hr = StringCchVPrintfA(szMessageBuffer, 16380, format, valist);
        if (FAILED(hr))
        {
            r = R_ERROR;
            return r;
        }
        va_end(valist);

        OutputDebugStringA(szMessageBuffer);
        return r;
#elif defined(__linux__)
        Result r = R_SUCCESS;
        va_list valist;
        va_start(valist, format);
        vprintf(format,valist);
        va_end(valist);
        return r;
#endif
    }

    const Char* uapGetUuidString(const Uuid &uuid)
    {
        static Char szUuid[]= "{00000000-0000-0000-0000-000000000000}";
#if defined(_WIN32)
        StringCchPrintfA(szUuid,sizeof(szUuid)+1,"{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
            uuid.Data1,uuid.Data2,uuid.Data3,uuid.Data4[0],uuid.Data4[1],
            uuid.Data4[2],uuid.Data4[3],uuid.Data4[4],uuid.Data4[5],uuid.Data4[6],uuid.Data4[7]);

#elif defined(__linux__)
        sprintf(szUuid, "{%08lx-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
            uuid.Data1,uuid.Data2,uuid.Data3,uuid.Data4[0],uuid.Data4[1],
            uuid.Data4[2],uuid.Data4[3],uuid.Data4[4],uuid.Data4[5],uuid.Data4[6],uuid.Data4[7]);

#endif
        return szUuid;
    }

    struct uapbePfn global_Pfn;

#if defined(_WIN32)
    static Result uapInitializeWindows()
    {
        Result r = R_SUCCESS;

        HMODULE hDll = LoadLibrary(_T("uapbe.dll"));
        if (hDll)
        {

            global_Pfn.pfn_beInitialize = (PFN_beInitialize)GetProcAddress(hDll, "uapbeInitialize");
            global_Pfn.pfn_beCreateApplication = (PFN_beCreateApplication)GetProcAddress(hDll, "uapbeCreateApplication");            

            UAP_TRACE("uapbeInitialize address: %p\n", global_Pfn.pfn_beInitialize);
            UAP_TRACE("uapbeCreateApplication address: %p\n", global_Pfn.pfn_beCreateApplication);


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
        Result r = R_SUCCESS;

        UAP_TRACE("uapInitialize\n");

#if defined(_WIN32)
        r = uapInitializeWindows();

#elif defined(__linux__)

        r = R_NOT_IMPL;
#else
        r = R_NOT_IMPL;
#endif

        return r;
    }







    Result uapCreateApplication(IApplication** ppiApp)
    {
        Result r = R_SUCCESS;
        UAP_ASSERT(global_Pfn.pfn_beCreateApplication);
        r = global_Pfn.pfn_beCreateApplication(ppiApp);
        return r;
    }

};
