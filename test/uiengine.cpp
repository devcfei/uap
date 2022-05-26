#include "headers.h"





TEST(UiEngine, Interface)
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

    
    sptr<IUiEngine> spUiEngine;
    r = spApp->createInstance(IID_UIENGINE, (void**)&spUiEngine);    
    EXPECT_EQ(r, R_SUCCESS);


}
