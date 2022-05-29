#include "common.h"


// {7b4a8d1a-137c-4945-ad03-16d068f36346}
DEFINE_UUID(UUID_TEST_ITEM, 
    0x7b4a8d1a, 0x137c, 0x4945, 0xad, 0x03, 0x16, 0xd0, 0x68, 0xf3, 0x63, 0x46);



TEST(Attrbutes, IAttributes_uint) 
{
    Result r;
    sptr<IApplication> sp;

    r = uapCreateApplication((IApplication**)&sp);
    EXPECT_EQ(r, R_SUCCESS);

    sptr<IAttributes> spAttributes;
    r = sp->createInstance(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, R_SUCCESS);


    Uint val = 0xdeedbeef;
    r = spAttributes->setUint(UUID_TEST_ITEM, val);
    EXPECT_EQ(r, R_SUCCESS);
    val = 0;

    r = spAttributes->getUint(UUID_TEST_ITEM, val);
    EXPECT_EQ(r, R_SUCCESS);

    EXPECT_EQ(val, 0xdeedbeef);

    // overwrite test
    val =  0xfacefeed;
    r = spAttributes->setUint(UUID_TEST_ITEM, val);
    EXPECT_EQ(r, R_SUCCESS);

    val = 0;

    r = spAttributes->getUint(UUID_TEST_ITEM, val);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(val, 0xfacefeed);
}

