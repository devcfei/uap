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

    /// insert menu
    /// \name the display name
    ///
    Result UiMenuBarImpl::insertMenuItem(const Char *name, Uint id, Uint flags)
    {
        Result r = R_SUCCESS;

        UiMenuItem item;
        item.name = name; // Char* -> std::string copy
        item.id = id;
        item.flags.ui = flags;

        vecMenuItem_.push_back(item);

        return r;
    }

   
    // IDraw
    Result UiMenuBarImpl::draw()
    {
        Result r = R_SUCCESS;

        if (ImGui::BeginMenuBar())
        {
            // if (ImGui::BeginMenu("File"))
            // {
            //     ImGui::MenuItem("Exit", NULL);

            //     ImGui::EndMenu();
            // }
            // if (ImGui::BeginMenu("View"))
            // {
            //     ImGui::MenuItem("Toolbar", NULL);
            //     ImGui::MenuItem("StatusBar", NULL);
            //     ImGui::EndMenu();
            // }

            // // HelpMarker(
            // //     "When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
            // //     "- Drag from window title bar or their tab to dock/undock." "\n"
            // //     "- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
            // //     "- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)" "\n"
            // //     "- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)" "\n"
            // //     "This demo app has nothing to do with enabling docking!" "\n\n"
            // //     "This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window." "\n\n"
            // //     "Read comments in ShowExampleAppDockSpace() for more details.");

            // if (ImGui::BeginMenu("Help"))
            // {
            //     ImGui::MenuItem("About", NULL, false);
            //     ImGui::EndMenu();
            // }

            bool bSuc;

            for (auto it : vecMenuItem_)
            {
                if (it.flags.s.start)
                {
                    bSuc = ImGui::BeginMenu(it.name.c_str());
                    continue;
                }

                if (bSuc)
                {
                    ImGui::MenuItem(it.name.c_str(), NULL);

                    if (it.flags.s.end)
                    {
                        ImGui::EndMenu();
                    }
                }
            }

            ImGui::EndMenuBar();
        }
        return r;
    }



}

