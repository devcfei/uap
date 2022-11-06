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
        else if (uapUuidIsEqual(rUuid, IID_IFRAME))
        {
            IFrame *pi = static_cast<IFrame *>(this);
            addRef();

            *((IFrame **)ppv) = pi;
            r = R_SUCCESS;
        }
        return r;
    }


    // IMenuBar

    Result MenuBarImpl::initialize(Boolean asTitleBar, const Char* logoPath, IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        INFO("MenuBarImpl::initialize\n");
        asTitleBar_ = asTitleBar;

        if(logoPath!=nullptr)
            spUiEngineBackend_->createTexture(logoPath, spTextureLogo_.getaddrof());


        // load system buttons texture
        // TODO: currently hardcode to use the png icon located in app folder
        //    - need a better design

        CHAR path[MAX_PATH];
        ::GetModuleFileNameA(NULL, path, MAX_PATH);
        ::PathRemoveFileSpecA(path);
        CHAR temp[MAX_PATH];

        StringCchCopyA(temp, MAX_PATH, path);
        StringCchCatA(temp, MAX_PATH, "\\min.png");
        spUiEngineBackend_->createTexture(temp, spTextureMin_.getaddrof());

        StringCchCopyA(temp, MAX_PATH, path);
        StringCchCatA(temp, MAX_PATH, "\\max.png");
        spUiEngineBackend_->createTexture(temp, spTextureMax_.getaddrof());

        StringCchCopyA(temp, MAX_PATH, path);
        StringCchCatA(temp, MAX_PATH, "\\close.png");
        spUiEngineBackend_->createTexture(temp, spTextureClose_.getaddrof());

        return r;
    }


    Result MenuBarImpl::setMenu(IMenu *piMenu)
    {
        Result r = R_SUCCESS;
        spMenu_ = piMenu;
        return r;
    }

    // IFrame
    Result MenuBarImpl::drawFrame()
    {
        Result r = R_SUCCESS;






        if (spMenu_.get())
        {

            if (ImGui::BeginMenuBar())
            {
                // draw the logo
                if (spTextureLogo_.get())
                {

                    float h = ImGui::GetFrameHeight();
                    ImVec2 size(h,h);
                    ImGui::Image((void *)spTextureLogo_->texture(), size);
                    ImGui::SameLine();
                    ImGui::Indent(h+12);

                }

                // draw the menu frame
                sptr<IFrame> spFrame;
                r = spMenu_.as(&spFrame);
                if (UAP_SUCCESS(r))
                {
                    r = spFrame->drawFrame();
                }


                // draw the system system button
                if(asTitleBar_)
                {
                    // if the menubar work as a title bar, need to add system buttons to the right

                    ImGuiStyle& style = ImGui::GetStyle();
                    float fbs= style.FrameBorderSize;
                    style.FrameBorderSize = 0;
                    float th = ImGui::GetTextLineHeight();
                    float fh = ImGui::GetFrameHeight();
                    ImVec2 size(th,th);

                    int width = fh+2;                   


                    ImGui::SameLine(ImGui::GetWindowWidth()-width*3);
                    if(spTextureMin_.get())
                        ImGui::ImageButton(spTextureMin_->texture(),size);
                    else
                        ImGui::Button("\xef\x8b\x91",size);  // ICON_FK_WINDOW_MINIMIZE

                    ImGui::SameLine(ImGui::GetWindowWidth()-width*2);
                    if(spTextureMax_.get())
                        ImGui::ImageButton(spTextureMax_->texture(),size);
                    else
                        ImGui::Button("\xef\x8b\x92",size);  // ICON_FK_WINDOW_RESTORE


                    ImGui::SameLine(ImGui::GetWindowWidth()-width*1);
                    if(spTextureClose_.get())
                        ImGui::ImageButton(spTextureClose_->texture(),size);
                    else
                        ImGui::Button("\xef\x80\x8d",size);  // ICON_FK_TIMES


                    style.FrameBorderSize = fbs;

                }

            
                ImGui::EndMenuBar();
            }
        }

        return r;
    }
}

