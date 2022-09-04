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

    // get current path
    char filename[MAX_PATH];
    r = spApp_->getCurrentPath(filename, MAX_PATH);
    strAppPath_= filename;

    // get toml config
    r = spApp_->createInstance(IID_ITOML, (void **)&spToml_);
    VERIFY(r, "createInstance IID_ITOML");

    std::string strAppConfig = strAppPath_+ "default.toml";
    r= spToml_->initialize(spApp_.get(), strAppConfig.data());
    VERIFY(r, "initial toml");


    r =initApplicationConfiguration();

    return r;
}


Result App::initApplicationConfiguration()
{
    Result r;

    // application configuration
    ApplicationConfiguration ac={0};

    bool b = false;
    spToml_->getBool("app","log",b);
    if(b)
        ac.s.enableLog = 1;

    ac.s.enableComponent = 1;   // always enable component
    ac.s.logLevel = 4;  // not impl    

    sptr<IAttributes> spAttributes;
    r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&spAttributes);
    VERIFY(r, "createInstance IID_IATTRIBUTES");


    spAttributes->setUint(UUID_APPLICATION_CONFIGURATION, ac.ui);


    r = spApp_->initialize(spAttributes.get());
    VERIFY(r, "app initialize");



    // app log
    LogAttributes logAttr = {0};

    logAttr.s.enable = 1;
    logAttr.s.enableFileLogger = 1;
    logAttr.s.enableLevelTag = 1;
    logAttr.s.defaultLevel = 3;

    initializeLogTraceHelper(spApp_.get(), logAttr);



    return r;
}


Result App::startUI()
{
    Result r;

    // create the engine
    r = spApp_->createInstance(IID_UIENGINE, (void **)&spUiEngine_);
    VERIFY(r, "create instance UI engine");


    // init UiEngine
    r = initUiEngine();


    // startup
    r = spUiEngine_->startup();

    // set layout
    r = setLayout();

    // run
    r = spUiEngine_->run();

    return r;
}


Result App::initUiEngine()
{
    Result r = R_SUCCESS;

    // create an attribute
    r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&spUiAttributes_);
    VERIFY(r, "create instance attributes");

    //
    //
    //

    // set application name
    spUiAttributes_->setString(UUID_APP_NAME, "Demo", 4);

    int layout = 0;
    spToml_->getInt("uiengine", "layout", layout);

    // set application layout style
    LayoutStyle style;
    // style = LAYOUT_STYLE_SIMPLE;
    // style = LAYOUT_STYLE_DOCKING;
    //  style = LAYOUT_STYLE_DEMO;

    switch (layout)
    {
    case 0:
        style = LAYOUT_STYLE_SIMPLE;
        break;
    case 1:
        style = LAYOUT_STYLE_DOCKING;
        break;
    case 2:
        style = LAYOUT_STYLE_DEMO;
        break;
    default:
        style = LAYOUT_STYLE_SIMPLE;
        break;
    }

    spUiAttributes_->setUint(UUID_UILAYOUT_STYLE, style);


    // set log
    LogAttributes logAttr = {0};

    bool b;
    r = spToml_->getBool("uiengine", "log", "enable",b);
    if(b)
        logAttr.s.enableFileLogger = 1;

    b=false;
    spToml_->getBool("uiengine", "log", "todebugger",b);
    if(b)
        logAttr.s.enableMessageToDebugger = 1;

    b=false;
    spToml_->getBool("uiengine", "log", "tag",b);
    if(b)
        logAttr.s.enableLevelTag = 1;

    int level=0;

    spToml_->getInt("uiengine", "log", "level",level);
    logAttr.s.defaultLevel =level;


    spUiAttributes_->setUlong(UUID_LOGTRACE_ATTRIBUTES, logAttr.ul);

    // initialize the UI engine
    r = spUiEngine_->initialize(spApp_.get(), spUiAttributes_.get());
    VERIFY(r, "initialze UI engine");

    return r;
}


