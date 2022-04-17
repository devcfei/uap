#include <gtest/gtest.h>
#include <uap.h>

// Demonstrate some basic assertions.
TEST(Log, Type)
{
    // Expect equality.
    uap::Result r = uap::logPrint("%d\n",1);
    EXPECT_EQ(r, uap::R_OK);

}