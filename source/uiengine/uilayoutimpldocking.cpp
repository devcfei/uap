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
            Size.y -= 10.0f; // TODO: need to remove this hard code

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
        ImGui::BeginChild("Toolbar", ImVec2(0, heightToolBar_), true);


        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(ImGui::GetStyle().FramePadding.x, ImGui::GetStyle().FramePadding.y + 10));
        if (ImGui::Button(ICON_FK_STAR, ImVec2(32, 32)))
        {
            UAP_TRACE("button clicked -ICON_FK_STAR \n");
        }

        ImGui::SameLine();
        ImGui::Button(ICON_FK_STAR_O, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_USER, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_TIMES, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_CHECK, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_SEARCH, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_CAMERA, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_VIDEO_CAMERA, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_PICTURE_O, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_CLOCK_O, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_MINUS_CIRCLE, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_TIMES_CIRCLE, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_CHECK_CIRCLE, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_PENCIL, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_LIST, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_DOWNLOAD, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_UPLOAD, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_USERS, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_LINK, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_BARS, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::Button(ICON_FK_TABLE, ImVec2(32, 32)); ImGui::SameLine();
        ImGui::PopStyleVar();

        ImGui::EndChild();

        return R_SUCCESS;
    }

    Result UiLayoutImplDocking::showStatusBar(bool* p_open)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Size.y - heightStatusBar_), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, heightStatusBar_), ImGuiCond_Appearing);

        ImGui::BeginChild("StatusBar", ImVec2(0, heightStatusBar_), true);
        ImGui::Text("status bar"); ImGui::SameLine();

        static float progress = 0.0f, progress_dir = 1.0f;
        progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
        if (progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
        if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }
        ImGui::ProgressBar(progress, ImVec2(100.0f, 0.0f));  ImGui::SameLine();


    #define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))    
        float progress_saturated = IM_CLAMP(progress, 0.0f, 1.0f);
        char buf[32];
        StringCchPrintfA(buf, 32, "%d/%d", (int)(progress_saturated * 1753), 1753);
        ImGui::ProgressBar(progress, ImVec2(150.f, 0.f), buf); ImGui::SameLine();

        ImGui::EndChild();

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


    

    // void UiLayoutImplDocking::ShowConsoleWindow(bool* p_open)
    // {
    //     ImGuiWindowFlags window_flags = 0;
    //     window_flags |= ImGuiWindowFlags_NoCollapse;
    //     const ImGuiViewport* viewport = ImGui::GetMainViewport();
    //     const ImVec2 base_pos = viewport->Pos;


    //     int height = 20;
    //     ImGui::SetNextWindowPos(ImVec2(base_pos.x + 300, base_pos.y + height), ImGuiCond_FirstUseEver);
    //     ImGui::SetNextWindowSize(ImVec2(viewport->Size.x-300, 300), ImGuiCond_Appearing);

    //     ImGui::Begin("Console", p_open, window_flags);

    //     ImGui::End();
    // }

    // void UiLayoutImplDocking::ShowLibraryWindow(bool* p_open)
    // {
    //     ImGui::Begin("Library", p_open);

    //     ImGui::End();
    // }

} // @namespace uap