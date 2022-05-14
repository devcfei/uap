#include "uapbe.h"


extern "C" DLL_EXPORTS Result uapbeInitialize()
{
    Result r = R_OK;
    TRACE("uapbeInitialize\n");
    return r;
}


extern "C" DLL_EXPORTS Result uapbeCreateApplication(IApplication** ppiApp)
{
    Result r = R_NO_MEMORY;
	IApplication* piApp;

    TRACE("new AppImpl()\n");
	piApp = new AppImpl();

	if(piApp)
	{
        *ppiApp = piApp;
        r = R_OK;		
	}

	return r;

}


extern "C" DLL_EXPORTS Result uapbeVPrint(Char *pszFormat, va_list vaList)
{
    Result r = R_OK;
    HRESULT hr;

    CHAR szMessageBuffer[16380] = {0};
    hr = StringCchVPrintfA(szMessageBuffer, 16380, pszFormat, vaList);
    if (FAILED(hr))
    {
		TRACE("StringCchVPrintfA failed\n");
        r = R_ERROR;
        return r;
    }

    OutputDebugStringA(szMessageBuffer);

    return r;
}