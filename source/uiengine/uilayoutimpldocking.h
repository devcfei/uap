#ifndef _UAP_UILAYOUTIMPL_DOCKING_
#define _UAP_UILAYOUTIMPL_DOCKING_

namespace uap
{

    class FrameWindowElementsImpl: public IFrameWindowElements
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // IFrameWindowElements
        virtual Result addMenuBar(IMenuBar *piMenuBar) ;
        virtual Result getMenuBar(IMenuBar **ppiMenuBar) ;
        virtual Result addToolBar(IToolBar *piToolBar) ;
        virtual Result getToolBar(IToolBar **ppiToolBar) ;
        virtual Result addStatusBar(IStatusBar *piStatusBar) ;
        virtual Result getStatusBar(IStatusBar **ppiStatusBar);

    
        FrameWindowElementsImpl()
            : refcount_(1)
        {
        }

        Ulong refcount_;

    protected:
        // menubar, toolbar, status bar
        sptr<IMenuBar> spMenuBar_;
        sptr<IToolBar> spToolBar_;
        sptr<IStatusBar> spStatusBar_;

    };



    class UiLayoutImplDocking: public ILayout, public FrameWindowElementsImpl
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // ILayout
        virtual Result initializeLayout(IAttributes* piAttributes);
        virtual Result drawLayout();
#ifdef _DEBUG
        virtual void openImGuiDemo(Boolean open)
        {
            showImGuiDemo_ = open;
        }
        virtual void openImPlotDemo(Boolean open)
        {
            showImPlotDemo_ = open;
        }
#endif


        virtual Result addFrame(IUniversal *piDraw);
        virtual Result deleteFrame(IUniversal *piDraw);

        static Result createInstance(void **ppv)
        {
            UiLayoutImplDocking *p = new UiLayoutImplDocking();
            if (p)
            {
                *(ILayout **)ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiLayoutImplDocking()
            : refcount_(1)
            , showMenuBar_(true)
            , showToolBar_(true)
            , showStatusBar_(true)       
            , showImGuiDemo_(false)        
            , showImPlotDemo_(false)        
            , heightMenuBar_(FONT_SIZE+6.0f)
            , heightToolBar_(TOOLBAR_HEIGHT)
            , heightStatusBar_(FONT_SIZE+6.0f)
        {
        }

        Ulong refcount_;

        //sptr<IUiEngine> spUiEngine_;

        // generic draw
        std::list<IFrame*> vecDraw_;


        //
        Result showMenuBar(bool* p_open);
        Result showToolBar(bool* p_open);
        Result showStatusBar(bool* p_open);
        
        bool showImGuiDemo_;
        bool showImPlotDemo_;
        bool showMenuBar_;
        bool showToolBar_;
        bool showStatusBar_;


        float heightMenuBar_;
        float heightToolBar_;
        float heightStatusBar_;



    }; // @class UiLayoutImplDocking




} // @namespace uap

#endif // _UAP_UILAYOUTIMPL_DOCKING_
