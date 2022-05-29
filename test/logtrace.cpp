#include "common.h"



TEST(LogTrace, basictest)
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
    ac.s.enableComponent = 1;

    spAttributes->setUint(UUID_APPLICATION_CONFIGURATION, ac.ui);


    r = spApp->initialize(spAttributes.get());
    EXPECT_EQ(r, R_SUCCESS);



    // log
    sptr<ILogTrace> spLog;
    r = spApp->createInstance(IID_LOGTRACE, (void**)&spLog);    
    EXPECT_EQ(r, R_SUCCESS);


    sptr<IAttributes> spAttributesLog;
    r = spApp->createInstance(IID_IATTRIBUTES, (void**)&spAttributesLog);    
    EXPECT_EQ(r, R_SUCCESS);


    LogAttributes logAttr;

    logAttr.s.defaultLevel=LT_ALL;
    logAttr.s.enableFileLogger=1;
    logAttr.s.enableMessageToDebugger=1;
    logAttr.s.enable=1;
    logAttr.s.enableLevelTag=1;

    spAttributesLog->setUlong(UUID_LOGTRACE_ATTRIBUTES, logAttr.ul);


    r = spLog->initialize(spApp.get(),MODULE_NAME, spAttributesLog.get());
    EXPECT_EQ(r, R_SUCCESS);


    spLog->output(0, "hello - level=%d\n", 0);
    spLog->output(1, "hello - level=%d\n", 1);
    spLog->output(2, "hello - level=%d\n", 2);
    spLog->output(3, "hello - level=%d\n", 3);
    spLog->output(4, "hello - level=%d\n", 4);

}