Result App::setLayout()
{
    Result r = R_SUCCESS;

    // build the MenuBar
    r = buildMenuBar();
    VERIFY(r, "build MenuBar");

    // build the ToolBar
    r = buildToolBar();
    VERIFY(r, "build ToolBar");

    // build the StatusBar
    r = buildStatusBar();
    VERIFY(r, "build StatusBar");


    // build the StatusBar
    r = buildLogWindow();
    VERIFY(r, "build LogWindow");


    // build the ImageWindow
    r = buildImageWindow();
    VERIFY(r, "build ImageWindow");

    // build the TextureInspector
    r = buildTextureInspector();
    VERIFY(r, "build TextureInspector");

    // build the FileBrowseWindow

    r = buildFileBrowserWindow();
    VERIFY(r, "build file browser");
    


    // build the layout
    r = buildLayout();
    VERIFY(r, "build UI layout");

    return r;
}

Result App::buildMenuBar()
{
    Result r = R_SUCCESS;

    // MenuBar
    sptr<IUiMenuBar> spMenuBar;
    r = spUiEngine_->createInstance(IID_IUIMENUBAR, (void **)&spMenuBar);
    VERIFY(r, "spUiEngine_.createInstance(<IUiMenuBar>)");

    sptr<IAttributes> spMenuBarAttrbutes;

    // create an attribute
    r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&spMenuBarAttrbutes);
    VERIFY(r, "create instance attributes");

    // initialize MenuBar
    r = spMenuBar->initialize(spMenuBarAttrbutes.get());
    VERIFY(r, "initialize MenuBar");

    UiMenuFlags flags;

    flags.s.start = 1;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 0;
    r = spMenuBar->insertMenuItem("File", 0, flags.ui);
    VERIFY(r, "insert MenuItem");

    flags.s.start = 0;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 1;
    r = spMenuBar->insertMenuItem("Exit", 0, flags.ui);
    VERIFY(r, "insert MenuItem");

    flags.s.start = 1;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 0;
    r = spMenuBar->insertMenuItem("View", 1, flags.ui);
    VERIFY(r, "insert MenuItem");

    flags.s.start = 0;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 0;
    r = spMenuBar->insertMenuItem("ToolBar", 0, flags.ui);
    VERIFY(r, "insert MenuItem");

    flags.s.start = 0;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 0;
    r = spMenuBar->insertMenuItem("StatusBar", 0, flags.ui);
    VERIFY(r, "insert MenuItem");


    flags.s.start = 0;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 0;
    r = spMenuBar->insertMenuItem("Console", 0, flags.ui);
    VERIFY(r, "insert MenuItem");

    flags.s.start = 0;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 1;
    r = spMenuBar->insertMenuItem("Log", 0, flags.ui);
    VERIFY(r, "insert MenuItem");


    flags.s.start = 1;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 1;
    r = spMenuBar->insertMenuItem("Help", 0, flags.ui);
    VERIFY(r, "insert MenuItem");


    flags.s.start = 0;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 1;
    r = spMenuBar->insertMenuItem("About", 0, flags.ui);
    VERIFY(r, "insert MenuItem");


    spUiEngine_->addMenuBar(spMenuBar.get());

    return r;
}

