#include "comp.h"



// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace uap
{

    Ulong UiEngineImpl::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong UiEngineImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result UiEngineImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        if (uapUuidIsEqual(rUuid, IID_UIENGINE))
        {
            IUiEngine *pi = static_cast<IUiEngine *>(this);
            addRef();

            *((IUiEngine **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }

    Result UiEngineImpl::createInstance(const Uuid& rUuid, void ** ppv)
    {
        Result r = R_INVALID_PARAMETERS;
        if (uapUuidIsEqual(rUuid, IID_IUIMENUBAR))
        {
            r = UiMenuBarImpl::createInstance(ppv);
        }
        else if (uapUuidIsEqual(rUuid, IID_IUIIMAGEWINDOW))
        {
            r = UiImageWindowImpl::createInstance(spBackend_.get(),(IUiImageWindow **)ppv);
        }
        else if (uapUuidIsEqual(rUuid, IID_IUITEXTURE_INSPECTOR))
        {
            r = UiTextureInspectorImpl::createInstance(spBackend_.get(),(IUiTextureInspector **)ppv);
        }


        return r;
    }


    Result UiEngineImpl::initialize(IApplication *piApp, IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;

        spApp_ = piApp;
        spAppAttributes_ = piAttributes;


        spAppAttributes_->getUlong(UUID_LOGTRACE_ATTRIBUTES, logAttributes_.ul);

        // initialize the log trace
        r = spApp_->createInstance(IID_LOGTRACE, (void **)&spLogTrace_);
        if (!UAP_SUCCESS(r))
        {
            UAP_TRACE("createInstance failed! r = 0x%8.8x\n", r);
            return r;
        }

        r = spLogTrace_->initialize(spApp_.get(), MODULE_NAME, spAppAttributes_.get());
        VERBOSE("initialize ILogTrace - r = 0x%8.8x\n", r);


        // create the backend

        beType_ = BT_D3D9;
        beType_ = BT_D3D11;

        if (beType_ == BT_D3D9)
        {
            r = UiEngineBackendDx9Impl::createInstance((void **)&spBackend_);
        }
        else if (beType_ = BT_D3D11)
        {
            r = UiEngineBackendDx11Impl::createInstance((void **)&spBackend_);

        }
        if (!UAP_SUCCESS(r))
        {
            UAP_TRACE("backend - createInstance failed! r = 0x%8.8x\n", r);
            return r;
        }
        // initialize the backend
        r = spBackend_->initializeBackend(this, nullptr);

        // create layout      
        r = createLayout();
        VERBOSE("createLayout - r = 0x%8.8x\n", r);

        return r;
    }

    Result UiEngineImpl::startup()
    {
        Result r = R_SUCCESS;

        VERBOSE("UiEngineImpl::startup\n");

        r = initializeWindow();
        VERIFY(r, "initializeWindow")

        r = initializeBackEnd();
        VERIFY(r, "initializeBackEnd")

        return r;
    }

    Result UiEngineImpl::run()
    {
        Result r = R_SUCCESS;
        VERBOSE("UiEngineImpl::run\n");

        // Main loop
        bool done = false;
        while (!done)
        {
            // Poll and handle messages (inputs, window resize, etc.)
            // See the WndProc() function below for our to dispatch events to the Win32 backend.
            MSG msg;
            while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
                if (msg.message == WM_QUIT)
                    done = true;
            }
            if (done)
                break;

            spBackend_->newFrame();

            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            drawLayout();

            spBackend_->render();


        }


        spBackend_->shutdown();

        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        spBackend_->destoryDevice();

        ::DestroyWindow(hWnd_);
        ::UnregisterClass(wc_.lpszClassName, wc_.hInstance);

        return r;
    }


    Result UiEngineImpl::addMenuBar(IUiMenuBar* piMenuBar)
    {
        Result r = R_SUCCESS;

        spMenuBar_ = piMenuBar;

        return r;
    }
    Result UiEngineImpl::getMenuBar(IUiMenuBar** ppiMenuBar)
    {
        Result r = R_SUCCESS;

        *ppiMenuBar = spMenuBar_.get();
        // Don't forget to add reference count
        (*ppiMenuBar)->addRef();

        return r;
    }


    Result UiEngineImpl::addImageWindow(IUiImageWindow* piImageWindow)
    {
        Result r = R_SUCCESS;
        spImageWindows_.push_back(piImageWindow);
        return r;
    }

    Result UiEngineImpl::getImageWindow(IUiImageWindow** ppiImageWindow)
    {
        Result r = R_SUCCESS;
        *ppiImageWindow = spImageWindows_[0].get();
        // Don't forget to add reference count
        (*ppiImageWindow)->addRef();
        return r;
    }


    Result UiEngineImpl::addTextureInspector(IUiTextureInspector* piTextureInspector)
    {
        Result r = R_SUCCESS;
        spTextureInspector_.push_back(piTextureInspector);
        return r;
    }

    Result UiEngineImpl::getTextureInspector(IUiTextureInspector** ppiTextureInspector)
    {
        Result r = R_SUCCESS;
        *ppiTextureInspector = spTextureInspector_[0].get();
        // Don't forget to add reference count
        (*ppiTextureInspector)->addRef();
        return r;
    }




    // private member functions
    Result UiEngineImpl::initializeWindow()
    {
        Result r = R_SUCCESS;
        VERBOSE("UiEngineImpl::initializeWindow\n");

        WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L,
                         GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("wcImGui"), NULL};


        Char appName[256];
        spAppAttributes_->getString(UUID_APP_NAME, appName,256,nullptr);


        wc_ = wc;
        ::RegisterClassEx(&wc);
        hWnd_ = ::CreateWindow(wc.lpszClassName, appName,
                               WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800,
                                NULL, NULL, wc.hInstance, (LPVOID)this);

        VERBOSE("UiEngineImpl instance, this=0x%p\n", this);

        // Initialize Direct3D devicde

        sptr<IAttributes> spDeviceAttributes;
        r = spApp_->createInstance(IID_IATTRIBUTES, (void**)&spDeviceAttributes);
        VERIFY(r, "create attributes for backend render device");

        spDeviceAttributes->setPtr(UUID_IUIENGINE_BACKEND_HWND, hWnd_);


        r = spBackend_->createDevice(spDeviceAttributes.get());
        VERIFY(r, "create backend render device");


        // Show the window
        ::ShowWindow(hWnd_, SW_SHOWDEFAULT);
        ::UpdateWindow(hWnd_);

        return r;
    }

    Result UiEngineImpl::initializeBackEnd()
    {
        Result r = R_SUCCESS;

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
        // io.ConfigViewportsNoAutoMerge = true;
        // io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsClassic();


        io.Fonts->AddFontDefault();

        char path[MAX_PATH];
        spApp_->getCurrentPath(path,MAX_PATH);
        StringCbCatA(path,MAX_PATH,"fontawesome-webfont.ttf");


        VERBOSE("front path = %s\n",path);
        

        ImFontConfig config;
        config.MergeMode = true;
        config.GlyphMinAdvanceX = 18.0f; // Use if you want to make the icon monospaced
        static const ImWchar icon_ranges[] = { ICON_MIN_FK, ICON_MAX_FK, 0 };
        io.Fonts->AddFontFromFileTTF(path, 18.0f, &config, icon_ranges);



        // static CHAR path[MAX_PATH];

        // if (SUCCEEDED(SHGetFolderPathA(NULL,
        //     CSIDL_PERSONAL | CSIDL_FLAG_CREATE,
        //     NULL,
        //     0,
        //     path)))
        // {
        //     StringCchCatA(path, MAX_PATH - 1, "\\demo\\");
        // }

        // StringCchCatA(path, MAX_PATH - 1, "demo.ini");


        //io.IniFilename = path; 


        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;

            style.TabRounding = 0.0f;
            style.Colors[ImGuiCol_Button].w = 1.0f;
            style.Colors[ImGuiCol_Button].x = 0.0f;
            style.Colors[ImGuiCol_Button].y = 0.0f;
            style.Colors[ImGuiCol_Button].z = 0.0f;

            style.WindowMenuButtonPosition = ImGuiDir_Right;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(hWnd_);

        spBackend_->setup();


        ImGuiTexInspect::Init();
        ImGuiTexInspect::CreateContext();

        return r;
    }

    Result UiEngineImpl::createLayout()
    {
        Result r = R_SUCCESS;

        // get layout style
        LayoutStyle style;
        r = spAppAttributes_->getUint(UUID_UILAYOUT_STYLE, (Uint&)style);
        if(!UAP_SUCCESS(r))
        {
            r = UiLayoutImplDemo::createInstance((void**)&spLayout_);            
        }
        else
        {
            if(style == LAYOUT_STYLE_SIMPLE)
            {
                r = UiLayoutImplSimple::createInstance((void**)&spLayout_);

            }
            else if(style == LAYOUT_STYLE_DOCKING)
            {
                r = UiLayoutImplDocking::createInstance((void**)&spLayout_);
                VERBOSE("create docking style layout, r = 0x%8.8x\n", r);

                r = spLayout_->initializeLayout(this, nullptr);
                VERBOSE("initialize the layout, r = 0x%8.8x\n", r);

            }
            else if(style == LAYOUT_STYLE_DEMO)
            {
                r = UiLayoutImplDemo::createInstance((void**)&spLayout_);
                
            }
        
        }   

        return r;
    }

    Result UiEngineImpl::drawLayout()
    {
        Result r = R_SUCCESS;

        r = spLayout_->draw();

        return r;
    }


    Result UiEngineImpl::resize(Uint width, Uint height)
    {
        Result r = R_SUCCESS;

        r = spBackend_->resize(width,height);

        return r;
    }




    // Win32 message handler
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.  
    LRESULT WINAPI UiEngineImpl::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {

        UiEngineImpl *pThis = nullptr;
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        pThis = (UiEngineImpl *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        // UAP_TRACE("UiEngineImpl instance, this=0x%p",pThis);

        switch (msg)
        {
        case WM_NCCREATE:
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)(((CREATESTRUCT *)lParam)->lpCreateParams));
            // UAP_TRACE("UiEngineImpl instance, this=0x%p", ( (CREATESTRUCT *) lParam)->lpCreateParams);

            break;
        case WM_SIZE:
            if (pThis)
            {
                pThis->resize(LOWORD(lParam), HIWORD(lParam));
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        case WM_DPICHANGED:
            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
            {
                // const int dpi = HIWORD(wParam);
                // printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
                const RECT *suggested_rect = (RECT *)lParam;
                ::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
            }
            break;
        }
        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }

}; //@namespace uap
