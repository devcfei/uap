#include <gtest/gtest.h>
#include <uap.h>



TEST(uap, IAttributes)
{
    uap::Result r;
    //Expect equality.
    uap::IAttributes *piAttributes;
    r = uap::uapGetInterface(IID_IATTRIBUTES, (uap::IUnknown**)&piAttributes);
    EXPECT_EQ(r, uap::R_OK);

    uap::Uint val =10;
    piAttributes->setUint(0,val);
    piAttributes->getUint(0,val);

    piAttributes->release();



}


TEST(uap, IAttributes_sptr)
{
    uap::Result r;

    uap::sptr<uap::IAttributes> sp;
    r = uap::uapGetInterface(IID_IATTRIBUTES, (uap::IUnknown**)sp.getaddrof());
    
    EXPECT_EQ(r, uap::R_OK);

}