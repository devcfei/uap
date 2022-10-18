#ifndef _UAP_UIENGINEIMPL_H_
#define _UAP_UIENGINEIMPL_H_


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
        virtual Result initialize(IApplication* piApp, IAttributes* piAttributes);
        virtual Result startup();
        virtual Result run();

        virtual Result addMenuBar(IUiMenuBar *piMenuBar);
        virtual Result getMenuBar(IUiMenuBar **ppiMenuBar);
        virtual Result addToolBar(IUiToolBar *piToolBar);
        virtual Result getToolBar(IUiToolBar **ppiToolBar);
        virtual Result addStatusBar(IUiStatusBar *piStatusBar);
        virtual Result getStatusBar(IUiStatusBar **ppiStatusBar);

        virtual Result addLogWindow(IUiLogWindow *piLogWindow);
        virtual Result getLogWindow(IUiLogWindow **ppiLogWindow);

        virtual Result addImageWindow(IUiImageWindow *piImageWindow);
        virtual Result getImageWindow(IUiImageWindow **ppiImageWindow);
        virtual Result addTextureInspector(IUiTextureInspector* piTextureInspector);
        virtual Result getTextureInspector(IUiTextureInspector** ppiTextureInspector);


        virtual Result addFileBroserWindow(IUiFileBrowser *piFileBrowserWindow);
        virtual Result getFileBroserWindow(IUiFileBrowser **ppiFileBrowserWindow);

        virtual Result addPanelWindow(IPanelWindow *piPanelWindow);
        virtual Result getPanelWindow(IPanelWindow **ppiPanelWindow);

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
        

        // layout attributes
        sptr<IUiLayout> spLayout_;

        // backend

        ImVec4 colorClear_;


        sptr<IUiMenuBar> spMenuBar_;
        sptr<IUiToolBar> spToolBar_;
        sptr<IUiStatusBar> spStatusBar_;
        sptr<IUiLogWindow> spLogWindow_;
        sptr<IUiFileBrowser> spFileBrowserWindow_;

        std::vector<sptr<IUiImageWindow> > spImageWindows_;
        std::vector<sptr<IUiTextureInspector> > spTextureInspector_;


        
        std::vector<sptr<IPanelWindow> > spPanelWindow_;


    };

}

#endif //_UAP_UIENGINEIMPL_H_
