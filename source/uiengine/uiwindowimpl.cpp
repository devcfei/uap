#include "common.h"


namespace uap
{

    Ulong WindowImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        //UAP_TRACE("WindowImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong WindowImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        //UAP_TRACE("WindowImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            //UAP_TRACE("delete WindowImpl!!!!!\n");
            delete this;
        }
        return ref;
    }
    Result WindowImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IWINDOW))
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
    Result WindowImpl::initialize(const Char* title, IAttributes* pAttributes, IEvent* piEvent)
    {
        Result r = R_SUCCESS;

        if(title)
            title_ = title;
        if(pAttributes)
        {
            Size_t len=0;
            Char title[256];
            r = pAttributes->getString(WINDOW_ATTRIBUTE_TITLE,title,256,&len);
            if(!UAP_SUCCESS(r))
            {
                r = R_SUCCESS; // ignore if window no title
            }

            if(len>0)
                title_ = title;


            r = pAttributes->getUint(WINDOW_CLOSE_EVENTID,evtIdWindowClose_);
            if(!UAP_SUCCESS(r))
            {
                r = R_SUCCESS; // ignore error for WINDOW_CLOSE_EVENTID not set
            }
        }

        spEvent_ = piEvent;

        return r;
    }

    
    // IFrame
    Result WindowImpl::drawFrame()
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

            if(open_ == false)
            {
                // if last draw open, and event id for close is set
                if(evtIdWindowClose_!=0)
                {
                    spEvent_->postEvent((EventId)evtIdWindowClose_, (EventArg)this, nullptr);
                }
            }

        }


        return r;
    }



    Result WindowImpl::drawPrimitives()
    {
        Result r = R_SUCCESS;

        if(spFrame_.get())
        {
            spFrame_->drawFrame();
        }

        return r;
    }


}

