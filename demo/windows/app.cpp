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

    std::string strAppConfig = strAppPath_+ "\\default.toml";
    r= spToml_->initialize(spApp_.get(), strAppConfig.c_str());
    VERIFY(r, "initial toml");


    r =initApplicationConfiguration();
    VERIFY(r, "initial app config");


    r =initAppEvent();
    VERIFY(r, "initial app event");


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


    spAttributes->setUint(APPLICATION_ATTRIBUTE_CONFIGURATION, ac.ui);

    Char appPath[256];
    spApp_->getCurrentPath(appPath, 256);
    std::string str=appPath;
    str+="\\app.log";
    spAttributes->setString(APPLICATION_ATTRIBUTE_LOGFILE_PATH,str.c_str(),str.length());

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

Result App::initAppEvent()
{
    Result r;


    r = spApp_->createInstance(IID_IEVENT, (void **)&spEvent_);
    VERIFY(r, "createInstance IID_IEVENT");


    r = spEvent_->initialize(nullptr);
    VERIFY(r, "event initialize");


    r = EventDispatcherImpl::createInstance(spEventDispatcher_.getaddrof(), this);
    VERIFY(r, "event dispatch create");


    r = spEvent_->addDispatcher(spEventDispatcher_.get());
    VERIFY(r, "event add dispatcher");
    

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
    VERIFY(r, "initial the engine");

    // create the draw
    r = spUiEngine_->createInstance(IID_IDRAW, (void **)&spDraw_);
    VERIFY(r, "create instance UI engine draw");

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


    // set application name
    spUiAttributes_->setString(UUID_APP_NAME, "Demo", 4);

    int layout = 0;
    int backend = 0;
    spToml_->getInt("uiengine", "layout", layout);
    spToml_->getInt("uiengine", "backend", backend);
    spToml_->getBool("uiengine", "notitlebar", notitlebar_);

    // set application layout style
    LayoutStyle style = LAYOUT_STYLE_SIMPLE;
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
    if(notitlebar_)
        spUiAttributes_->setUint(UUID_UILAYOUT_DISABLE_SYSTEM_TITLEBAR, 1);


    


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
    BackendType betype;
    switch(backend)
    {
    case 0: betype = BT_D3D9; break;
    case 1: betype = BT_D3D11; break;
    default: betype = BT_D3D9; break;
    }
    r = spUiEngine_->initialize(spApp_.get(), spUiAttributes_.get(), betype);
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


    // build the Log Window
    r = buildLogWindow();
    VERIFY(r, "build LogWindow");


    // build the File Browse Window
    r = buildFileBrowserWindow();
    VERIFY(r, "build file browser");
    
    r = buildGenericWindow();
    VERIFY(r, "build generic window");
    

    r = buildSettingWindow();
    VERIFY(r, "build setting window");


    // build the layout
    r = buildLayout();
    VERIFY(r, "build UI layout");

    return r;
}

