#ifndef _EVENTDISPATCH_H_
#define _EVENTDISPATCH_H_


enum EventIdEnum
{
    Event_Test0 =0,
    Event_Test1 =1,

    Event_AppUser= 1000,
    Event_FileOpen,
    Event_AppExit,
    Event_AppAbout,
    Event_ViewToolBar,
    Event_ViewStatusBar,
    Event_ViewPanelGeneric,
    Event_ViewPanelFileBrowser,
    Event_ViewPanelLog,
};



class EventDispatcherImpl : public IEventDispatcher
{
public:
    // IUniversal
    virtual Ulong addRef();
    virtual Ulong release();
    virtual Result queryInterface(const Uuid &, void **);

    // IEventDispatcher
    virtual Result initialize(IAttributes *piAttributes);
    virtual Result dispatch(EventId eventId, EventArg a, EventArg b);

    static Result createInstance(IEventDispatcher **ppv)
    {
        EventDispatcherImpl *p = new EventDispatcherImpl();
        if (p)
        {
            *ppv = p;
            return R_SUCCESS;
        }
        return R_ERROR;
    }

private:
    EventDispatcherImpl()
        : refcount_(1)
    {
    }
    Ulong refcount_;
};

#endif //_EVENTDISPATCH_H_
