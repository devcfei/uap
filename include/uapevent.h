#ifndef _UAP_EVENT_H_
#define _UAP_EVENT_H_

#ifndef _UAP_APP_H_
#error uapevent.h requires uapapp.h to be included first
#endif

namespace uap
{


    typedef Ulong EventId;
    typedef UlongLong *EventArg;

    // {44cbd895-71b5-46e0-82d0-01866fea9c64}
    DEFINE_UUID(IID_IEVENTDISPATCHER,
                0x44cbd895, 0x71b5, 0x46e0, 0x82, 0xd0, 0x01, 0x86, 0x6f, 0xea, 0x9c, 0x64);

    class IEventDispatcher : public IUniversal
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IEventDispatcher
        virtual Result initialize(IAttributes *piAttributes) = 0;
        virtual Result dispatch(EventId eventId, EventArg a, EventArg b ) = 0;


        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IEVENTDISPATCHER;
    }; // @class IEventDispatcher


    // {14b1b585-2d32-4d90-b64e-8272ab02ac5f}
    DEFINE_UUID(IID_IEVENT,
                0x14b1b585, 0x2d32, 0x4d90, 0xb6, 0x4e, 0x82, 0x72, 0xab, 0x02, 0xac, 0x5f);

    class IEvent : public IUniversal
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IEvent
        virtual Result initialize(IAttributes *piAttributes) = 0;
        virtual Result addDispatcher(IEventDispatcher * piEventDispatcher) = 0;
        virtual Result postEvent(EventId id, EventArg a, EventArg b) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IEVENT;
    }; // @class IEvent

} // @namespace uap

#endif // _UAP_EVENT_H_