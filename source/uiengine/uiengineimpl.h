#ifndef _UAP_UIENGINEIMPL_H_
#define _UAP_UIENGINEIMPL_H_


namespace uap
{

    class UiEngineImpl : public IUiEngine
    {
    public:
        UiEngineImpl()
            : refcount_(1)
        {
        }
        virtual const Uuid& uuidof();
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const uap::Uuid &,void **);

        // IUiEngine
        virtual Result initialize(IApplication* piApp, IAttributes* piAttributes);
        virtual Result run();

    private:
        const Uuid uuid_= IID_IMAGEENGINE;
        Ulong refcount_;

        Result initializeWindow();
        Result initializeBackEnd();
        Result reset();

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


        // log attributes
        LogAttributes logAttributes_;
        sptr<ILogTrace> spLogTrace_;

    };

};

#endif //_UAP_UIENGINEIMPL_H_
