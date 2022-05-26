#include "headers.h"




TEST(ImageEngine, Interface)
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


    sptr<IImageEngine> spImageEngine;
    r = spApp->createInstance(IID_IMAGEENGINE, (void**)&spImageEngine);    
    EXPECT_EQ(r, R_SUCCESS);


    r = spImageEngine->initialize(spApp.get());
    EXPECT_EQ(r, R_SUCCESS);



}
