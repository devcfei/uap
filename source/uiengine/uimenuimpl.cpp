#include "common.h"

namespace uap
{
    // IMenu implementation
    Ulong MenuImpl::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }

    Ulong MenuImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }

    Result MenuImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IMENU))
        {
            IMenu *pi = static_cast<IMenu *>(this);
            addRef();

            *((IMenu **)ppv) = pi;
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

    Result MenuImpl::drawMenu(IMenu *pMenu)
    {
        Result r;
        sptr<IMenu> spMenu = pMenu;
        sptr<IFrame> spFrame;

        r = spMenu.as(&spFrame);
        if (UAP_SUCCESS(r))
        {
            r = spFrame->drawFrame();
        }
        return r;
    }

    Result MenuImpl::drawFrame()
    {
        Result r = R_SUCCESS;
        bool bMenuBegin = false;
        bool bMenuClicked = false;

        for (auto it : vecMenuItem_)
        {
            bool bHasSubItem = false;

            if(it.separator)
            {
                ImGui::Separator();
                continue;
            }

            if (it.submenu)
            {
                bMenuBegin = ImGui::BeginMenu(it.name.c_str());
                bHasSubItem = true;

            }
            else
                bMenuClicked = ImGui::MenuItem(it.name.c_str(), NULL);

            

            if (bMenuBegin )
            {
                ImGui::Indent( 16.0f );

                if (it.submenu)
                {
                    r = drawMenu(it.submenu);
                }

                ImGui::Unindent( 16.0f );

                if(bHasSubItem==true)    
                    ImGui::EndMenu();
            }




            if(bMenuClicked)
            {
                spEvent_->postEvent(it.evtId, 0, 0);
            }
        }

        
        return r;
    }

    Result MenuImpl::initialize(IAttributes *piAttributes, IEvent* piEvent)
    {

        spEvent_ =  piEvent;

        return R_SUCCESS;
    }
    
    Result MenuImpl::addItem(const Char *name, Boolean check, IMenu* submenu, EventId evtId)
    {
        Result r = R_SUCCESS;

        MenuItem item;

        item.separator = false;
        item.name = name;
        item.check = check;
        item.submenu = submenu;
        item.evtId = evtId;

        vecMenuItem_.push_back(item);

        return r;
    }

    Result MenuImpl::addSeparator()
    {
        Result r = R_SUCCESS;

        MenuItem item;

        item.separator = true;

        vecMenuItem_.push_back(item);

        return r;
    }
    
    
    
    
} //@namespace uap


