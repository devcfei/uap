#ifndef _EVENT_IMPL_H_
#define _EVENT_IMPL_H_

// implementation for uap::IEvent

namespace uap
{
    class EventImpl : public IEvent
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &, void **);

        // IEvent
        virtual Result initialize(IAttributes *piAttributes);
        virtual Result addDispatcher(IEventDispatcher * piEventDispatcher);
        virtual Result postEvent(EventId id, EventArg a, EventArg b);


        static Result createInstance(IEvent **ppv)
        {
            EventImpl *p = new EventImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        EventImpl()
            : refcount_(1)
            , maxeventcount_(10000)
        {
        }
        Ulong refcount_;
        Ulong maxeventcount_;



        CRITICAL_SECTION cs_;

        HANDLE semaphore_;

        // worker thread
        HANDLE hThread_;
        DWORD dwThreadId_;
        static DWORD WINAPI threadProc(LPVOID lpParam);
        Result processEvent();


        struct EventPacket
        {
            EventId id;
            EventArg a;
            EventArg b;
        };

        std::list<EventPacket> listEventPacket_;
    

        sptr<IEventDispatcher> spDispatcher_;

    }; //@class EventImpl

} // @namespace uap

#endif //_EVENT_IMPL_H_