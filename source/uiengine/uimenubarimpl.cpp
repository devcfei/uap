#include "common.h"


namespace uap
{

    Ulong MenuBarImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        //UAP_TRACE("MenuBarImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong MenuBarImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        //UAP_TRACE("MenuBarImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            UAP_TRACE("MenuBarImpl delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result MenuBarImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IMENUBAR))
        {
            IMenuBar *pi = static_cast<IMenuBar *>(this);
            addRef();

            *((IMenuBar **)ppv) = pi;
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


    // IMenuBar

    Result MenuBarImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        INFO("MenuBarImpl::initialize\n");
        return r;
    }


    Result MenuBarImpl::setMenu(IMenu *piMenu)
    {
        Result r = R_SUCCESS;
        spMenu_ = piMenu;
        return r;
    }

    // IDraw
    Result MenuBarImpl::draw()
    {
        Result r = R_SUCCESS;

        if (spMenu_.get())
        {
            if (ImGui::BeginMenuBar())
            {
                // TODO: for customized menubar
                //ImGui::Text("\xef\x80\x86"); // TODO: STAR_O as the logo
                sptr<IDraw> spDraw;
                r = spMenu_.as(&spDraw);
                if (UAP_SUCCESS(r))
                {
                    r = spDraw->draw();
                }

                // TODO: for customized menubar
                // int width = 30;
                // ImGui::SameLine(ImGui::GetWindowWidth()-width*4);
                // ImGui::Button("\xef\x8b\x91");  // ICON_FK_WINDOW_MINIMIZE
                // ImGui::SameLine(ImGui::GetWindowWidth()-width*3);
                // ImGui::Button("\xef\x8b\x90");  // ICON_FK_WINDOW_MAXIMIZE
                // ImGui::SameLine(ImGui::GetWindowWidth()-width*2);
                // ImGui::Button("\xef\x8b\x92");  // ICON_FK_WINDOW_RESTORE
                // ImGui::SameLine(ImGui::GetWindowWidth()-width*1);
                // ImGui::Button("\xef\x80\x8d");  // ICON_FK_TIMES

            
                ImGui::EndMenuBar();
            }
        }

        return r;
    }
}

