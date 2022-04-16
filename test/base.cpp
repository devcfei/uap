#include <gtest/gtest.h>
#include <uap.h>

// Demonstrate some basic assertions.
TEST(Base, Type)
{
    // Expect equality.
    EXPECT_EQ(1, sizeof(uap::Char));
    EXPECT_EQ(2, sizeof(uap::Short));
    EXPECT_EQ(4, sizeof(uap::Int));
    EXPECT_EQ(4, sizeof(uap::Long));
    EXPECT_EQ(8, sizeof(uap::LongLong));


    EXPECT_EQ(1, sizeof(uap::Uchar));
    EXPECT_EQ(2, sizeof(uap::Ushort));
    EXPECT_EQ(4, sizeof(uap::Uint));
    EXPECT_EQ(4, sizeof(uap::Ulong));
    EXPECT_EQ(8, sizeof(uap::UlongLong));
}