Result App::buildMenuBar()
{
    Result r = R_SUCCESS;

    // Menu

    // Menu File
    r = spUiEngine_->createInstance(IID_IMENU, (void **)&spMenuFile_);
    VERIFY(r, "spUiEngine_.createInstance(<IMenu>)");

    r = spMenuFile_->initialize(nullptr, spEvent_.get());
    VERIFY(r, "menu file, initalize");

    spMenuFile_->addItem("New", false, NULL, Event_FileNew);
    spMenuFile_->addItem("Open File...", false, NULL, Event_FileOpen);
    spMenuFile_->addItem("Open Folder...", false, NULL, Event_FolderOpen);
    spMenuFile_->addItem("Save as...", false, NULL, Event_SaveAs);
    spMenuFile_->addSeparator();
    spMenuFile_->addItem("Settings ...", false, NULL, Event_OpenSettings);

    spMenuFile_->addSeparator();
    spMenuFile_->addItem("Exit", false, NULL, Event_AppExit);

    // Menu View
    r = spUiEngine_->createInstance(IID_IMENU, (void **)&spMenuView_);
    VERIFY(r, "spUiEngine_.createInstance(<IMenu>)");

    r = spMenuView_->initialize(nullptr, spEvent_.get());
    VERIFY(r, "menu view, initalize");

    spMenuView_->addItem("ToolBar", false, NULL, Event_ViewToolBar);
    spMenuView_->addItem("StatusBar", false, NULL, Event_ViewStatusBar);

    // Menu View panel
    r = spUiEngine_->createInstance(IID_IMENU, (void **)&spMenuViewPanelWindow_);
    VERIFY(r, "spUiEngine_.createInstance(<IMenu>)");

    r = spMenuViewPanelWindow_->initialize(nullptr, spEvent_.get());
    VERIFY(r, "menu view panel, initalize");

    spMenuViewPanelWindow_->addItem("Generic", false, NULL, Event_ViewPanelGeneric);
    spMenuViewPanelWindow_->addItem("File Browser", false, NULL, Event_ViewPanelFileBrowser);
    spMenuViewPanelWindow_->addItem("Log", false, NULL, Event_ViewPanelLog);

    spMenuView_->addSeparator();
    spMenuView_->addItem("Panel", false, spMenuViewPanelWindow_.get(), 0);

    r = spUiEngine_->createInstance(IID_IMENU, (void **)&spMenuHelp_);
    VERIFY(r, "spUiEngine_.createInstance(<IMenu>)");

    r = spMenuHelp_->initialize(nullptr, spEvent_.get());
    VERIFY(r, "menu help, initalize");

    spMenuHelp_->addItem("About", false, NULL, Event_AppAbout);
#if defined(_DEBUG)
    spMenuHelp_->addSeparator();
    spMenuHelp_->addItem("ImGui Demo", false, NULL, Event_HelpImGuiDemo);
    spMenuHelp_->addItem("ImPlot Demo", false, NULL, Event_HelpImPlotDemo);
#endif

    r = spUiEngine_->createInstance(IID_IMENU, (void **)&spMenuTop_);
    VERIFY(r, "spUiEngine_.createInstance(<IMenu>)");
    spMenuTop_->addItem("File", false, spMenuFile_.get(), 0);
    spMenuTop_->addItem("View", false, spMenuView_.get(), 0);
    spMenuTop_->addItem("Help", false, spMenuHelp_.get(), 0);

    // MenuBar
    r = spUiEngine_->createInstance(IID_IMENUBAR, (void **)&spMenuBar_);
    VERIFY(r, "spUiEngine_.createInstance(<IMenuBar>)");

    sptr<IAttributes> spMenuBarAttrbutes;

    // create an attribute
    r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&spMenuBarAttrbutes);
    VERIFY(r, "create instance attributes");

    // initialize MenuBar
    std::string logoPath = strAppPath_ + "\\logo.png";
    r = spMenuBar_->initialize(notitlebar_ ==1? true:false, logoPath.c_str() ,  spMenuBarAttrbutes.get());
    VERIFY(r, "initialize MenuBar");

    r = spMenuBar_->setMenu(spMenuTop_.get());
    VERIFY(r, "menubar setMenu");

    return r;
}

Result App::buildToolBar()
{
    Result r = R_SUCCESS;

    // ToolBar
    r = spUiEngine_->createInstance(IID_ITOOLBAR, (void **)&spToolBar_);
    VERIFY(r, "spUiEngine_.createInstance(<IToolBar>)");

    char filename[MAX_PATH];
    spApp_->getCurrentPath(filename, MAX_PATH);
    StringCchCatA(filename, MAX_PATH, "\\fa-solid-900.ttf");

    spToolBar_->buildToolBarFromTTF(filename, ICON_MIN_FA, ICON_MAX_FA);

    static const Char *label[] =
        {
            ICON_FA_FILE,         // new
            ICON_FA_FOLDER_OPEN,  // open
            ICON_FA_SAVE,  // save
            ICON_FA_CUT,   // cut
            ICON_FA_CLONE,        // copy
            ICON_FA_PASTE,      // paste
            ICON_FA_SEARCH_MINUS,    // zoom in
            ICON_FA_SEARCH_PLUS,   // zoom out
            ICON_FA_DOWNLOAD,       // download
            ICON_FA_UPLOAD,         // upload
            ICON_FA_COG,            // settings
            ICON_FA_INFO,    // about info
        };

    for (int i = 0; i < sizeof(label) / sizeof(label[0]); ++i)
    {
        spToolBar_->addButton(label[i]);
    }

    return r;
}

