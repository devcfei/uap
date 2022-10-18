#include "common.h"

namespace uap
{

    // IUniversal
    Ulong EventImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        UAP_TRACE("EventImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong EventImpl::release()
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
    Result EventImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IEVENT))
        {
            IEvent *pi = static_cast<IEvent *>(this);
            addRef();

            *((IEvent **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }

    // IEvent
    Result EventImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;

        InitializeCriticalSection(&cs_);

        semaphore_ = CreateSemaphore(
            NULL,           // default security attributes
            0,              // initial count
            maxeventcount_, // maximum count
            NULL);          // unnamed semaphore

        hThread_ = CreateThread(
            NULL,          // default security attributes
            0,             // use default stack size
            threadProc,    // thread function name
            this,          // argument to thread function
            0,             // use default creation flags
            &dwThreadId_); // returns the thread identifier

        return r;
    }

    Result EventImpl::addDispatcher(IEventDispatcher *piEventDispatcher)
    {
        Result r = R_SUCCESS;
        EnterCriticalSection(&cs_);

        spDispatcher_ = piEventDispatcher;
        LeaveCriticalSection(&cs_);

        return r;
    }

    Result EventImpl::postEvent(EventId id, EventArg a, EventArg b)
    {
        Result r = R_SUCCESS;

        EventPacket packet = {id, a, b};

        UAP_TRACE("push Event, evtId = %d\n", id);
        EnterCriticalSection(&cs_);

        listEventPacket_.push_back(packet);

        if (!ReleaseSemaphore(
                semaphore_, // handle to semaphore
                1,          // increase count by one
                NULL))
        {

            r = R_ERROR;
        }

        LeaveCriticalSection(&cs_);

        return r;
    }

    DWORD WINAPI EventImpl::threadProc(LPVOID lpParam)
    {
        Result r = R_SUCCESS;

        EventImpl *p = static_cast<EventImpl *>(lpParam);

        r = p->processEvent();

        return 0;
    }

    Result EventImpl::processEvent()
    {
        Result r = R_SUCCESS;

        while (1)
        {
            DWORD dwWaitResult;

            EventPacket packet;

            dwWaitResult = WaitForSingleObject(
                semaphore_, // handle to semaphore
                INFINITE);

            // UAP_TRACE("get Event\n");

            switch (dwWaitResult)
            {
            // The semaphore object was signaled.
            case WAIT_OBJECT_0:

                EnterCriticalSection(&cs_);
                packet = listEventPacket_.front();
                LeaveCriticalSection(&cs_);

                if (spDispatcher_.get())
                {
                    r = spDispatcher_->dispatch(packet.id, packet.a, packet.b);
                }

                EnterCriticalSection(&cs_);
                listEventPacket_.pop_front();
                LeaveCriticalSection(&cs_);

                break;

            // The semaphore was nonsignaled, so a time-out occurred.
            case WAIT_TIMEOUT:
                r = R_ERROR;
                break;
            }

            if (r == R_ERROR)
            {
                break;
            }
        }

        return r;
    }

} // @namespace uap