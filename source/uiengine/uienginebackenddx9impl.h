#ifndef _UIENGINEBACKENDDX9IMPL_
#define _UIENGINEBACKENDDX9IMPL_

namespace uap
{

    class UiEngineBackendDx9Impl : public IUiEngineBackend
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

        static Result createInstance(void **ppv)
        {
            UiEngineBackendDx9Impl *p = new UiEngineBackendDx9Impl();
            if (p)
            {
                *(UiEngineBackendDx9Impl **)ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiEngineBackendDx9Impl()
            : refcount_(1)
        {
        }
        Ulong refcount_;

        // d3d9
        ComPtr<IDirect3D9> d3d9_;
        ComPtr<IDirect3DDevice9> d3d9Device_;
        D3DPRESENT_PARAMETERS d3dpp_;

        Result d3d9CreateDevice(HWND hWnd);
        Result d3d9DestoryDevice();

        HWND hWnd_;

    }; // @class IUiEngineBackend

} //@namespace uap

#endif // _UIENGINEBACKENDDX9IMPL_
