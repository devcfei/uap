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


    // set log
    LogAttributes logAttr={0};

    logAttr.s.defaultLevel=LT_ALL;
    logAttr.s.enableAppLogTrace=1;
    logAttr.s.enableDebugTrace=1;
    logAttr.s.enableLevelTag=1;
    spUiAttributes_->setUlong(UUID_LOGTRACE_ATTRIBUTES, logAttr.ul);

    // initialize the UI engine
    r = spUiEngine_->initialize(spApp_.get(),spUiAttributes_.get());
    RESULT_CHECK(r,"initialze UI engine");


    // set layout
    r = spUiEngine_->queryInterface(IID_IUILAYOUT, (void**)&spLayout_);
    RESULT_CHECK(r,"queryInterface IUiLayout\n")

    // create an attribute
    r = spApp_->createInterface(IID_IATTRIBUTES, (void**)&spLayoutAttributes_);
    RESULT_CHECK(r,"create instance attributes")

    // set layout
    setLayout();

    r = spLayout_->initializeLayout(spLayoutAttributes_.get());
    RESULT_CHECK(r,"create instance attributes")

    // startup
    r = spUiEngine_->startup();   

    // run
    r = spUiEngine_->run();

    return r;  
}

Result App::setLayout()
{
    Result r = R_OK;
    // set attributes of spLayoutAttributes_

    sptr<IAttributes> sp=spLayoutAttributes_.get();

    

    return r;  

}

