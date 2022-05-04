#include "imageengineimpl.h"


namespace uap
{
    const Uuid& ImageEngineImpl::uuidof()
    {
        return uuid_;
    }

    Ulong ImageEngineImpl::addRef()
    {
        TRACE("ImageEngineImpl::addRef\n");

        return InterlockedIncrement(&refcount_);
    }
    Ulong ImageEngineImpl::release()
    {
        TRACE("CAttributesImpl::release\n");

        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result ImageEngineImpl::queryInterface(const uap::Uuid &, void **)
    {
        return R_OK;
    }

    //
    Result ImageEngineImpl::initialize()
    {
        TRACE("ImageEngineImpl::initialize\n");
        return R_OK;
    }


}; //@namespace uap
