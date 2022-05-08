#include <gtest/gtest.h>
#include <uap.h>
#include <uapimageengine.h>




TEST(imageengine, Interface)
{

    uap::Result r;

    uap::sptr<uap::IApp> sp;

    r = uap::uapAppInitialize((uap::IApp**)&sp);
    EXPECT_EQ(r, uap::R_OK);


    uap::sptr<uap::IImageEngine> spImageEngine;
    r = sp->createInterface(IID_IMAGEENGINE, (void**)&spImageEngine);    
    EXPECT_EQ(r, uap::R_OK);


    r = spImageEngine->initialize(sp.get());
    EXPECT_EQ(r, uap::R_OK);



}
