#ifndef _UAP_UIENGINEIMPL_H_
#define _UAP_UIENGINEIMPL_H_


namespace uap
{
    class UiMenuBarImpl: public IUiMenuBar
    {
    public:
        Ulong addRef()
        {
            return InterlockedIncrement(&refcount_);
        }
        Ulong release()
        {
            Ulong ref = InterlockedDecrement(&refcount_);
            if (!ref)
            {
                delete this;
            }
            return ref;
        }
        Result queryInterface(const Uuid &rUuid, void **ppv)
        {
            Result r = R_NO_SUCH_INTERFACE;

            if (uapUuidIsEqual(rUuid, IID_IUIMENUBAR))
            {
                IUiMenuBar *pi = static_cast<IUiMenuBar *>(this);
                addRef();

                *((IUiMenuBar **)ppv) = pi;
                r = R_SUCCESS;
            }

            return r;
        }
        // IUiMenuBar
        virtual Result initializeMenuBar(IAttributes* piAttributes)
        {
            Result r = R_SUCCESS;
            return r;
        }
    private:
        Ulong refcount_;
    };

    class UiEngineImpl : public IUiEngine
        , public UiMenuBarImpl
    {
    public:
        UiEngineImpl()
            : refcount_(1)
        {
        }
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // IUiEngine
        virtual Result initialize(IApplication* piApp, IAttributes* piAttributes);
        virtual Result startup();
        virtual Result run();


    private:
        Ulong refcount_;

        Result initializeWindow();
        Result initializeBackEnd();
        Result reset();
        Result createLayout();
        Result drawLayout();


        // Win32
        WNDCLASSEX wc_;
        HWND hWnd_;
        static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        // d3d9
        ComPtr<IDirect3D9> d3d9_;
        ComPtr<IDirect3DDevice9> d3d9Device_;        
        D3DPRESENT_PARAMETERS d3dpp_;

        Result d3d9CreateDevice(HWND hWnd);
        Result d3d9DestoryDevice();


        // set when initialize
        sptr<IApplication> spApp_ ;
        sptr<IAttributes> spAppAttributes_ ;
        LogAttributes logAttributes_;
        sptr<ILogTrace> spLogTrace_;

        // layout attributes
        sptr<IUiLayout> spLayout_;
        sptr<IAttributes> spMenuBarAttributes_ ;

        ImVec4 colorClear_;


    };

};

#endif //_UAP_UIENGINEIMPL_H_
