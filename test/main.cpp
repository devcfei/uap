#include <gtest/gtest.h>
#include <uap.h>



// // Demonstrate some basic assertions.
// TEST(uapTest, BasicAssertions)
// {
//     // Expect two strings not to be equal.
//     EXPECT_STRNE("hello", "world");
//     // Expect equality.
//     EXPECT_EQ(7 * 6, 42);

// }

int main(int argc, char *argv[])
{
    uap::Result r = uap::uapInitialize();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}