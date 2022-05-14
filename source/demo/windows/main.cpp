#include <windows.h>
#include <tchar.h>

#include <uap.h>
#include <uapuiengine.h>

using namespace uap;

#if defined (_DEBUG)
#define TRACE(fmt, ...) uap::logPrint("demo.exe!" fmt, __VA_ARGS__)
#define ASSERT(_expr_)
#else
#define TRACE(fmt, ...) 
#define ASSERT(_expr_)
#endif



#define RESULT_CHECK(r, _message_) \
        if(!UAP_SUCCESS(r)) \
        { \
            TRACE( _message_ ## " failed! r = 0x%8.8x\n",r); \
            return r; \
        } 


Result startUI(IApplication* piApp)
{
    Result r;

    sptr<IApplication> spApp=piApp;

    // create the engine
    sptr<IUiEngine> spUiEngine;
    r = spApp->createInterface(IID_UIENGINE,(void**)&spUiEngine);
    RESULT_CHECK(r,"create instance UI engine")

    // create an attribute
    sptr<IAttributes> spAttributes;
    r = spApp->createInterface(IID_IATTRIBUTES, (void**)&spAttributes);
    RESULT_CHECK(r,"create instance attributes")


    // set log
    LogAttributes logAttr={0};

    logAttr.s.defaultLevel=LT_ALL;
    logAttr.s.enableAppLogTrace=1;
    logAttr.s.enableDebugTrace=1;
    logAttr.s.enableLevelTag=1;
    spAttributes->setUlong(UUID_LOGTRACE_ATTRIBUTES, logAttr.ul);

    // initialize the UI engine
    r = spUiEngine->initialize(spApp.get(),spAttributes.get());
    RESULT_CHECK(r,"initialze UI engine");
     

    r = spUiEngine->run();

    return r;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    int ret = 0;
    ::CoInitialize(NULL);

    // uap initialize
    Result r = uapInitialize();

    // create the application
    sptr<IApplication> spApp; 
    r = uapCreateApplication((IApplication**)&spApp);
    if(!UAP_SUCCESS(r))
    {
        ret = -1;
        ExitProcess(1);
    }

    // create an attribute
    sptr<IAttributes> spAttributes;
    r = spApp->createInterface(IID_IATTRIBUTES, (void**)&spAttributes);
    if(!UAP_SUCCESS(r))
    {
        ret = -1;
        ExitProcess(1);
    }

    // application initialize with log trace and components
    Uint initFlags = APP_INIT_LOGTRACE_ENALBE | APP_INIT_COMPONENT_ENALBE;
    spAttributes->setUint(UUID_APP_INIT_FLAGS, initFlags);

    r = spApp->initialize(spAttributes.get());
    if(!UAP_SUCCESS(r))
    {
        ret = -1;
        ExitProcess(1);
    }


    r = startUI(spApp.get());
    if(!UAP_SUCCESS(r))
    {
        ret = -1;
        ExitProcess(1);
    }


    return ret;
}
