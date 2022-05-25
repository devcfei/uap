#ifndef _UAP_UIENGINEIMPL_H_
#define _UAP_UIENGINEIMPL_H_


namespace uap
{
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
        Result createLayout();
        Result drawLayout();
        Result resize(Uint width, Uint height);


        // Win32
        WNDCLASSEX wc_;
        HWND hWnd_;
        static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);




        // set when initialize
        sptr<IApplication> spApp_ ;
        sptr<IAttributes> spAppAttributes_ ;
        LogAttributes logAttributes_;
        sptr<ILogTrace> spLogTrace_;

        BackendType beType_;
        sptr<IUiEngineBackend> spBackend_;
        

        // layout attributes
        sptr<IUiLayout> spLayout_;

        // backend

        ImVec4 colorClear_;


    };

}

#endif //_UAP_UIENGINEIMPL_H_
