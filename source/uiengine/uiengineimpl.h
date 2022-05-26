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
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        virtual Result createInstance(const Uuid&, void **);


        // IUiEngine
        virtual Result initialize(IApplication* piApp, IAttributes* piAttributes);
        virtual Result startup();
        virtual Result run();

        virtual Result addMenuBar(IUiMenuBar* piMenuBar);
        virtual Result getMenuBar(IUiMenuBar** ppiMenuBar);
        virtual Result addImageWindow(IUiImageWindow* piImageWindow);
        virtual Result getImageWindow(IUiImageWindow** ppiImageWindow);

        virtual Result addTextureInspector(IUiTextureInspector* piTextureInspector);
        virtual Result getTextureInspector(IUiTextureInspector** ppiTextureInspector);

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


        sptr<IUiMenuBar> spMenuBar_;

        std::vector<sptr<IUiImageWindow> > spImageWindows_;
        std::vector<sptr<IUiTextureInspector> > spTextureInspector_;


    };

}

#endif //_UAP_UIENGINEIMPL_H_
