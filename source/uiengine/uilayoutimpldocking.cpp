#include "common.h"

namespace uap
{

    // FrameWindowElementsImpl
    Ulong FrameWindowElementsImpl::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong FrameWindowElementsImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            UAP_TRACE("FrameWindowElementsImpl delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result FrameWindowElementsImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        if (uapUuidIsEqual(rUuid, IID_IFRAMEWINDOWELEMENTS))
        {
            FrameWindowElementsImpl *pi = static_cast<FrameWindowElementsImpl *>(this);
            addRef();

            *((FrameWindowElementsImpl **)ppv) = pi;
            r = R_SUCCESS;
        }
        return r;
    }

    Result FrameWindowElementsImpl::addMenuBar(IMenuBar* piMenuBar)
    {
        Result r = R_SUCCESS;

        spMenuBar_ = piMenuBar;

        return r;
    }
    Result FrameWindowElementsImpl::getMenuBar(IMenuBar** ppiMenuBar)
    {
        Result r = R_SUCCESS;

        *ppiMenuBar = spMenuBar_.get();
        // Don't forget to add reference count
        (*ppiMenuBar)->addRef();

        return r;
    }
    Result FrameWindowElementsImpl::addToolBar(IToolBar *piToolBar)
    {
        Result r = R_SUCCESS;

        spToolBar_ = piToolBar;

        return r;
    }

    Result FrameWindowElementsImpl::getToolBar(IToolBar **ppiToolBar)
    {
        Result r = R_SUCCESS;

        *ppiToolBar = spToolBar_.get();
        // Don't forget to add reference count
        (*ppiToolBar)->addRef();

        return r;
    }

    Result FrameWindowElementsImpl::addStatusBar(IStatusBar *piStatusBar)
    {
        Result r = R_SUCCESS;

        spStatusBar_ = piStatusBar;

        return r;
    }
    Result FrameWindowElementsImpl::getStatusBar(IStatusBar **ppiStatusBar)
    {
        Result r = R_SUCCESS;

        *ppiStatusBar = spStatusBar_.get();
        // Don't forget to add reference count
        (*ppiStatusBar)->addRef();

        return r;
    }


    // UiLayoutImplDocking
    Ulong UiLayoutImplDocking::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong UiLayoutImplDocking::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            UAP_TRACE("UiLayoutImplDocking delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiLayoutImplDocking::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        if (uapUuidIsEqual(rUuid, IID_ILAYOUT))
        {
            UiLayoutImplDocking *pi = static_cast<UiLayoutImplDocking *>(this);
            addRef();

            *((UiLayoutImplDocking **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_IFRAMEWINDOWELEMENTS))
        {
            FrameWindowElementsImpl *pi = static_cast<FrameWindowElementsImpl *>(this);
            addRef();

            *((FrameWindowElementsImpl **)ppv) = pi;
            r = R_SUCCESS;
        }
        return r;
    }

    Result UiLayoutImplDocking::initializeLayout(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;

        //spUiEngine_ = piUiEngine;
        // TODO: why need a release? :)
        //piUiEngine->release();
        INFO("UiLayoutImplDocking::initializeLayout\n");

        return r;
    }

    Result UiLayoutImplDocking::drawLayout()
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



#if defined(_DEBUG)
        if (showImGuiDemo_)
            ImGui::ShowDemoWindow(&showImGuiDemo_);


        if(showImPlotDemo_)
        {
            ImPlot::ShowDemoWindow(&showImPlotDemo_);
        }

#endif      


        if (showStatusBar_)
        {
            showStatusBar(&showStatusBar_);
        }

        // draw
        for(auto it: vecDraw_)
        {
            it->drawFrame();
        }

        ImGui::End();

        return r;
    }

    Result UiLayoutImplDocking::addFrame(IUniversal *piDraw)
    {
        Result r = R_SUCCESS;
        sptr<IFrame> spFrame;
        r = piDraw->queryInterface(IID_IFRAME, (void**)spFrame.getaddrof());
        if(UAP_SUCCESS(r))
        {
            vecDraw_.push_back(spFrame.get());
        }
        return r;
    }


    Result UiLayoutImplDocking::deleteFrame(IUniversal *piDraw)
    {

        Result r = R_NOT_FOUND;
        for (std::list<IFrame*>::iterator it = vecDraw_.begin();
            it != vecDraw_.end();
            ++it)
        {
            if(*it == piDraw)
            {
                vecDraw_.erase(it);
                r = R_SUCCESS;
                break;
            }
        }

        return r;
    }


    Result UiLayoutImplDocking::showMenuBar(bool* p_open)
    {
        Result r = R_SUCCESS;

        sptr<IFrame> spFrame;
        r = spMenuBar_.as(&spFrame);
        if(UAP_SUCCESS(r))
        {
            r = spFrame->drawFrame();
        }       


        return r;

    }


    Result UiLayoutImplDocking::showToolBar(bool* p_open)
    {

        Result r = R_SUCCESS;

        sptr<IFrame> spFrame;
        r = spToolBar_.as(&spFrame);
        if(UAP_SUCCESS(r))
        {
            r = spFrame->drawFrame();
        }     
        return r;
    }

    Result UiLayoutImplDocking::showStatusBar(bool* p_open)
    { 
        Result r = R_SUCCESS;

        sptr<IFrame> spFrame;
        r = spStatusBar_.as(&spFrame);
        if(UAP_SUCCESS(r))
        {
            r = spFrame->drawFrame();
        }    

        return R_SUCCESS;
    } 

} // @namespace uap