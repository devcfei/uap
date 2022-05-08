#include <windows.h>
#include <tchar.h>

#include <uap.h>
#include <uapuiengine.h>

using namespace uap;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    int ret = 0;
    ::CoInitialize(NULL);

    Result r = uapInitialize();

    sptr<IApp> spApp; 

    r = uapAppInitialize((IApp**)&spApp);

    if(!UAP_SUCCESS(r))
    {
        ret = -1;
        ExitProcess(1);
    }


    sptr<IUiEngine> spUiEngine;
    r = spApp->createInterface(IID_UIENGINE,(void**)&spUiEngine);
    if(!UAP_SUCCESS(r))
    {
        ret = -1;
        ExitProcess(1);
    }



    r = spUiEngine->initialize();
    if(!UAP_SUCCESS(r))
    {
        ret = -1;
        ExitProcess(1);
    }

    r = spUiEngine->run();


    return ret;
}
