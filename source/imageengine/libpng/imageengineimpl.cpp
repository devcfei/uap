#include "imageengineimpl.h"


namespace uap
{
    Ulong ImageEngineImpl::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong ImageEngineImpl::release()
    {

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
