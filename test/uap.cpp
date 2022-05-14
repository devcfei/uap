#include <gtest/gtest.h>
#include <uap.h>



TEST(uap, IAttributes)
{
    uap::Result r;
    uap::sptr<uap::IApplication> sp;

    r = uap::uapCreateApplication((uap::IApplication**)&sp);
    EXPECT_EQ(r, uap::R_OK);


    uap::IAttributes *piAttributes;
    r = sp->createInterface(IID_IATTRIBUTES, (void**)&piAttributes);    
    EXPECT_EQ(r, uap::R_OK);

    uap::Uint val =10;
    piAttributes->setUint(0,val);
    piAttributes->getUint(0,val);
    piAttributes->release();

}


TEST(uap, IAttributes_sptr)
{
    uap::Result r;
    uap::sptr<uap::IApplication> sp;

    r = uap::uapCreateApplication((uap::IApplication**)&sp);
    EXPECT_EQ(r, uap::R_OK);

    uap::sptr<uap::IAttributes> spAttributes;
    r = sp->createInterface(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, uap::R_OK);

    uap::Uint val =20;
    spAttributes->setUint(0,val);
    spAttributes->getUint(0,val);


}