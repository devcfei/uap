#include <gtest/gtest.h>
#include <uap.h>

// Demonstrate some basic assertions.
TEST(uap, Initialize)
{
    //Expect equality.
    uap::Result r = uap::uapInitialize();
    EXPECT_EQ(r, uap::R_OK);

}


TEST(uap, IAttributes)
{
    //Expect equality.
    uap::IAttributes *piAttributes;
    uap::Result r = uap::uapGetInterface(IID_IATTRIBUTES, (uap::IUnknown**)&piAttributes);
    EXPECT_EQ(r, uap::R_OK);

    uap::Uint val =10;
    piAttributes->setUint(0,val);
    piAttributes->getUint(0,val);

}