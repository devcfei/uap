#include "headers.h"

TEST(App, initialize)
{
    Result r;

    sptr<IApplication> spApp;

    r = uapCreateApplication((IApplication**)&spApp);
    EXPECT_EQ(r, R_SUCCESS);


    sptr<IAttributes> spAttributes;
    r = spApp->createInterface(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, R_SUCCESS);


    r = spApp->initialize(spAttributes.get());
    EXPECT_EQ(r, R_SUCCESS);

}


TEST(App, createInterface)
{
    Result r;

    sptr<IApplication> spApp;

    r = uapCreateApplication((IApplication**)&spApp);
    EXPECT_EQ(r, R_SUCCESS);

    // uapbe interfaces
    sptr<IAttributes> spAttributes;
    r = spApp->createInterface(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, R_SUCCESS);


    r = spApp->initialize(spAttributes.get());
    EXPECT_EQ(r, R_SUCCESS);


    // component interfaces
    sptr<IImageEngine> spImageEngine;
    r = spApp->createInterface(IID_IMAGEENGINE, (void**)&spImageEngine);    
    EXPECT_EQ(r, R_SUCCESS);

    sptr<IUiEngine> spUiEngine;
    r = spApp->createInterface(IID_UIENGINE, (void**)&spUiEngine);    
    EXPECT_EQ(r, R_SUCCESS);

}