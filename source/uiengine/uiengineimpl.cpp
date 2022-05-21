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
        // create the interfaces implemented by uapbe
        if (uapUuidIsEqual(rUuid, IID_UIENGINE))
        {
            IUiEngine *pi = static_cast<IUiEngine *>(this);
            addRef();

            *((IUiEngine **)ppv) = pi;
            r = R_SUCCESS;
        }
        // else if (uapUuidIsEqual(rUuid, IID_IUILAYOUT))
        // {
        //     IUiLayout *pi = static_cast<IUiLayout *>(this);
        //     addRef();

        //     *((IUiLayout **)ppv) = pi;
        //     r = R_SUCCESS;
        // }
        else if (uapUuidIsEqual(rUuid, IID_IUIMENUBAR))
        {
            IUiMenuBar *pi = static_cast<IUiMenuBar *>(this);
            addRef();

            *((IUiMenuBar **)ppv) = pi;
            r = R_SUCCESS;
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
        r = spApp_->createInterface(IID_LOGTRACE, (void **)&spLogTrace_);
        if (!UAP_SUCCESS(r))
        {
            UAP_TRACE("createInterface failed! r = 0x%8.8x\n", r);
            return r;
        }

        r = spLogTrace_->initialize(spApp_.get(), MODULE_NAME, spAppAttributes_.get());
        VERBOSE("initialize ILogTrace - r = 0x%8.8x\n", r);


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
        VERBOSE("UiEngineImpl::run\n");

        ImGuiIO &io = ImGui::GetIO();


        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        colorClear_ = clear_color;

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

            // Start the Dear ImGui frame
            ImGui_ImplDX9_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();


            drawLayout();

            // Rendering
            ImGui::EndFrame();
            d3d9Device_->SetRenderState(D3DRS_ZENABLE, FALSE);
            d3d9Device_->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
            d3d9Device_->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
            D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(colorClear_.x * colorClear_.w * 255.0f),
                                                  (int)(colorClear_.y * colorClear_.w * 255.0f),
                                                  (int)(colorClear_.z * colorClear_.w * 255.0f),
                                                  (int)(colorClear_.w * 255.0f));
            d3d9Device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
            if (d3d9Device_->BeginScene() >= 0)
            {
                ImGui::Render();
                ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
                d3d9Device_->EndScene();
            }

            // Update and Render additional Platform Windows
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
            }

            HRESULT result = d3d9Device_->Present(NULL, NULL, NULL, NULL);

            // Handle loss of D3D9 device
            if (result == D3DERR_DEVICELOST && d3d9Device_->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
                reset();
        }

        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        d3d9DestoryDevice();
        ::DestroyWindow(hWnd_);
        ::UnregisterClass(wc_.lpszClassName, wc_.hInstance);

        return R_SUCCESS;
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
                               WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, (LPVOID)this);

        VERBOSE("UiEngineImpl instance, this=0x%p\n", this);

        // Initialize Direct3D
        r = d3d9CreateDevice(hWnd_);
        if (!UAP_SUCCESS(r))
        {
            d3d9DestoryDevice();
            ::UnregisterClass(wc.lpszClassName, wc.hInstance);
            r = R_ERROR;
        }

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
        ImFontConfig config;
        config.MergeMode = true;
        config.GlyphMinAdvanceX = 18.0f; // Use if you want to make the icon monospaced
        static const ImWchar icon_ranges[] = { ICON_MIN_FK, ICON_MAX_FK, 0 };
        io.Fonts->AddFontFromFileTTF("fontawesome-webfont.ttf", 18.0f, &config, icon_ranges);

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
        ImGui_ImplDX9_Init(d3d9Device_.Get());

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


    Result UiEngineImpl::reset()
    {
        Result r = R_SUCCESS;
        ImGui_ImplDX9_InvalidateDeviceObjects();
        HRESULT hr = d3d9Device_->Reset(&d3dpp_);
        if (hr == D3DERR_INVALIDCALL)
            IM_ASSERT(0);
        ImGui_ImplDX9_CreateDeviceObjects();

        return r;
    }

    Result UiEngineImpl::d3d9CreateDevice(HWND hWnd)
    {
        Result r = R_SUCCESS;
        if ((d3d9_ = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        {
            r = R_INTERNEL_FAILURE;
        }

        VERIFY(r, "Direct3DCreate9");

        // Create the D3DDevice
        ZeroMemory(&d3dpp_, sizeof(d3dpp_));
        d3dpp_.Windowed = TRUE;
        d3dpp_.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dpp_.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
        d3dpp_.EnableAutoDepthStencil = TRUE;
        d3dpp_.AutoDepthStencilFormat = D3DFMT_D16;
        d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_ONE; // Present with vsync
        // d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
        if (d3d9_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp_, &d3d9Device_) < 0)
        {
            r = R_INTERNEL_FAILURE;
        }

        VERIFY(r, "IDirect3D9::CreateDevice");

        return r;
    }

    Result UiEngineImpl::d3d9DestoryDevice()
    {
        Result r = R_SUCCESS;

        d3d9Device_.Reset();
        d3d9_.Reset();

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
                if (pThis->d3d9Device_ != NULL && wParam != SIZE_MINIMIZED)
                {
                    pThis->d3dpp_.BackBufferWidth = LOWORD(lParam);
                    pThis->d3dpp_.BackBufferHeight = HIWORD(lParam);
                    pThis->reset();
                }
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
