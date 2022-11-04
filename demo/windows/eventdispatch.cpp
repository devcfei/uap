#include "framework.h"



// IUniversal
Ulong EventDispatcherImpl::addRef()
{
    Ulong ref = InterlockedIncrement(&refcount_);
    UAP_TRACE("EventImpl::addRef- refcount=%d\n", ref);
    return ref;
}
Ulong EventDispatcherImpl::release()
{
    Ulong ref = InterlockedDecrement(&refcount_);
    UAP_TRACE("EventDispatcherImpl::release - refcount=%d\n", ref);
    if (!ref)
    {
        UAP_TRACE("EventDispatcherImpl delete!!!!\n");
        delete this;
    }
    return ref;
}
Result EventDispatcherImpl::queryInterface(const Uuid &rUuid, void **ppv)
{
    Result r = R_NO_SUCH_INTERFACE;

    if (uapUuidIsEqual(rUuid, IID_IEVENTDISPATCHER))
    {
        IEventDispatcher *pi = static_cast<IEventDispatcher *>(this);
        addRef();

        *((IEventDispatcher **)ppv) = pi;
        r = R_SUCCESS;
    }

    return r;
}


// IEventDispatcher
Result EventDispatcherImpl::initialize(IAttributes *piAttributes)
{
    Result r = R_SUCCESS;


    return r;
}

Result EventDispatcherImpl::dispatch(EventId eventId, EventArg a, EventArg b)
{
    Result r = R_SUCCESS;

    UAP_TRACE("Event: Id=%d\n", eventId);

    App* pApp =(App*) ctx_;

    switch(eventId)
    {
    case Event_AppExit:
    {
        exit(0); // TODO: better exit sequence?
        break;
    }
    case Event_FileOpen:
    {
        pApp->onFileOpenClicked();
        break;
    }
    case Event_FolderOpen:
    {
        pApp->onFolderOpenClicked();
        break;
    }

    case Event_SaveAs:
    {
        pApp->onFileSaveAsClicked();
        break;
    }

    case Event_OpenSettings:
    {
        pApp->onFileSettings();
        break;
    }
    


    case Event_ViewPanelGeneric:
    {
        pApp->onViewPanelGenericClicked();
        break;
    }

    case Event_ViewPanelLog:
    {
        pApp->onViewPanelLogClicked();
        break;
    }
    case Event_ViewPanelFileBrowser:
    {
        pApp->onViewPanelFileBrowserClicked();
        break;
    }
    
#if defined(_DEBUG)
    case Event_HelpImGuiDemo:
    {
        pApp->onHelpImGuiDemoClicked();
        break;
    }

    case Event_HelpImPlotDemo:
    {
        pApp->onHelpImPlotDemoClicked();
        break;
    }
#endif


    case Event_WindowClosed:
    {


        pApp->onWindowClosed((IWindow*) a);
        

        break;
    }


    case Event_FileBrowserClicked:
    {
        TCHAR* p = (TCHAR*)a;

        std::tstring str =p;
        pApp->onFileBrowserClicked(str);

    }


    default:
        break;

    }

    return r;
}
