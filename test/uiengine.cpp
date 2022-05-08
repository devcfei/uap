#include <gtest/gtest.h>
#include <uap.h>
#include <uapuiengine.h>




TEST(uiengine, Interface)
{
    uap::Result r;

    uap::sptr<uap::IApp> sp;

    r = uap::uapAppInitialize((uap::IApp**)&sp);
    EXPECT_EQ(r, uap::R_OK);


    uap::sptr<uap::IUiEngine> spUiEngine;
    r = sp->createInterface(IID_IMAGEENGINE, (void**)&spUiEngine);    
    EXPECT_EQ(r, uap::R_OK);


    r = spUiEngine->initialize();
    EXPECT_EQ(r, uap::R_OK);

}
