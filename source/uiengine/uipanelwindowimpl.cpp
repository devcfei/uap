#include "common.h"


namespace uap
{

    Ulong UiPanelWindowImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        //UAP_TRACE("UiPanelWindowImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong UiPanelWindowImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        //UAP_TRACE("UiPanelWindowImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            //UAP_TRACE("delete UiPanelWindowImpl!!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiPanelWindowImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IUIPANELWINDOW))
        {
            IPanelWindow *pi = static_cast<IPanelWindow *>(this);
            addRef();

            *((IPanelWindow **)ppv) = pi;
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

   
    // IDraw
    Result UiPanelWindowImpl::draw()
    {
        Result r = R_SUCCESS;
        if (open_)
        {
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            const ImVec2 base_pos = viewport->Pos;

            ImGui::SetNextWindowPos(ImVec2(base_pos.x + pos_.x, base_pos.y + pos_.y), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(size_, ImGuiCond_FirstUseEver);

            ImGui::Begin(title_.c_str(), &open_);

            drawPrimitives();

            ImGui::End();
        }

        return r;
    }

    // IPanelWindow
    
    Result UiPanelWindowImpl::initialize(IAttributes* pAttributes)
    {
        Result r;
        Char title[256];
        Ulong len=0;
        r = pAttributes->getString(PANELWINDOW_ATTRIBUTE_TITLE,title,256,&len);
        if(!UAP_SUCCESS(r))
        {
            return r;
        }

        if(len>0)
            title_ = title;


        return r;
    }

    Boolean UiPanelWindowImpl::isOpen() const
    {
        return open_;
    }

    Boolean UiPanelWindowImpl::setOpen(Boolean open)
    {
        return open_=open;  // TODO: need atomic operation?
    }


    Result UiPanelWindowImpl::drawPrimitives()
    {
        Result r = R_SUCCESS;


        return r;
    }


}

