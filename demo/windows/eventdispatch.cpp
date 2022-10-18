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
    UAP_TRACE("EventImpl::release - refcount=%d\n", ref);
    if (!ref)
    {
        UAP_TRACE("EventImpl delete!!!!\n");
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

    return r;
}