Result App::buildStatusBar()
{
    Result r = R_SUCCESS;

    // StatusBar
    r = spUiEngine_->createInstance(IID_ISTATUSBAR, (void **)&spStatusBar_);
    VERIFY(r, "spUiEngine_.createInstance(<IStatusBar>)");


    return r;
}

Result App::buildLogWindow()
{
    Result r = R_SUCCESS;

    // LogWindow
    r = spUiEngine_->createInstance(IID_ILOGWINDOW, (void **)&spLogWindow_);
    VERIFY(r, "spUiEngine_.createInstance(<ILogWindow>)");


    spLogWindow_->addMessage("first message!\n");
    return r;
}


Result App::buildFileBrowserWindow()
{
    Result r = R_SUCCESS;

    r = spUiEngine_->createInstance(IID_IFILEBROWSERWINDOW, (void **)&spFileBrowserWindow_);
    VERIFY(r, "spUiEngine_.createInstance(<ILogWindow>)");

    // char path[256];
    // spApp_->getCurrentPath(path,256);
    // spFileBrowserWindow_->addPath(path);



    // create an attribute
    sptr<IAttributes> attr;
    r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&attr);
    VERIFY(r, "create instance attributes");


    r = attr->setUint(FILEBROWSERWINDOW_ATTRBUTE_FILECLICKED_EVENT_ID, Event_FileBrowserClicked);
    VERIFY(r, "set FILEBROWSERWINDOW_ATTRBUTE_FILECLICKED_EVENT_ID");



    // initialize the panel window with attributes
    sptr<IWindow> spWindow;
    r = spFileBrowserWindow_.as(&spWindow);
    VERIFY(r, "as IWindow");

    r = spWindow->initialize(attr.get(), spEvent_.get());
    VERIFY(r, "initialize IWindow");


    return r;
}

Result App::buildGenericWindow()
{
    Result r = R_SUCCESS;

    // Panel Window
    r = spUiEngine_->createInstance(IID_IWINDOW, (void **)&spGenericWindow_);
    VERIFY(r, "spUiEngine_.createInstance(<IWindow>)");

    // create an attribute
    sptr<IAttributes> attr;
    r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&attr);
    VERIFY(r, "create instance attributes");

    std::string title = "Generic Window";
    r = attr->setString(WINDOW_ATTRIBUTE_TITLE, title.c_str(), title.length());
    VERIFY(r, "set WINDOW_ATTRIBUTE_TITLE");

    // initialize the panel window with attributes
    r = spGenericWindow_->initialize(attr.get(), nullptr);
    VERIFY(r, "initialize IWindow");


    r = GenericFrameImpl::createInstance(spGenericWindowFrame_.getaddrof(), spDraw_.get());
    VERIFY(r, "create generic window frame");

    spGenericWindow_->setFrame(spGenericWindowFrame_.get());


    return r;
}


Result App::buildSettingWindow()
{
    Result r = R_SUCCESS;
    r = spUiEngine_->createInstance(IID_IWINDOW, (void **)&spSettingWindow_);
    VERIFY(r, "spUiEngine_.createInstance(<IWindow>)");

    // create an attribute
    sptr<IAttributes> attr;
    r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&attr);
    VERIFY(r, "create instance attributes");

    std::string title = "Settings";
    r = attr->setString(WINDOW_ATTRIBUTE_TITLE, title.c_str(), title.length());
    VERIFY(r, "set WINDOW_ATTRIBUTE_TITLE");


    // initialize the setting window with attributes
    r = spSettingWindow_->initialize(attr.get(), nullptr);
    VERIFY(r, "initialize IWindow");


    r = SettingFrameImpl::createInstance(spSettingWindowFrame_.getaddrof(), spDraw_.get());
    VERIFY(r, "create setting window frame");
    spSettingWindow_->setFrame(spSettingWindowFrame_.get());


    return r;
}


