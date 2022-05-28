#ifndef _UAP_UILAYOUTIMPL_DOCKING_
#define _UAP_UILAYOUTIMPL_DOCKING_

namespace uap
{



    class UiLayoutImplDocking: public IUiLayout
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // IUiLayout
        virtual Result initializeLayout(IUiEngine* piUiEngine, IAttributes* piAttributes);
        virtual Result draw();

        static Result createInstance(void **ppv)
        {
            UiLayoutImplDocking *p = new UiLayoutImplDocking();
            if (p)
            {
                *(IUiLayout **)ppv = p;
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
            , showDemoWindow_(true)        
            , heightMenuBar_(FONT_SIZE+6.0f)
            , heightToolBar_(TOOLBAR_HEIGHT)
            , heightStatusBar_(FONT_SIZE+6.0f)
        {
        }

        Ulong refcount_;

        sptr<IUiEngine> spUiEngine_;


        //
        Result showMenuBar(bool* p_open);
        Result showToolBar(bool* p_open);
        Result showStatusBar(bool* p_open);
        
        bool showDemoWindow_;
        bool showMenuBar_;
        bool showToolBar_;
        bool showStatusBar_;


        float heightMenuBar_;
        float heightToolBar_;
        float heightStatusBar_;

        // ImageWindow
        Result showImageWindow();
        // Texture Inspector
        Result showTextureInspector();


        // Log Window
        Result showLogWindow();



    }; // @class UiLayoutImplDocking




} // @namespace uap

#endif // _UAP_UILAYOUTIMPL_DOCKING_
