#include "common.h"



namespace uap
{

    Ulong UiEngineBackendDx11Impl::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong UiEngineBackendDx11Impl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            UAP_TRACE("UiEngineBackendDx11Impl delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiEngineBackendDx11Impl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        // create the interfaces implemented by
        if (uapUuidIsEqual(rUuid, IID_IUIENGINE_BACKEND))
        {
            IUiEngineBackend *pi = static_cast<IUiEngineBackend *>(this);
            addRef();

            *((IUiEngineBackend **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }



    Result UiEngineBackendDx11Impl::initializeBackend(IUiEngine *piUiEngine, IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;

        INFO("UiEngineBackendDx11Impl::initializeBackend\n");
        
        return r;
    }

    Result UiEngineBackendDx11Impl::newFrame()
    {
        Result r = R_SUCCESS;
        ImGui_ImplDX11_NewFrame();
        return r;
    }

    Result UiEngineBackendDx11Impl::render()
    {
        Result r = R_SUCCESS;

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        ImVec4 colorClear_ = clear_color;
        ImGuiIO &io = ImGui::GetIO();

#if defined(USE_COMPTR)
        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = {clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w};
        d3d11DeviceContext_->OMSetRenderTargets(1, &d3d11RenderTargetView_, NULL);
        d3d11DeviceContext_->ClearRenderTargetView(d3d11RenderTargetView_.Get(), clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        d3d11SwapChain_->Present(1, 0); // Present with vsync
                                        // d3d11SwapChain_->Present(0, 0); // Present without vsync
#else
        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = {clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w};
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        g_pSwapChain->Present(1, 0); // Present with vsync
        // g_pSwapChain->Present(0, 0); // Present without vsync
#endif

        return r;
    }

    Result UiEngineBackendDx11Impl::reset()
    {
        Result r = R_SUCCESS;

        return r;
    }

    Result UiEngineBackendDx11Impl::shutdown()
    {
        Result r = R_SUCCESS;

        ImGui_ImplDX11_Shutdown();

        return r;
    }



    Result UiEngineBackendDx11Impl::setup()
    {
        Result r = R_SUCCESS;
#if defined(USE_COMPTR)
        ImGui_ImplDX11_Init(d3d11Device_.Get(), d3d11DeviceContext_.Get());
#else
        ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
        ImGuiTexInspect::ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext); //TEX_INSPECT_CHANGE

#endif

        return r;
    }
    Result UiEngineBackendDx11Impl::resize(Uint width, Uint height)
    {
        Result r = R_SUCCESS;
        d3d11CleanupRenderTarget();
#if defined(USE_COMPTR)
        d3d11SwapChain_->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
#else
        g_pSwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
#endif
        d3d11CreateRenderTarget();
        return r;
    }
    Result UiEngineBackendDx11Impl::createDevice(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;

        HWND hWnd;
        piAttributes->getPtr(UUID_IUIENGINE_BACKEND_HWND, (void *&)hWnd);

        r = d3d11CreateDevice(hWnd);


        return r;
    }
    Result UiEngineBackendDx11Impl::destoryDevice()
    {
        Result r = R_SUCCESS;
        r = d3d11DestoryDevice();
        return r;
    }

    Result UiEngineBackendDx11Impl::d3d11CreateDevice(HWND hWnd)
    {
        Result r = R_SUCCESS;

        // Setup swap chain
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        // createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_0,
        };
#if defined(USE_COMPTR)
        if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
                                          createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION,
                                          &sd, &d3d11SwapChain_,
                                          &d3d11Device_, &featureLevel, &d3d11DeviceContext_) != S_OK)
        {
            r = R_INTERNEL_FAILURE;
        }

#else
        if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
                                          createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION,
                                          &sd, &g_pSwapChain,
                                          &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        {
            r = R_INTERNEL_FAILURE;
        }
#endif

        VERIFY(r, "IDirect3D11::D3D11CreateDeviceAndSwapChain");

        d3d11CreateRenderTarget();

        return r;
    }

    Result UiEngineBackendDx11Impl::d3d11CreateRenderTarget()
    {
        Result r = R_SUCCESS;
        ID3D11Texture2D *pBackBuffer;

#if defined(USE_COMPTR)
        d3d11SwapChain_->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        d3d11Device_->CreateRenderTargetView(pBackBuffer, NULL, &d3d11RenderTargetView_);
#else
        g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
#endif
        pBackBuffer->Release();

        return r;
    }

    Result UiEngineBackendDx11Impl::d3d11CleanupRenderTarget()
    {
        Result r = R_SUCCESS;

#if defined(USE_COMPTR)
        d3d11RenderTargetView_.Reset();
#else
        if (g_mainRenderTargetView)
        {
            g_mainRenderTargetView->Release();
            g_mainRenderTargetView = NULL;
        }
#endif
        return r;
    }

    Result UiEngineBackendDx11Impl::d3d11DestoryDevice()
    {
        Result r = R_SUCCESS;

        d3d11CleanupRenderTarget();

#if defined(USE_COMPTR)

        d3d11SwapChain_.Reset();
        d3d11DeviceContext_.Reset();
        d3d11Device_.Reset();

#else
        if (g_pSwapChain)
        {
            g_pSwapChain->Release();
            g_pSwapChain = NULL;
        }
        if (g_pd3dDeviceContext)
        {
            g_pd3dDeviceContext->Release();
            g_pd3dDeviceContext = NULL;
        }
        if (g_pd3dDevice)
        {
            g_pd3dDevice->Release();
            g_pd3dDevice = NULL;
        }
#endif

        return r;
    }

    Result UiEngineBackendDx11Impl::createTexture(Char* filename, IUiTexture** ppiTexture)
    {
        Result r = R_SUCCESS;
        IUiTexture* piTexture=nullptr;

        r = UiTextureImpl::createInstance(g_pd3dDevice, &piTexture);
        if(!UAP_SUCCESS(r))
        {
            return r;
        }
      

        r = piTexture->loadTexture(filename);
        if(!UAP_SUCCESS(r))
        {
            return r;
        }

        *ppiTexture= piTexture;

        return r;
    }


} //@namespace uap

