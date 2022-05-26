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
    r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&spAttributes);
    RESULT_CHECK(r, "createInstance IID_IATTRIBUTES");

    // application initialize with log trace and components
    Uint initFlags = APP_INIT_LOGTRACE_ENALBE | APP_INIT_COMPONENT_ENALBE;
    spAttributes->setUint(UUID_APP_INIT_FLAGS, initFlags);

    r = spApp_->initialize(spAttributes.get());
    RESULT_CHECK(r, "app initialize");

    return r;
}

Result App::startUI()
{
    Result r;

    // create the engine
    r = spApp_->createInstance(IID_UIENGINE, (void **)&spUiEngine_);
    RESULT_CHECK(r, "create instance UI engine");

    // create an attribute
    r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&spUiAttributes_);
    RESULT_CHECK(r, "create instance attributes");

    //
    //
    //

    // set application name
    spUiAttributes_->setString(UUID_APP_NAME, "Demo", 4);

    // set application layout style
    LayoutStyle style;
    style = LAYOUT_STYLE_SIMPLE;
    style = LAYOUT_STYLE_DOCKING;
    // style = LAYOUT_STYLE_DEMO;
    spUiAttributes_->setUint(UUID_UILAYOUT_STYLE, style);

    // set log
    LogAttributes logAttr = {0};

    logAttr.s.defaultLevel = LT_ALL;
    logAttr.s.enableAppLogTrace = 1;
    logAttr.s.enableDebugTrace = 1;
    logAttr.s.enableLevelTag = 1;
    spUiAttributes_->setUlong(UUID_LOGTRACE_ATTRIBUTES, logAttr.ul);

    // initialize the UI engine
    r = spUiEngine_->initialize(spApp_.get(), spUiAttributes_.get());
    RESULT_CHECK(r, "initialze UI engine");

    // startup
    r = spUiEngine_->startup();

    // set layout
    r = setLayout();

    // run
    r = spUiEngine_->run();

    return r;
}

Result App::setLayout()
{
    Result r = R_SUCCESS;

    // build the MenuBar
    r = buildMenuBar();
    RESULT_CHECK(r, "build MenuBar");

    // build the ToolBar
    r = buildToolBar();
    RESULT_CHECK(r, "build ToolBar");

    // build the StatusBar
    r = buildStatusBar();
    RESULT_CHECK(r, "build StatusBar");

    // build the ImageWindow
    r = buildImageWindow();
    RESULT_CHECK(r, "build ImageWindow");

    // build the TextureInspector
    r = buildTextureInspector();
    RESULT_CHECK(r, "build TextureInspector");

    // build the layout
    r = buildLayout();
    RESULT_CHECK(r, "build UI layout");

    return r;
}

Result App::buildMenuBar()
{
    Result r = R_SUCCESS;

    // MenuBar
    sptr<IUiMenuBar> spMenuBar;
    r = spUiEngine_->createInstance(IID_IUIMENUBAR, (void **)&spMenuBar);
    RESULT_CHECK(r, "spUiEngine_.createInstance(<IUiMenuBar>)");

    sptr<IAttributes> spMenuBarAttrbutes;

    // create an attribute
    r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&spMenuBarAttrbutes);
    RESULT_CHECK(r, "create instance attributes");

    // initialize MenuBar
    r = spMenuBar->initialize(spMenuBarAttrbutes.get());
    RESULT_CHECK(r, "initialize MenuBar");

    UiMenuFlags flags;

    flags.s.start = 1;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 0;
    r = spMenuBar->insertMenuItem("File", 0, flags.ui);
    RESULT_CHECK(r, "insert MenuItem");

    flags.s.start = 1;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 1;
    r = spMenuBar->insertMenuItem("Exit", 0, flags.ui);
    RESULT_CHECK(r, "insert MenuItem");

    flags.s.start = 1;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 0;
    r = spMenuBar->insertMenuItem("View", 1, flags.ui);
    RESULT_CHECK(r, "insert MenuItem");

    flags.s.start = 0;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 0;
    r = spMenuBar->insertMenuItem("ToolBar", 0, flags.ui);
    RESULT_CHECK(r, "insert MenuItem");

    flags.s.start = 0;
    flags.s.checked = 0;
    flags.s.enable = 1;
    flags.s.end = 1;
    r = spMenuBar->insertMenuItem("StatusBar", 0, flags.ui);
    RESULT_CHECK(r, "insert MenuItem");

    spUiEngine_->addMenuBar(spMenuBar.get());

    return r;
}

Result App::buildToolBar()
{
    Result r = R_SUCCESS;

    // ToolBar
    sptr<IUiToolBar> spToolBar;
    r = spUiEngine_->createInstance(IID_IUITOOLBAR, (void **)&spToolBar);
    RESULT_CHECK(r, "spUiEngine_.createInstance(<IUiToolBar>)");

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
    RESULT_CHECK(r, "spUiEngine_.createInstance(<IUiStatusBar>)");

    spUiEngine_->addStatusBar(spStatusBar.get());

    return r;
}

Result App::buildImageWindow()
{
    Result r = R_SUCCESS;

    sptr<IUiImageWindow> spImageWindow;
    r = spUiEngine_->createInstance(IID_IUIIMAGEWINDOW, (void **)&spImageWindow);
    RESULT_CHECK(r, "spUiEngine_.createInstance(<IUiImageWindow>)");

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
    RESULT_CHECK(r, "spUiEngine_.createInstance(<IUiTextureInspector>)");

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
