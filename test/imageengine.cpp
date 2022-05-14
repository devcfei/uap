#include <gtest/gtest.h>
#include <uap.h>
#include <uapimageengine.h>




TEST(imageengine, Interface)
{

    uap::Result r;

    uap::sptr<uap::IApplication> spApp;

    r = uap::uapCreateApplication((uap::IApplication**)&spApp);
    EXPECT_EQ(r, uap::R_OK);


    uap::sptr<uap::IAttributes> spAttributes;
    r = spApp->createInterface(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, uap::R_OK);


    r = spApp->initialize(spAttributes.get());
    EXPECT_EQ(r, uap::R_OK);


    uap::sptr<uap::IImageEngine> spImageEngine;
    r = spApp->createInterface(IID_IMAGEENGINE, (void**)&spImageEngine);    
    EXPECT_EQ(r, uap::R_OK);


    r = spImageEngine->initialize(spApp.get());
    EXPECT_EQ(r, uap::R_OK);



}
