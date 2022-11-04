#include "common.h"

namespace uap
{

    Ulong LogWindowImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        // UAP_TRACE("LogWindowImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong LogWindowImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        // UAP_TRACE("LogWindowImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            UAP_TRACE("LogWindowImpl delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result LogWindowImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_ILOGWINDOW))
        {
            ILogWindow *pi = static_cast<ILogWindow *>(this);
            addRef();

            *((ILogWindow **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_IWINDOW))
        {
            IWindow *pi = static_cast<IWindow *>(this);
            addRef();

            *((IWindow **)ppv) = pi;
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

    Result LogWindowImpl::drawPrimitives()
    {
        Result r = R_SUCCESS;

        if (ImGui::SmallButton("[Debug] Add 5 entries"))
        {
            static int counter = 0;
            const char *categories[3] = {"info", "warn", "error"};
            const char *words[] = {"Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent"};
            for (int n = 0; n < 5; n++)
            {
                const char *category = categories[counter % IM_ARRAYSIZE(categories)];
                const char *word = words[counter % IM_ARRAYSIZE(words)];
                log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
                           ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
                counter++;
            }
        }

        // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
        log.Draw(title_.c_str(), &open_);
        return r;
    }

    // ILogWindow
    Result LogWindowImpl::addMessage(Char *name)
    {
        Result r = R_SUCCESS;
        log.AddLog(name);
        return r;
    }
}
