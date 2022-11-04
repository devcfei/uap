#include "common.h"


namespace uap
{

    Ulong UiEngineBackendDx9Impl::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong UiEngineBackendDx9Impl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            UAP_TRACE("UiEngineBackendDx9Impl delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiEngineBackendDx9Impl::queryInterface(const Uuid &rUuid, void **ppv)
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



    Result UiEngineBackendDx9Impl::initializeBackend(IUiEngine *piUiEngine, IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        return r;
    }

    Result UiEngineBackendDx9Impl::newFrame()
    {
        Result r = R_SUCCESS;
        ImGui_ImplDX9_NewFrame();
        return r;
    }

    Result UiEngineBackendDx9Impl::setup()
    {
        Result r = R_SUCCESS;
        ImGui_ImplDX9_Init(d3d9Device_.Get());
        return r;
    }


    Result UiEngineBackendDx9Impl::render()
    {
        Result r = R_SUCCESS;

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        ImVec4 colorClear_ = clear_color;

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

        ImGuiIO &io = ImGui::GetIO();

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

        return r;
    }

    Result UiEngineBackendDx9Impl::reset()
    {
        Result r = R_SUCCESS;
        ImGui_ImplDX9_InvalidateDeviceObjects();
        HRESULT hr = d3d9Device_->Reset(&d3dpp_);
        if (hr == D3DERR_INVALIDCALL)
            IM_ASSERT(0);
        ImGui_ImplDX9_CreateDeviceObjects();
        return r;
    }

    Result UiEngineBackendDx9Impl::shutdown()
    {
        Result r = R_SUCCESS;
        ImGui_ImplDX9_Shutdown();
        return r;
    }

    Result UiEngineBackendDx9Impl::resize(Uint width, Uint height)
    {
        Result r = R_SUCCESS;
        d3dpp_.BackBufferWidth = width;
        d3dpp_.BackBufferHeight = height;
        reset();
        return r;
    }
    Result UiEngineBackendDx9Impl::createDevice(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;

        HWND hWnd;
        piAttributes->getPtr(UUID_IUIENGINE_BACKEND_HWND, (void*&)hWnd);

        r = d3d9CreateDevice(hWnd);


        return r;
    }
    Result UiEngineBackendDx9Impl::destoryDevice()
    {
        Result r = R_SUCCESS;
        r = d3d9DestoryDevice();
        return r;
    }


    Result UiEngineBackendDx9Impl::d3d9CreateDevice(HWND hWnd)
    {
        Result r = R_SUCCESS;

        if ((d3d9_ = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        {
            r = R_INTERNEL_FAILURE;
        }


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

        return r;
    }

    Result UiEngineBackendDx9Impl::d3d9DestoryDevice()
    {
        Result r = R_SUCCESS;

        d3d9Device_.Reset();
        d3d9_.Reset();
    
        return r;
    }

    Result UiEngineBackendDx9Impl::createTexture(const Char* filename, ITexture** ppiTexture)
    {
        Result r = R_NOT_IMPL;
        // ITexture* piTexture;

        // r = TextureImpl::createInstance((void**)piTexture);
        
      

        // r = piTexture->loadTexture(filename);


        // *(void**)ppv = piTexture;

        return r;
    }

} //@namespace uap

