#ifndef _UAP_UI_ENGINEIMPL_H_
#define _UAP_UI_ENGINEIMPL_H_


namespace uap
{
    class UiEngineImpl : public IUiEngine
    {
    public:

        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        virtual Result createInstance(const Uuid&, void **);


        // IUiEngine
        virtual Result initialize(IApplication* piApp, IAttributes* piAttributes, BackendType bt);
        virtual Result startup();
        virtual Result run();

        virtual Result getLayout(ILayout** ppiLayout);


        static ILogTrace* getLogTrace()
        {
            return spLogTrace_.get();
        }

        static Result createInstance(IUiEngine **ppv)
        {
            UiEngineImpl *p = new UiEngineImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiEngineImpl()
            : refcount_(1)
        {
        }
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
        inline static sptr<ILogTrace> spLogTrace_;

        BackendType beType_;
        sptr<IUiEngineBackend> spBackend_;        

        // layout
        sptr<ILayout> spLayout_;

        // backend
        ImVec4 colorClear_;


        //app location path
        std::string strAppLocation_;
    };




    
}

#endif //_UAP_UIENGINEIMPL_H_
