#include "common.h"


namespace uap
{

    Ulong UiStatusBarImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        //UAP_TRACE("UiStatusBarImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong UiStatusBarImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        //UAP_TRACE("UiStatusBarImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            //UAP_TRACE("delete UiStatusBarImpl!!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiStatusBarImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IUISTATUSBAR))
        {
            IUiStatusBar *pi = static_cast<IUiStatusBar *>(this);
            addRef();

            *((IUiStatusBar **)ppv) = pi;
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


    // IUiStatusBar

    Result UiStatusBarImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        INFO("UiStatusBarImpl::initialize\n");
        return r;
    }

   
    // IDraw
    Result UiStatusBarImpl::draw()
    {
        Result r = R_SUCCESS;

        // Particular window styling
        ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(66,150,250,79));



        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        //ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Size.y - heightStatusBar_), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, heightStatusBar_), ImGuiCond_Appearing);
        ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y +viewport->Size.y- heightStatusBar_), ImGuiCond_Appearing);




        ImGui::BeginChild("StatusBar", ImVec2(0, heightStatusBar_), false);
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

        ImGui::PopStyleColor();


        return r;
    }



}

