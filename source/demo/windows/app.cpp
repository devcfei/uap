#include "framework.h"


App::App()
{

}

App::~App()
{

}

Result App::createApplication()
{
    Result r;
    r = uapCreateApplication((IApplication **)&spApp_);

    return r;
}

Result App::initApplication()
{
    Result r;

    sptr<IAttributes> spAttributes;
    r = spApp_->createInterface(IID_IATTRIBUTES, (void**)&spAttributes);
    RESULT_CHECK(r,"createInterface IID_IATTRIBUTES");


    // application initialize with log trace and components
    Uint initFlags = APP_INIT_LOGTRACE_ENALBE | APP_INIT_COMPONENT_ENALBE;
    spAttributes->setUint(UUID_APP_INIT_FLAGS, initFlags);

    r = spApp_->initialize(spAttributes.get());
    RESULT_CHECK(r,"app initialize");

    return r;
}


Result App::startUI()
{
    Result r;

    // create the engine
    r = spApp_->createInterface(IID_UIENGINE,(void**)&spUiEngine_);
    RESULT_CHECK(r,"create instance UI engine")

    // create an attribute
    r = spApp_->createInterface(IID_IATTRIBUTES, (void**)&spUiAttributes_);
    RESULT_CHECK(r,"create instance attributes")

    //
    // 
    //

    // set application name
    spUiAttributes_->setString(UUID_APP_NAME, "Demo",4);

    // set application layout style
    LayoutStyle style;
    //style = LAYOUT_STYLE_SIMPLE; 
    style = LAYOUT_STYLE_DOCKING; 
    //style = LAYOUT_STYLE_DEMO;
    spUiAttributes_->setUint(UUID_UILAYOUT_STYLE,style);

    // set log
    LogAttributes logAttr={0};

    logAttr.s.defaultLevel=LT_ALL;
    logAttr.s.enableAppLogTrace=1;
    logAttr.s.enableDebugTrace=1;
    logAttr.s.enableLevelTag=1;
    spUiAttributes_->setUlong(UUID_LOGTRACE_ATTRIBUTES, logAttr.ul);

    

    // initialize the UI engine
    r = spUiEngine_->initialize(spApp_.get(),spUiAttributes_.get());
    RESULT_CHECK(r,"initialze UI engine")



    // set layout
    r = setLayout();

    // startup
    r = spUiEngine_->startup();   

    // run
    r = spUiEngine_->run();

    return r;  
}

Result App::setLayout()
{
    Result r = R_SUCCESS;

#if 0

    // get layout IUiLayout
    r = spUiEngine_->queryInterface(IID_IUILAYOUT, (void**)&spLayout_);
    RESULT_CHECK(r,"queryInterface IUiLayout")

    // create an attribute
    r = spApp_->createInterface(IID_IATTRIBUTES, (void**)&spLayoutAttributes_);
    RESULT_CHECK(r,"create instance attributes")


    LayoutStyle style;
    //style = LAYOUT_STYLE_SIMPLE; 
    style = LAYOUT_STYLE_DOCKING; 
    //style = LAYOUT_STYLE_DEMO;
    spLayoutAttributes_->setUint(UUID_UILAYOUT_STYLE,style);

    // initialize the UI layout
    r = spLayout_->initializeLayout(spLayoutAttributes_.get());
    RESULT_CHECK(r,"initiaize the UI layout")    

#endif
    // build the layout
    r =  buildLayout();
    RESULT_CHECK(r,"build UI layout")


    return r;  

}


Result App::buildLayout()
{
    Result r = R_SUCCESS;

    // MenuBar
    // get layout IUiLayout
    sptr<IUiMenuBar> spMenuBar;
    r = spUiEngine_.as(&spMenuBar);
    RESULT_CHECK(r,"spUiEngine_.as(<IUiMenuBar>)");

    sptr<IAttributes> spMenuBarAttrbutes;

    // create an attribute
    r = spApp_->createInterface(IID_IATTRIBUTES, (void**)&spMenuBarAttrbutes);
    RESULT_CHECK(r,"create instance attributes")





    // initialize MenuBar
    r = spMenuBar->initializeMenuBar(spMenuBarAttrbutes.get());
    RESULT_CHECK(r,"initialize MenuBar")


    return r;  
}


