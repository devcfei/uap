#include "common.h"


namespace uap
{

    
    Ulong UiLogWindowImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        //UAP_TRACE("UiLogWindowImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong UiLogWindowImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        //UAP_TRACE("UiLogWindowImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            UAP_TRACE("UiLogWindowImpl delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiLogWindowImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IUILOGWINDOW))
        {
            IUiLogWindow *pi = static_cast<IUiLogWindow *>(this);
            addRef();

            *((IUiLogWindow **)ppv) = pi;
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


    // IUiLogWindow

    Result UiLogWindowImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        INFO("UiLogWindowImpl::initialize\n");
        return r;
    }



    Result UiLogWindowImpl::addMessage(Char* name)
    {
        Result r = R_SUCCESS;


        log.AddLog(name);

        return r;
    }


    // IDraw
    Result UiLogWindowImpl::draw()
    {
        Result r = R_SUCCESS;

        static bool p_open=true;

        // For the demo: add a debug button _BEFORE_ the normal log window contents
        // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
        // Most of the contents of the window will be added by the log.Draw() call.
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
        ImGui::Begin("Log", &p_open);
        if (ImGui::SmallButton("[Debug] Add 5 entries"))
        {
            static int counter = 0;
            const char* categories[3] = { "info", "warn", "error" };
            const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
            for (int n = 0; n < 5; n++)
            {
                const char* category = categories[counter % IM_ARRAYSIZE(categories)];
                const char* word = words[counter % IM_ARRAYSIZE(words)];
                log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
                    ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
                counter++;
            }
        }
        ImGui::End();

        // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
        log.Draw("Log", &p_open);

        return r;
    }



}

