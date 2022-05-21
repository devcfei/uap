#include "uapbe.h"


extern "C" DLL_EXPORTS Result uapbeInitialize()
{
    Result r = R_SUCCESS;
    UAP_TRACE("uapbeInitialize\n");
    return r;
}


extern "C" DLL_EXPORTS Result uapbeCreateApplication(IApplication** ppiApp)
{
    Result r = R_NO_MEMORY;
	IApplication* piApp;

    UAP_TRACE("new AppImpl()\n");
	piApp = new AppImpl();

	if(piApp)
	{
        *ppiApp = piApp;
        r = R_SUCCESS;		
	}

	return r;

}