#include "common.h"


namespace uap
{

    Ulong ImageWindowImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        //UAP_TRACE("ImageWindowImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong ImageWindowImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        //UAP_TRACE("ImageWindowImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            UAP_TRACE("ImageWindowImpl delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result ImageWindowImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IIMAGEWINDOW))
        {
            IImageWindow *pi = static_cast<IImageWindow *>(this);
            addRef();

            *((IImageWindow **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_IWINDOW))
        {
            IWindow *pi = static_cast<IWindow *>(this);
            addRef();

            *((IWindow **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_IFRAME))
        {
            IFrame *pi = static_cast<IFrame *>(this);
            addRef();

            *((IFrame **)ppv) = pi;
            r = R_SUCCESS;
        }
        return r;
    }

    // IWindow
    Result ImageWindowImpl::drawPrimitives()
    {
        Result r = R_SUCCESS;

        ImGui::Text("pointer = %p", spTexture_->texture());
        ImGui::Text("size = %d x %d", spTexture_->width(), spTexture_->height());
        ImGui::Image((void*)spTexture_->texture(), ImVec2((float)spTexture_->width(), (float)spTexture_->height()));


        return r;
    }



    // IImageWindow
    Result ImageWindowImpl::loadImage(const Char *name)
    {
        Result r = R_SUCCESS;

        r = spUiEngineBackend_->createTexture(name,spTexture_.getaddrof());
        return r;
    }

    
    Result ImageWindowImpl::setTexture(ITexture* pTexture)
    {
        Result r = R_SUCCESS;
        spTexture_ = pTexture;
        return r;
    }

}