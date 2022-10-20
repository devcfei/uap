#include "common.h"


namespace uap
{

    Ulong ToolBarImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        //UAP_TRACE("ToolBarImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong ToolBarImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        //UAP_TRACE("ToolBarImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            //UAP_TRACE("delete ToolBarImpl!!!!!\n");
            delete this;
        }
        return ref;
    }
    Result ToolBarImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_ITOOLBAR))
        {
            IToolBar *pi = static_cast<IToolBar *>(this);
            addRef();

            *((IToolBar **)ppv) = pi;
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


    // IToolBar

    Result ToolBarImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        INFO("ToolBarImpl::initialize\n");
        return r;
    }


    Result ToolBarImpl::buildToolBarFromTTF(const Char* filename, Ushort min, Ushort max)
    {
        Result r = R_SUCCESS;


        ImGuiIO &io = ImGui::GetIO();

        

        ImFontConfig config;
        config.MergeMode = true;
        config.GlyphMinAdvanceX = 18.0f; // Use if you want to make the icon monospaced
        static const ImWchar icon_ranges[] = { min, max, 0 };
        io.Fonts->AddFontFromFileTTF(filename, 18.0f, &config, icon_ranges);
        io.Fonts->Build();



        return r;
    }


    Result ToolBarImpl::addButton(const Char* label)
    {
        Result r = R_SUCCESS;

        vecLabel_.push_back(label);
        return r;
    }
    // IDraw
    Result ToolBarImpl::draw()
    {
        Result r = R_SUCCESS;


        // Particular window styling
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0,255,0,0));



        ImGui::BeginChild("Toolbar", ImVec2(0, heightToolBar_), false);




        for(auto it: vecLabel_)
        {
            ImGui::Button((it), ImVec2(32, 32));ImGui::SameLine();

        }




        ImGui::EndChild();

        ImGui::PopStyleColor();


        return r;
    }



}