Result App::buildLayout()
{
    Result r = R_SUCCESS;

    // get layout and add the draw to the layout
    r = spUiEngine_->getLayout(spLayout_.getaddrof());
    VERIFY(r, "get layout");

    sptr<IFrameWindowElements> spUiElement;
    r = spLayout_.as(&spUiElement);
    VERIFY(r, "as uielement");

    // add menubar
    r = spUiElement->addMenuBar(spMenuBar_.get());
    VERIFY(r, "add menubar");

    // add toolbar
    r = spUiElement->addToolBar(spToolBar_.get());
    VERIFY(r, "add menubar");

    // add statusbar
    r = spUiElement->addStatusBar(spStatusBar_.get());
    VERIFY(r, "add statusbar");

    // add generic window
    r = spLayout_->addFrame(spGenericWindow_.get());
    VERIFY(r, "add panel window draw to layout");

    // add log window
    r = spLayout_->addFrame(spLogWindow_.get());
    VERIFY(r, "add log window draw to layout");


    // add file browser window
    r = spLayout_->addFrame(spFileBrowserWindow_.get());
    VERIFY(r, "add file browser window draw to layout");


    // add setting window
    r = spLayout_->addFrame(spSettingWindow_.get());
    VERIFY(r, "add setting window draw to layout");


    return r;
}




Result App::openImageFile(std::tstring filename)
{
    Result r;


    r = fileListManager_.addFile(filename);
    if(UAP_SUCCESS(r))
    {

        sptr<IImageWindow> spImageWindow;

        r = spUiEngine_->createInstance(IID_IIMAGEWINDOW, (void **)&spImageWindow);
        VERIFY(r, "spUiEngine_.createInstance(<IImageWindow>)");


        USES_CONVERSION;

        std::string file = T2A(filename.c_str());



        // create an attribute
        sptr<IAttributes> attr;
        r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&attr);
        VERIFY(r, "create instance attributes");


        
        std::string title = file;

        PathStripPathA(title.data());
        
        r = attr->setString(WINDOW_ATTRIBUTE_TITLE, title.c_str(), title.length());
        VERIFY(r, "set WINDOW_ATTRIBUTE_TITLE");

        r = attr->setUint(WINDOW_CLOSE_EVENTID, Event_WindowClosed);
        VERIFY(r, "set WINDOW_CLOSE_EVENTID");


        // initialize the panel window with attributes
        sptr<IWindow> spWindow;
        r = spImageWindow.as(&spWindow);
        VERIFY(r, "as IWindow");

        r = spWindow->initialize(attr.get(), spEvent_.get());
        VERIFY(r, "initialize IWindow");

        r = spImageWindow->loadImage(file.c_str());
        VERIFY(r, "load image");


        // add image window
        r = spLayout_->addFrame(spImageWindow.get());
        VERIFY(r, "add image window draw to layout");

        vecImageWindows_.push_back(spImageWindow);


        // map the window and file
        mapWindowFile_.insert(std::make_pair(spWindow.get(), filename));

    }


    return r;
}


Result App::openImageFileByTextureInspector(std::tstring filename)
{
    Result r;


    r = fileListManager_.addFile(filename);
    if(UAP_SUCCESS(r))
    {

        sptr<ITextureInspector> spTextureInspector;

        r = spUiEngine_->createInstance(IID_ITEXTURE_INSPECTOR, (void **)&spTextureInspector);
        VERIFY(r, "spUiEngine_.createInstance(<IImageWindow>)");


        USES_CONVERSION;

        std::string file = T2A(filename.c_str());



        // create an attribute
        sptr<IAttributes> attr;
        r = spApp_->createInstance(IID_IATTRIBUTES, (void **)&attr);
        VERIFY(r, "create instance attributes");


        
        std::string title = file;

        PathStripPathA(title.data());
        
        r = attr->setString(WINDOW_ATTRIBUTE_TITLE, title.c_str(), title.length());
        VERIFY(r, "set WINDOW_ATTRIBUTE_TITLE");

        r = attr->setUint(WINDOW_CLOSE_EVENTID, Event_WindowClosed);
        VERIFY(r, "set WINDOW_CLOSE_EVENTID");


        // initialize the panel window with attributes
        sptr<IWindow> spWindow;
        r = spTextureInspector.as(&spWindow);
        VERIFY(r, "as IWindow");

        r = spWindow->initialize(attr.get(), spEvent_.get());
        VERIFY(r, "initialize IWindow");

        r = spTextureInspector->loadImage(file.c_str());
        VERIFY(r, "load image");


        // add image window
        r = spLayout_->addFrame(spTextureInspector.get());
        VERIFY(r, "add image window draw to layout");

        vecTextureInspectorWindows_.push_back(spTextureInspector);


        // map the window and file
        mapWindowFile_.insert(std::make_pair(spWindow.get(), filename));

    }


    return r;
}