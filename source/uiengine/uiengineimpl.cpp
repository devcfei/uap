#include "comp.h"

namespace uap
{
    const Uuid& UiEngineImpl::uuidof()
    {
        return uuid_;
    }

    Ulong UiEngineImpl::addRef()
    {
        TRACE("UiEngineImpl::addRef\n");

        return InterlockedIncrement(&refcount_);
    }
    Ulong UiEngineImpl::release()
    {
        TRACE("UiEngineImpl::release\n");

        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result UiEngineImpl::queryInterface(const uap::Uuid &, void **)
    {
        return R_OK;
    }

    //
    Result UiEngineImpl::initialize()
    {
        TRACE("UiEngineImpl::initialize\n");
        return R_OK;
    }


}; //@namespace uap
