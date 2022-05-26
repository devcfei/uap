#include "headers.h"


TEST(UAP, Types)
{
    EXPECT_EQ(1, sizeof(Char));
    EXPECT_EQ(2, sizeof(Short));
    EXPECT_EQ(4, sizeof(Int));
#if defined(_WIN32)
    EXPECT_EQ(4, sizeof(Long));
#endif


#if defined(__linux__)

#if defined(__x86_64__)
    EXPECT_EQ(8, sizeof(Long));
#endif

#if defined(__i386__)
    EXPECT_EQ(4, sizeof(Long));
#endif

#endif

    EXPECT_EQ(8, sizeof(LongLong));


    EXPECT_EQ(1, sizeof(Uchar));
    EXPECT_EQ(2, sizeof(Ushort));
    EXPECT_EQ(4, sizeof(Uint));
#if defined(_WIN32)
    EXPECT_EQ(4, sizeof(Ulong));
#endif


#if defined(__linux__)

#if defined(__x86_64__)
    EXPECT_EQ(8, sizeof(Ulong));
#endif

#if defined(__i386__)
    EXPECT_EQ(4, sizeof(Ulong));
#endif

#endif
    EXPECT_EQ(8, sizeof(UlongLong));
}


TEST(UAP, Initialize)
{
    Result r;
    r = uapInitialize();
    EXPECT_EQ(r, R_SUCCESS);
}




TEST(UAP, ResultCheck)
{
    Result r;
    r = R_SUCCESS;    
    EXPECT_EQ(1, UAP_SUCCESS(r));
    
    r = R_ERROR;
    EXPECT_EQ(0, UAP_SUCCESS(r));
}


TEST(UAP, PrintMessage)
{
    Result r;
    r = uapPrintMessage("hello - %d\n", 10);
    EXPECT_EQ(r, R_SUCCESS);
}

TEST(UAP, GetResultString)
{
    Result r;
    r = R_ERROR;
    r = uapPrintMessage("error - %d(%s)\n", r, uapGetResultString(r));
    EXPECT_EQ(r, R_SUCCESS);
}



// {fa18eeec-ebe6-42aa-be35-4767d3061f23}
DEFINE_UUID(UUID_TEST1, 
    0xfa18eeec, 0xebe6, 0x42aa, 0xbe, 0x35, 0x47, 0x67, 0xd3, 0x06, 0x1f, 0x23);

// {d36023ef-4f69-45c1-8bd8-115a14f0c5b4}
DEFINE_UUID(UUID_TEST2, 
    0xd36023ef, 0x4f69, 0x45c1, 0x8b, 0xd8, 0x11, 0x5a, 0x14, 0xf0, 0xc5, 0xb4);

TEST(UAP, UUID)
{
    EXPECT_EQ(1,uapUuidIsEqual(UUID_TEST1, UUID_TEST1));
    EXPECT_EQ(0,uapUuidIsEqual(UUID_TEST1, UUID_TEST2));

    const Char* string1 = "{fa18eeec-ebe6-42aa-be35-4767d3061f23}";
    const Char* string2 = uapGetUuidString(UUID_TEST1);


    EXPECT_EQ(0,strcmp(string1, string2));

}


TEST(UAP, Log)
{
    Result r = R_SUCCESS;
    // Expect equality.
    UAP_TRACE("test log\n");
    
    EXPECT_EQ(r, R_SUCCESS);

}


TEST(UAP, IAttributes)
{
    Result r;
    sptr<IApplication> sp;

    r = uapCreateApplication((IApplication**)&sp);
    EXPECT_EQ(r, R_SUCCESS);


    IAttributes *piAttributes;
    r = sp->createInstance(IID_IATTRIBUTES, (void**)&piAttributes);    
    EXPECT_EQ(r, R_SUCCESS);

    Uint val =10;
    piAttributes->setUint(UUID_NULL,val);
    piAttributes->getUint(UUID_NULL,val);
    piAttributes->release();

}


TEST(UAP, IAttributes_sptr)
{
    Result r;
    sptr<IApplication> sp;

    r = uapCreateApplication((IApplication**)&sp);
    EXPECT_EQ(r, R_SUCCESS);

    sptr<IAttributes> spAttributes;
    r = sp->createInstance(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, R_SUCCESS);

    Uint val =20;
    spAttributes->setUint(UUID_NULL,val);
    spAttributes->getUint(UUID_NULL,val);


}


// {7b4a8d1a-137c-4945-ad03-16d068f36346}
DEFINE_UUID(UUID_TEST_ITEM, 
    0x7b4a8d1a, 0x137c, 0x4945, 0xad, 0x03, 0x16, 0xd0, 0x68, 0xf3, 0x63, 0x46);



TEST(UAP, IAttributes_uint) 
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

