#include "comp.h"


namespace uap
{

    Ulong UiImageWindowImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        //UAP_TRACE("UiImageWindowImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong UiImageWindowImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        //UAP_TRACE("UiImageWindowImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            //UAP_TRACE("delete UiImageWindowImpl!!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiImageWindowImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IUIIMAGEWINDOW))
        {
            IUiImageWindow *pi = static_cast<IUiImageWindow *>(this);
            addRef();

            *((IUiImageWindow **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_IDRAW))
        {
            IDraw *pi = static_cast<IDraw *>(this);
            addRef();

            *((IDraw **)ppv) = pi;
            r = R_SUCCESS;
        }
        return r;
    }


    // IUiImageWindow

    Result UiImageWindowImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        INFO("UiImageWindowImpl::initializeBackend\n");
        return r;
    }

    Result UiImageWindowImpl::loadImage(Char *name)
    {
        Result r = R_SUCCESS;

        r = spUiEngineBackend_->createTexture(name,spTexture_.getaddrof());
        return r;
    }

    // IDraw
    Result UiImageWindowImpl::draw()
    {
        Result r = R_SUCCESS;
        ImGui::Begin("DirectX11 Texture Test");
        ImGui::Text("pointer = %p", spTexture_->texture());
        ImGui::Text("size = %d x %d", spTexture_->width(), spTexture_->height());
        ImGui::Image((void*)spTexture_->texture(), ImVec2((float)spTexture_->width(), (float)spTexture_->height()));
        ImGui::End();


        return r;
    }
}