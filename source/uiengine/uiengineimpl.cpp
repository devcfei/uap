#include "comp.h"



// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



namespace uap
{
    const Uuid& UiEngineImpl::uuidof()
    {
        return uuid_;
    }

    Ulong UiEngineImpl::addRef()
    {
        TRACE("UiEngineImpl::addRef\n");

        return InterlockedIncrement(&refcount_);
    }
    Ulong UiEngineImpl::release()
    {
        TRACE("UiEngineImpl::release\n");

        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result UiEngineImpl::queryInterface(const uap::Uuid &, void **)
    {
        return R_OK;
    }

    Result UiEngineImpl::initialize()
    {
        Result r = R_OK;
        TRACE("UiEngineImpl::initialize\n");


        r = initializeWindow();
        if(!UAP_SUCCESS(r))
        {
            TRACE("initializeWindow failed! r = 0x%8.8x\n",r);
            return r;
        }


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

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(hWnd_);
        ImGui_ImplDX9_Init(d3d9Device_.Get());

        return R_OK;
    }


    Result UiEngineImpl::run()
    {
        TRACE("UiEngineImpl::run\n");

        ImGuiIO &io = ImGui::GetIO();

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }

            // Rendering
            ImGui::EndFrame();
            d3d9Device_->SetRenderState(D3DRS_ZENABLE, FALSE);
            d3d9Device_->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
            d3d9Device_->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
            D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*clear_color.w*255.0f), (int)(clear_color.y*clear_color.w*255.0f), (int)(clear_color.z*clear_color.w*255.0f), (int)(clear_color.w*255.0f));
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


        return R_OK;
    }


    // private member functions
    Result UiEngineImpl::initializeWindow()
    {
        Result r = R_OK;
        TRACE("UiEngineImpl::initializeWindow\n");

        WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, 
            GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };

        wc_=wc;
        ::RegisterClassEx(&wc);
        hWnd_ = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX9 Example"), 
            WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, (LPVOID)this);

        TRACE("UiEngineImpl instance, this=0x%p",this);

        // Initialize Direct3D
        r = d3d9CreateDevice(hWnd_);
        if(!UAP_SUCCESS(r))
        {
            d3d9DestoryDevice();
            ::UnregisterClass(wc.lpszClassName, wc.hInstance);
            r= R_ERROR;
        }

        // Show the window
        ::ShowWindow(hWnd_, SW_SHOWDEFAULT);
        ::UpdateWindow(hWnd_);

        return r;
    }

    
    Result UiEngineImpl::reset()
    {
        Result r = R_OK;
        ImGui_ImplDX9_InvalidateDeviceObjects();
        HRESULT hr = d3d9Device_->Reset(&d3dpp_);
        if (hr == D3DERR_INVALIDCALL)
            IM_ASSERT(0);
        ImGui_ImplDX9_CreateDeviceObjects();

        return r;
    }

    Result UiEngineImpl::d3d9CreateDevice(HWND hWnd)
    {
        Result r = R_OK;
        if ((d3d9_ = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        {
            TRACE("Direct3DCreate9 failed!\n");
            r= R_INTERNEL_FAILURE;
            return r;
        }

        // Create the D3DDevice
        ZeroMemory(&d3dpp_, sizeof(d3dpp_));
        d3dpp_.Windowed = TRUE;
        d3dpp_.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dpp_.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
        d3dpp_.EnableAutoDepthStencil = TRUE;
        d3dpp_.AutoDepthStencilFormat = D3DFMT_D16;
        d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
        //d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
        if (d3d9_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp_, &d3d9Device_) < 0)
        {
            TRACE("CreateDevice failed!\n");
            r = R_INTERNEL_FAILURE;
            return r;
        }
        
        return r;
    }

    Result UiEngineImpl::d3d9DestoryDevice()
    {
        Result r = R_OK;

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

        UiEngineImpl* pThis = nullptr;
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;


        pThis = (UiEngineImpl*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        //TRACE("UiEngineImpl instance, this=0x%p",pThis);

        switch (msg)
        {
        case WM_NCCREATE:
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) (( (CREATESTRUCT *) lParam)->lpCreateParams) );
            //TRACE("UiEngineImpl instance, this=0x%p", ( (CREATESTRUCT *) lParam)->lpCreateParams);

            break;
        case WM_SIZE:
            if(pThis)
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
                //const int dpi = HIWORD(wParam);
                //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
                const RECT* suggested_rect = (RECT*)lParam;
                ::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
            }
            break;
        }
        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }





}; //@namespace uap
