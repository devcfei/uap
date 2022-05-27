#include "comp.h"

namespace uap
{

    Ulong UiLayoutImplDocking::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong UiLayoutImplDocking::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result UiLayoutImplDocking::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        if (uapUuidIsEqual(rUuid, IID_IUILAYOUT))
        {
            UiLayoutImplDocking *pi = static_cast<UiLayoutImplDocking *>(this);
            addRef();

            *((UiLayoutImplDocking **)ppv) = pi;
            r = R_SUCCESS;
        }
        return r;
    }

    Result UiLayoutImplDocking::initializeLayout(IUiEngine* piUiEngine, IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;

        spUiEngine_ = piUiEngine;
        // TODO: why need a release? :)
        //piUiEngine->release();

        return r;
    }

    Result UiLayoutImplDocking::draw()
    {

        Result r = R_SUCCESS;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static bool p_open = false;
        
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("mainframe", &p_open, window_flags);

        if (showMenuBar_)
        {
            showMenuBar(&showMenuBar_);
        }

        if (showToolBar_)
        {
            showToolBar(&showToolBar_);
        }

        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MainFrame-Top");

            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);

            ImVec2 Size = viewport->WorkSize;

            if (showStatusBar_)
            {
                // Size.x = viewport->WorkSize.x;
                Size.y -= heightStatusBar_;
            }
            if (showToolBar_)
            {
                Size.y -= heightToolBar_;
            }

            Size.y -= heightMenuBar_;
            Size.y -= 8.0f; // don't forget the padding

            ImGui::DockSpace(dockspace_id, Size, dockspace_flags);
        }
        else
        {
            // TODO: error
            // ShowDockingDisabledMessage();
        }


        if (showDemoWindow_)
            ImGui::ShowDemoWindow(&showDemoWindow_);


        


        if (showStatusBar_)
        {
            showStatusBar(&showStatusBar_);
        }

        showImageWindow();
        showTextureInspector();

        ImGui::End();

        return r;
    }


    Result UiLayoutImplDocking::showMenuBar(bool* p_open)
    {
        Result r = R_SUCCESS;

        sptr<IUiMenuBar> spMenuBar;
        r = spUiEngine_->getMenuBar(spMenuBar.getaddrof());

        sptr<IDraw> spDraw;
        r = spMenuBar.as(&spDraw);
        if(UAP_SUCCESS(r))
        {
            r = spDraw->draw();
        }
        


        return r;

    }


    Result UiLayoutImplDocking::showToolBar(bool* p_open)
    {

        Result r = R_SUCCESS;

        sptr<IUiToolBar> spToolBar;
        r = spUiEngine_->getToolBar(spToolBar.getaddrof());

        sptr<IDraw> spDraw;
        r = spToolBar.as(&spDraw);
        if(UAP_SUCCESS(r))
        {
            r = spDraw->draw();
        }
        


        return r;

    }

    Result UiLayoutImplDocking::showStatusBar(bool* p_open)
    { 
        Result r = R_SUCCESS;

        sptr<IUiStatusBar> spStatusBar;
        r = spUiEngine_->getStatusBar(spStatusBar.getaddrof());

        sptr<IDraw> spDraw;
        r = spStatusBar.as(&spDraw);
        if(UAP_SUCCESS(r))
        {
            r = spDraw->draw();
        }    

        return R_SUCCESS;
    }

    Result UiLayoutImplDocking::showImageWindow()
    {
        Result r = R_SUCCESS;

        sptr<IUiImageWindow> spImageWindow;
        r = spUiEngine_->getImageWindow(spImageWindow.getaddrof());

        sptr<IDraw> spDraw;
        r = spImageWindow.as(&spDraw);
        if(UAP_SUCCESS(r))
        {
            r = spDraw->draw();
        }    


        return r;

    }


    Result UiLayoutImplDocking::showTextureInspector()
    {
        Result r = R_SUCCESS;

        sptr<IUiTextureInspector> spTextureInspector;
        r = spUiEngine_->getTextureInspector(spTextureInspector.getaddrof());

        sptr<IDraw> spDraw;
        r = spTextureInspector.as(&spDraw);
        if(UAP_SUCCESS(r))
        {
            r = spDraw->draw();
        }    


        return r;

    }

} // @namespace uap