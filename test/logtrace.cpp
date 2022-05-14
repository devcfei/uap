#include <gtest/gtest.h>
#include <uap.h>

using namespace uap;



TEST(LogTrace, basictest)
{
    uap::Result r;

    uap::sptr<uap::IApplication> spApp;

    r = uap::uapCreateApplication((uap::IApplication**)&spApp);
    EXPECT_EQ(r, uap::R_OK);


    uap::sptr<uap::IAttributes> spAttributes;
    r = spApp->createInterface(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, uap::R_OK);


    // application initialize with log trace and components
    Uint initFlags = APP_INIT_LOGTRACE_ENALBE | APP_INIT_COMPONENT_ENALBE;
    spAttributes->setUint(UUID_APP_INIT_FLAGS, initFlags);

    r = spApp->initialize(spAttributes.get());
    EXPECT_EQ(r, uap::R_OK);



    // log
    uap::sptr<uap::ILogTrace> spLog;
    r = spApp->createInterface(IID_LOGTRACE, (void**)&spLog);    
    EXPECT_EQ(r, uap::R_OK);


    uap::sptr<uap::IAttributes> spAttributesLog;
    r = spApp->createInterface(IID_IATTRIBUTES, (void**)&spAttributesLog);    
    EXPECT_EQ(r, uap::R_OK);


    uap::LogAttributes logAttr;

    logAttr.s.defaultLevel=uap::LT_ALL;
    logAttr.s.enableAppLogTrace=1;
    logAttr.s.enableDebugTrace=1;
    logAttr.s.enable=1;
    logAttr.s.enableLevelTag=1;

    spAttributesLog->setUlong(uap::UUID_LOGTRACE_ATTRIBUTES, logAttr.ul);


    r = spLog->initialize(spApp.get(),"uaptest.exe", spAttributesLog.get());
    EXPECT_EQ(r, uap::R_OK);


    spLog->output(0, "hello - level=%d\n", 0);
    spLog->output(1, "hello - level=%d\n", 1);
    spLog->output(2, "hello - level=%d\n", 2);
    spLog->output(3, "hello - level=%d\n", 3);
    spLog->output(4, "hello - level=%d\n", 4);

}