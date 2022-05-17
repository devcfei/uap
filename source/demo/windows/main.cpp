#include "framework.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    int ret = 0;
    ::CoInitialize(NULL);

    // uap initialize
    Result r = uapInitialize();

    // new app;
    App *app = new App();

    r = app->createApplication();
    r = app->initApplication();
    r = app->startUI();

    delete app;

    return ret;
}
