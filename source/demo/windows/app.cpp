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

    UiMenuFlags flags;

    flags.s.start = 1;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 0;
    r = spMenuBar->insertMenuItem("File", 0,flags.ui);
    RESULT_CHECK(r,"insert MenuItem")


    flags.s.start = 1;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 1;
    r = spMenuBar->insertMenuItem("Exit", 0,flags.ui);
    RESULT_CHECK(r,"insert MenuItem")

    flags.s.start = 1;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 0;
    r = spMenuBar->insertMenuItem("View", 1,flags.ui);
    RESULT_CHECK(r,"insert MenuItem")

    flags.s.start = 0;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 0;
    r = spMenuBar->insertMenuItem("ToolBar", 0,flags.ui);
    RESULT_CHECK(r,"insert MenuItem")



    flags.s.start = 0;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 1;
    r = spMenuBar->insertMenuItem("StatusBar", 0,flags.ui);
    RESULT_CHECK(r,"insert MenuItem")

    
    return r;  
}


