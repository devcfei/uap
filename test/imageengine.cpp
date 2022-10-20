#include "common.h"



TEST(ImageEngine, Interface)
{

    Result r;

    sptr<IApplication> spApp;

    r = uapCreateApplication((IApplication**)&spApp);
    EXPECT_EQ(r, R_SUCCESS);


    sptr<IAttributes> spAttributes;
    r = spApp->createInstance(IID_IATTRIBUTES, (void**)&spAttributes);    
    EXPECT_EQ(r, R_SUCCESS);


    // application configuration
    ApplicationConfiguration ac={0};
    ac.s.enableLog = 1;
    ac.s.enableComponent = 1;   // always enable component


    spAttributes->setUint(APPLICATION_ATTRIBUTE_CONFIGURATION, ac.ui);
    
    Char appPath[256];
    spApp->getCurrentPath(appPath, 256);
    std::string str=appPath;
    str+="\\app.log";
    spAttributes->setString(APPLICATION_ATTRIBUTE_LOGFILE_PATH,str.c_str(),str.length());


    r = spApp->initialize(spAttributes.get());
    EXPECT_EQ(r, R_SUCCESS);


    sptr<IImageEngine> spImageEngine;
    r = spApp->createInstance(IID_IMAGEENGINE, (void**)&spImageEngine);    
    EXPECT_EQ(r, R_SUCCESS);


    r = spImageEngine->initialize(spApp.get());
    EXPECT_EQ(r, R_SUCCESS);



}
