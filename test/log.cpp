#include <gtest/gtest.h>
#include <uap.h>

// Demonstrate some basic assertions.
TEST(Log, Type)
{
    uap::Result r = uap::R_OK;
    // Expect equality.
    r = uap::logPrint("test log: %d\n",1);
    EXPECT_EQ(r, uap::R_OK);

}