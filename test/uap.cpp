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
    piAttributes->setUint(UUID_NULL,val);
    piAttributes->getUint(UUID_NULL,val);
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
    spAttributes->setUint(UUID_NULL,val);
    spAttributes->getUint(UUID_NULL,val);


}


// {7b4a8d1a-137c-4945-ad03-16d068f36346}
DEFINE_UUID(UUID_TEST_ITEM, 
    0x7b4a8d1a, 0x137c, 0x4945, 0xad, 0x03, 0x16, 0xd0, 0x68, 0xf3, 0x63, 0x46);



TEST(uap, IAttributes_uint) 
{
    uap::Result r;
    uap::sptr<uap::IApplication> sp;

    r = uap::uapCreateApplication((uap::IApplication**)&sp);
    EXPECT_EQ(r, uap::R_OK);

    uap::sptr<uap::IAttributes> spAttributes;
    r = sp->createInterface(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, uap::R_OK);


    uap::Uint val = 0xdeedbeef;
    r = spAttributes->setUint(UUID_TEST_ITEM, val);
    EXPECT_EQ(r, uap::R_OK);
    val = 0;

    r = spAttributes->getUint(UUID_TEST_ITEM, val);
    EXPECT_EQ(r, uap::R_OK);

    EXPECT_EQ(val, 0xdeedbeef);

    // overwrite test
    val =  0xfacefeed;
    r = spAttributes->setUint(UUID_TEST_ITEM, val);
    EXPECT_EQ(r, uap::R_OK);

    val = 0;

    r = spAttributes->getUint(UUID_TEST_ITEM, val);
    EXPECT_EQ(r, uap::R_OK);
    EXPECT_EQ(val, 0xfacefeed);
}

