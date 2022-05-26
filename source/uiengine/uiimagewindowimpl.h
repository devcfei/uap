#ifndef _UAP_UIIMAGEWINDOW_H_
#define _UAP_UIIMAGEWINDOW_H_

namespace uap
{

    class UiImageWindowImpl : public IUiImageWindow
                , public IDraw
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IUiImageWindow
        virtual Result initialize(IAttributes *piAttributes);
        virtual Result loadImage(Char *name);

        // IDraw
        virtual Result draw();

        static Result createInstance(IUiEngineBackend * piUiEngineBackend, IUiImageWindow ** ppiUiImageWindow)
        {
            UiImageWindowImpl *p = new UiImageWindowImpl(piUiEngineBackend);
            if (p)
            {
                *ppiUiImageWindow = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiImageWindowImpl(IUiEngineBackend * piUiEngineBackend)
            :refcount_(1)
            ,spUiEngineBackend_(piUiEngineBackend)
        {

        }
        Ulong refcount_;



        sptr<IUiTexture> spTexture_;
        sptr<IUiEngineBackend> spUiEngineBackend_;



    }; // @class UiImageWindowImpl

} // @namespace uap

#endif // _UAP_UIIMAGEWINDOW_H_