Result App::buildToolBar()
{
    Result r = R_SUCCESS;

    // ToolBar
    sptr<IUiToolBar> spToolBar;
    r = spUiEngine_->createInstance(IID_IUITOOLBAR, (void **)&spToolBar);
    VERIFY(r, "spUiEngine_.createInstance(<IUiToolBar>)");

    char filename[MAX_PATH];
    spApp_->getCurrentPath(filename, MAX_PATH);
    StringCchCatA(filename, MAX_PATH, "fontawesome-webfont.ttf");

    spToolBar->buildToolBarFromTTF(filename, ICON_MIN_FK, ICON_MAX_FK);

    static const Char *label[] =
        {
            ICON_FK_STAR,
            ICON_FK_STAR,
            ICON_FK_STAR_O,
            ICON_FK_USER,
            ICON_FK_TIMES,
            ICON_FK_CHECK,
            ICON_FK_SEARCH,
            ICON_FK_CAMERA,
            ICON_FK_VIDEO_CAMERA,
            ICON_FK_PICTURE_O,
            ICON_FK_CLOCK_O,
            ICON_FK_MINUS_CIRCLE,
            ICON_FK_TIMES_CIRCLE,
            ICON_FK_CHECK_CIRCLE,
            ICON_FK_PENCIL,
            ICON_FK_LIST,
            ICON_FK_DOWNLOAD,
            ICON_FK_UPLOAD,
            ICON_FK_USERS,
            ICON_FK_LINK,
            ICON_FK_BARS,
            ICON_FK_TABLE,
        };

    for (int i = 0; i < sizeof(label) / sizeof(label[0]); ++i)
    {
        spToolBar->addButton(label[i]);
    }

    spUiEngine_->addToolBar(spToolBar.get());

    return r;
}

Result App::buildStatusBar()
{
    Result r = R_SUCCESS;

    // StatusBar
    sptr<IUiStatusBar> spStatusBar;
    r = spUiEngine_->createInstance(IID_IUISTATUSBAR, (void **)&spStatusBar);
    VERIFY(r, "spUiEngine_.createInstance(<IUiStatusBar>)");

    spUiEngine_->addStatusBar(spStatusBar.get());

    return r;
}

Result App::buildLogWindow()
{
    Result r = R_SUCCESS;

    // StatusBar
    sptr<IUiLogWindow> spLogWindow;
    r = spUiEngine_->createInstance(IID_IUILOGWINDOW, (void **)&spLogWindow);
    VERIFY(r, "spUiEngine_.createInstance(<IUiLogWindow>)");

    spUiEngine_->addLogWindow(spLogWindow.get());



    spLogWindow->addMessage("first message!\n");
    return r;
}


Result App::buildFileBrowserWindow()
{
    Result r = R_SUCCESS;

    // StatusBar
    sptr<IUiFileBrowser> spBrowser;
    r = spUiEngine_->createInstance(IID_IFILEBROSWER, (void **)&spBrowser);
    VERIFY(r, "spUiEngine_.createInstance(<IUiLogWindow>)");

    spUiEngine_->addFileBroserWindow(spBrowser.get());


    char path[256];
    spApp_->getCurrentPath(path,256);
    spBrowser->initialize(path);

    return r;
}


Result App::buildImageWindow()
{
    Result r = R_SUCCESS;

    sptr<IUiImageWindow> spImageWindow;
    r = spUiEngine_->createInstance(IID_IUIIMAGEWINDOW, (void **)&spImageWindow);
    VERIFY(r, "spUiEngine_.createInstance(<IUiImageWindow>)");

    char filename[MAX_PATH];
    spApp_->getCurrentPath(filename, MAX_PATH);
    StringCchCatA(filename, MAX_PATH, "demo.png");

    r = spImageWindow->loadImage(filename);

    spUiEngine_->addImageWindow(spImageWindow.get());

    return r;
}

Result App::buildTextureInspector()
{
    Result r = R_SUCCESS;

    sptr<IUiTextureInspector> spTextureInspector;
    r = spUiEngine_->createInstance(IID_IUITEXTURE_INSPECTOR, (void **)&spTextureInspector);
    VERIFY(r, "spUiEngine_.createInstance(<IUiTextureInspector>)");

    char filename[MAX_PATH];
    spApp_->getCurrentPath(filename, MAX_PATH);
    StringCchCatA(filename, MAX_PATH, "demo.png");

    r = spTextureInspector->loadImage(filename);

    spUiEngine_->addTextureInspector(spTextureInspector.get());

    return r;
}

Result App::buildLayout()
{
    Result r = R_SUCCESS;

    return r;
}
