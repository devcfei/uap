#include "uapbe.h"

Result TraceMessage(LPCTSTR pszFormat, ...)
{
    Result r = R_OK;
    HRESULT hr;
    va_list pArgs;

    TCHAR szMessageBuffer[10380] = {0};
    va_start(pArgs, pszFormat);
    hr = StringCchVPrintf(szMessageBuffer, 10380, pszFormat, pArgs);
    va_end(pArgs);
    if (FAILED(hr))
    {
        r = R_ERROR;
        return r;
    }
    OutputDebugString(szMessageBuffer);

    return r;
}