#include "common.h"




TEST(UiEngine, createInstance)
{
    Result r;

    sptr<IApplication> spApp;

    r = uapCreateApplication((IApplication**)&spApp);
    EXPECT_EQ(r, R_SUCCESS);


    sptr<IAttributes> spAttributes;
    r = spApp->createInstance(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, R_SUCCESS);

    // application configuration
    ApplicationConfiguration ac={0};
    ac.s.enableLog = 1;
    ac.s.enableComponent = 1;   // always enable component


    spAttributes->setUint(UUID_APPLICATION_CONFIGURATION, ac.ui);


    r = spApp->initialize(spAttributes.get());
    EXPECT_EQ(r, R_SUCCESS);

    
    sptr<IUiEngine> spUiEngine;
    r = spApp->createInstance(IID_UIENGINE, (void**)&spUiEngine);    
    EXPECT_EQ(r, R_SUCCESS);


    // create an attribute
    sptr<IAttributes> spUiAttributes;

    r = spApp->createInstance(IID_IATTRIBUTES, (void **)&spUiAttributes);

    spUiAttributes->setUint(UUID_UILAYOUT_STYLE, LAYOUT_STYLE_SIMPLE);


    // set log
    LogAttributes logAttr = {0};


    logAttr.s.enable = 1;
    logAttr.s.enableFileLogger = 1;
    logAttr.s.enableMessageToDebugger = 1;
    logAttr.s.enableLevelTag = 1;
    logAttr.s.defaultLevel =4;


    spUiAttributes->setUlong(UUID_LOGTRACE_ATTRIBUTES, logAttr.ul);


    // initialize the UI engine
    r = spUiEngine->initialize(spApp.get(), spUiAttributes.get());



}
