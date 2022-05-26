#include "headers.h"

TEST(App, initialize)
{
    Result r;

    sptr<IApplication> spApp;

    r = uapCreateApplication((IApplication**)&spApp);
    EXPECT_EQ(r, R_SUCCESS);


    sptr<IAttributes> spAttributes;
    r = spApp->createInstance(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, R_SUCCESS);


    r = spApp->initialize(spAttributes.get());
    EXPECT_EQ(r, R_SUCCESS);

}


TEST(App, createInstance)
{
    Result r;

    sptr<IApplication> spApp;

    r = uapCreateApplication((IApplication**)&spApp);
    EXPECT_EQ(r, R_SUCCESS);

    // uapbe interfaces
    sptr<IAttributes> spAttributes;
    r = spApp->createInstance(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, R_SUCCESS);


    r = spApp->initialize(spAttributes.get());
    EXPECT_EQ(r, R_SUCCESS);


    // component interfaces
    sptr<IImageEngine> spImageEngine;
    r = spApp->createInstance(IID_IMAGEENGINE, (void**)&spImageEngine);    
    EXPECT_EQ(r, R_SUCCESS);

    sptr<IUiEngine> spUiEngine;
    r = spApp->createInstance(IID_UIENGINE, (void**)&spUiEngine);    
    EXPECT_EQ(r, R_SUCCESS);

}