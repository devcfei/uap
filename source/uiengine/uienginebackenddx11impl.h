#ifndef _UIENGINEBACKENDDX11IMPL_
#define _UIENGINEBACKENDDX11IMPL_

// TODO: why ComPtr doesn't work?
//#define USE_COMPTR



namespace uap
{

    class UiEngineBackendDx11Impl : public IUiEngineBackend
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &, void **);

        // UiEngineBackend
        virtual Result initializeBackend(IUiEngine *piUiEngine, IAttributes *piAttributes);
        
        virtual Result createDevice(IAttributes *piAttributes);
        virtual Result destoryDevice();
        virtual Result newFrame();
        virtual Result setup();
        virtual Result render();
        virtual Result reset();
        virtual Result shutdown();
        virtual Result resize(Uint width, Uint height);

        virtual Result createTexture(Char* filename, void** ppv) ;
        

        static Result createInstance(void **ppv)
        {
            UiEngineBackendDx11Impl *p = new UiEngineBackendDx11Impl();
            if (p)
            {
                *(UiEngineBackendDx11Impl **)ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiEngineBackendDx11Impl()
            : refcount_(1)
        {
        }
        Ulong refcount_;

        // d3d11

#if defined(USE_COMPTR)
        ComPtr<ID3D11Device> d3d11Device_;
        ComPtr<ID3D11DeviceContext> d3d11DeviceContext_;
        ComPtr<IDXGISwapChain> d3d11SwapChain_;
        ComPtr<ID3D11RenderTargetView> d3d11RenderTargetView_;

#else
        ID3D11Device *g_pd3dDevice;
        ID3D11DeviceContext *g_pd3dDeviceContext;
        IDXGISwapChain *g_pSwapChain;
        ID3D11RenderTargetView *g_mainRenderTargetView;
#endif

        Result d3d11CreateDevice(HWND hWnd);
        Result d3d11CreateRenderTarget();
        Result d3d11CleanupRenderTarget();
        Result d3d11DestoryDevice();


        HWND hWnd_;

    }; // @class UiEngineBackendDx11Impl

} //@namespace uap

#endif // _UIENGINEBACKENDDX11IMPL_
