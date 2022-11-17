#ifndef _UAP_UI_IMAGEWINDOW_IMPL_H_
#define _UAP_UI_IMAGEWINDOW_IMPL_H_

namespace uap
{

    class ImageWindowImpl : public IImageWindow
                , public WindowImpl
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);


        // IWindow
        virtual Result drawPrimitives();

        // IImageWindow
        virtual Result loadImage(const Char *name);
        virtual Result setTexture(ITexture* pTexture);


        static Result createInstance(IUiEngineBackend * piUiEngineBackend, IImageWindow ** ppiUiImageWindow)
        {
            ImageWindowImpl *p = new ImageWindowImpl(piUiEngineBackend);
            if (p)
            {
                *ppiUiImageWindow = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
    
        Ulong refcount_;

    protected:

        ImageWindowImpl(IUiEngineBackend * piUiEngineBackend)
            :refcount_(1)
            ,spUiEngineBackend_(piUiEngineBackend)
            , WindowImpl("Image", true)
        {

        }



        sptr<ITexture> spTexture_;
        sptr<IUiEngineBackend> spUiEngineBackend_;



    }; // @class ImageWindowImpl

} // @namespace uap

#endif // _UAP_UI_IMAGEWINDOW_IMPL_H_
