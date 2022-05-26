#ifndef _UAP_UIIMAGE_TEXTURE_INSPECTOR_
#define _UAP_UIIMAGE_TEXTURE_INSPECTOR_

namespace uap
{

    class UiTextureInspectorImpl : public IUiTextureInspector
                , public IDraw
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IUiTextureInspector
        virtual Result initialize(IAttributes *piAttributes);
        virtual Result loadImage(Char *name);

        // IDraw
        virtual Result draw();

        static Result createInstance(IUiEngineBackend * piUiEngineBackend, IUiTextureInspector ** ppi)
        {
            UiTextureInspectorImpl *p = new UiTextureInspectorImpl(piUiEngineBackend);
            if (p)
            {
                *ppi = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiTextureInspectorImpl(IUiEngineBackend * piUiEngineBackend)
            :refcount_(1)
            ,spUiEngineBackend_(piUiEngineBackend)
        {

        }
        Ulong refcount_;



        sptr<IUiTexture> spTexture_;
        sptr<IUiEngineBackend> spUiEngineBackend_;



    }; // @class UiTextureInspectorImpl

} // @namespace uap

#endif // _UAP_UIIMAGE_TEXTURE_INSPECTOR_
