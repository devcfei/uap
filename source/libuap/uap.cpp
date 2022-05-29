#include "uapheaders.h"

namespace uap
{
    /// print message
    Result uapPrintMessage(Char *format, ...)
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
        vprintf(format, valist);
        va_end(valist);
        return r;
#endif
    }

    const Char *uapGetUuidString(const Uuid &uuid)
    {
        static Char szUuid[] = "{00000000-0000-0000-0000-000000000000}";
#if defined(_WIN32)
        StringCchPrintfA(szUuid, sizeof(szUuid) + 1, "{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
                         uuid.Data1, uuid.Data2, uuid.Data3, uuid.Data4[0], uuid.Data4[1],
                         uuid.Data4[2], uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);

#elif defined(__linux__)
        sprintf(szUuid, "{%08lx-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
                uuid.Data1, uuid.Data2, uuid.Data3, uuid.Data4[0], uuid.Data4[1],
                uuid.Data4[2], uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);

#endif
        return szUuid;
    }

    Result uapInitialize()
    {
        Result r = R_SUCCESS;

        UAP_TRACE("uapInitialize\n");

#if defined(_WIN32)

#elif defined(__linux__)

        r = R_NOT_IMPL;
#else
        r = R_NOT_IMPL;
#endif

        return r;
    }

    Result uapCreateApplication(IApplication **ppiApp)
    {
        Result r = R_NO_SUCH_INTERFACE;
        UAP_TRACE("uapCreateApplication\n");

#if defined(_WIN32)

        HMODULE hDll = LoadLibrary(_T("application.dll"));
        if (hDll)
        {
            PFN_CreateInstance pfn = (PFN_CreateInstance)GetProcAddress(hDll, "CreateInstance");
            if (pfn)
            {
                r = pfn(IID_IAPPLICATION, (void **)ppiApp);
            }
        }
        else
        {
            r = R_FILE_NOT_EXIST;
            UAP_TRACE("ERROR: LoadLibrary failed! %s\n");
        }

#elif defined(__linux__)

        r = R_NOT_IMPL;
#else
        r = R_NOT_IMPL;
#endif

        return r;
    }

};
