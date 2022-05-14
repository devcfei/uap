#include <gtest/gtest.h>
#include <uap.h>
#include <uapuiengine.h>




TEST(uiengine, Interface)
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

    
    uap::sptr<uap::IUiEngine> spUiEngine;
    r = spApp->createInterface(IID_UIENGINE, (void**)&spUiEngine);    
    EXPECT_EQ(r, uap::R_OK);


}
