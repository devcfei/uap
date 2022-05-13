#include <gtest/gtest.h>
#include <uap.h>

TEST(LogTrace, basictest)
{
    uap::Result r;

    uap::sptr<uap::IApp> sp;

    r = uap::uapAppInitialize((uap::IApp**)&sp);
    EXPECT_EQ(r, uap::R_OK);


    uap::sptr<uap::ILogTrace> spLog;
    r = sp->createInterface(IID_LOGTRACE, (void**)&spLog);    
    EXPECT_EQ(r, uap::R_OK);


    r = spLog->initialize("logTest", 4);
    EXPECT_EQ(r, uap::R_OK);


    spLog->output(0, "hello - level=%d\n", 0);
    spLog->output(1, "hello - level=%d\n", 1);
    spLog->output(2, "hello - level=%d\n", 2);
    spLog->output(3, "hello - level=%d\n", 3);
    spLog->output(4, "hello - level=%d\n", 4);

}