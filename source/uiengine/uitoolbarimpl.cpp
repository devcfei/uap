#include "comp.h"


namespace uap
{

    Ulong UiToolBarImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        //UAP_TRACE("UiToolBarImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong UiToolBarImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        //UAP_TRACE("UiToolBarImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            //UAP_TRACE("delete UiToolBarImpl!!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiToolBarImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IUITOOLBAR))
        {
            IUiToolBar *pi = static_cast<IUiToolBar *>(this);
            addRef();

            *((IUiToolBar **)ppv) = pi;
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


    // IUiToolBar

    Result UiToolBarImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        return r;
    }


    Result UiToolBarImpl::buildToolBarFromTTF(const Char* filename, Ushort min, Ushort max)
    {
        Result r = R_SUCCESS;


        ImGuiIO &io = ImGui::GetIO();

        

        ImFontConfig config;
        config.MergeMode = true;
        config.GlyphMinAdvanceX = 18.0f; // Use if you want to make the icon monospaced
        static const ImWchar icon_ranges[] = { min, max, 0 };
        io.Fonts->AddFontFromFileTTF(filename, 18.0f, &config, icon_ranges);




        return r;
    }


    Result UiToolBarImpl::addButton(const Char* label)
    {
        Result r = R_SUCCESS;

        vecLabel_.push_back(label);
        return r;
    }
    // IDraw
    Result UiToolBarImpl::draw()
    {
        Result r = R_SUCCESS;

        ImGui::BeginChild("Toolbar", ImVec2(0, heightToolBar_), true);


        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(ImGui::GetStyle().FramePadding.x, ImGui::GetStyle().FramePadding.y + 10));


        for(auto it: vecLabel_)
        {
            ImGui::Button((it), ImVec2(32, 32));ImGui::SameLine();

        }


        ImGui::PopStyleVar();

        ImGui::EndChild();


        return r;
    }



}

