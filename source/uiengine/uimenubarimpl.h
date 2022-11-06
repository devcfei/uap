#ifndef _UAP_UI_MENUBAR_IMPL_H_
#define _UAP_UI_MENUBAR_IMPL_H_

namespace uap
{

    class MenuBarImpl : public IMenuBar
                , public IFrame
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IMenuBar
        virtual Result initialize(Boolean asTitleBar, const Char* logoPath, IAttributes *piAttributes);
        virtual Result setMenu(IMenu* piMenu) ;

        // IFrame
        virtual Result drawFrame();

        static Result createInstance(IUiEngineBackend * piUiEngineBackend,IMenuBar **ppv)
        {
            MenuBarImpl *p = new MenuBarImpl(piUiEngineBackend);
            if (p)
            {
                *(IMenuBar **)ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        MenuBarImpl(IUiEngineBackend * piUiEngineBackend)
            :refcount_(1)
            ,spUiEngineBackend_(piUiEngineBackend)
            ,asTitleBar_(false)
        {

        }
        Ulong refcount_;

        sptr<IMenu> spMenu_;

        sptr<IUiEngineBackend> spUiEngineBackend_;

        sptr<ITexture> spTextureLogo_;
        sptr<ITexture> spTextureMin_;
        sptr<ITexture> spTextureMax_;
        sptr<ITexture> spTextureClose_;
        Boolean asTitleBar_;
    }; // @class MenuBarImpl

} // @namespace uap

#endif // _UAP_UI_MENUBAR_IMPL_H_
