#include "uapbe.h"




using namespace uap;

extern "C" DLL_EXPORTS Result uapbeVPrint(Char* pszFormat, va_list vaList)
{
    Result r = R_OK;
    HRESULT hr;

	TCHAR szMessageBuffer[16380] = { 0 };
	hr = StringCchVPrintfA(szMessageBuffer, 16380, pszFormat, vaList);

    if(FAILED(hr))
    {
        r = R_ERROR;
        return r;
    }
	OutputDebugString(szMessageBuffer);

    return r;
}