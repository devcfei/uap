#include "common.h"


namespace uap
{

    Ulong UiMenuBarImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        //UAP_TRACE("UiMenuBarImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong UiMenuBarImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        //UAP_TRACE("UiMenuBarImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            UAP_TRACE("UiMenuBarImpl delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiMenuBarImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IUIMENUBAR))
        {
            IUiMenuBar *pi = static_cast<IUiMenuBar *>(this);
            addRef();

            *((IUiMenuBar **)ppv) = pi;
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


    // IUiMenuBar

    Result UiMenuBarImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        INFO("UiMenuBarImpl::initialize\n");
        return r;
    }


    Result UiMenuBarImpl::setMenu(IMenu *piMenu)
    {
        Result r = R_SUCCESS;
        spMenu_ = piMenu;
        return r;
    }

    // IDraw
    Result UiMenuBarImpl::draw()
    {
        Result r = R_SUCCESS;

        if (spMenu_.get())
        {
            if (ImGui::BeginMenuBar())
            {
                sptr<IDraw> spDraw;
                r = spMenu_.as(&spDraw);
                if (UAP_SUCCESS(r))
                {
                    r = spDraw->draw();
                }
                ImGui::EndMenuBar();
            }
        }

        return r;
    }
}

