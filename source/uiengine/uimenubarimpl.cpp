#include "comp.h"


namespace uap
{

    Ulong UiMenuBarImpl::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong UiMenuBarImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
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

        return r;
    }


    // IUiMenuBar

    Result UiMenuBarImpl::initializeMenuBar(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
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

    Result UiMenuBarImpl::drawMenuBar()
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

            for(auto it: vecMenuItem_)
            {

                if(ImGui::BeginMenu(it.name.c_str()) )                              
                {
                    ImGui::EndMenu();
                }
            }


            ImGui::EndMenuBar();
        }
        return r;
    }

}

