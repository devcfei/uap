#ifndef _UAP_TEXTURE_INSPECTOR_IMPL_
#define _UAP_TEXTURE_INSPECTOR_IMPL_

namespace uap
{

    class TextureInspectorImpl : public ITextureInspector, public WindowImpl
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IWindow
        virtual Result drawPrimitives();

        // ITextureInspector
        virtual Result loadImage(const Char *name);

        static Result createInstance(IUiEngineBackend *piUiEngineBackend, ITextureInspector **ppi)
        {
            TextureInspectorImpl *p = new TextureInspectorImpl(piUiEngineBackend);
            if (p)
            {
                *ppi = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        Ulong refcount_;

    protected:
        TextureInspectorImpl(IUiEngineBackend *piUiEngineBackend)
            : refcount_(1), spUiEngineBackend_(piUiEngineBackend), WindowImpl("Image", true)
            , initCreate_(true)
        {
        }

        sptr<IUiTexture> spTexture_;
        sptr<IUiEngineBackend> spUiEngineBackend_;


        Boolean initCreate_;
    }; // @class TextureInspectorImpl

} // @namespace uap

#endif // _UAP_TEXTURE_INSPECTOR_IMPL_
