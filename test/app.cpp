#include <gtest/gtest.h>
#include <uap.h>
#include <uapimageengine.h>
#include <uapuiengine.h>

TEST(App, initialize)
{
    uap::Result r;

    uap::sptr<uap::IApp> sp;

    r = uap::uapAppInitialize((uap::IApp**)&sp);

    EXPECT_EQ(r, uap::R_OK);

    r = sp->initialize();
    EXPECT_EQ(r, uap::R_OK);

}


TEST(App, createInterface)
{
    uap::Result r;

    uap::sptr<uap::IApp> sp;

    r = uap::uapAppInitialize((uap::IApp**)&sp);
    EXPECT_EQ(r, uap::R_OK);

    // uapbe interfaces
    uap::sptr<uap::IAttributes> spAttributes;
    r = sp->createInterface(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, uap::R_OK);


    // component interfaces
    uap::sptr<uap::IImageEngine> spImageEngine;
    r = sp->createInterface(IID_IMAGEENGINE, (void**)&spImageEngine);    
    EXPECT_EQ(r, uap::R_OK);

    uap::sptr<uap::IUiEngine> spUiEngine;
    r = sp->createInterface(IID_UIENGINE, (void**)&spUiEngine);    
    EXPECT_EQ(r, uap::R_OK);

}