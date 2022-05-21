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
    Result ImageEngineImpl::queryInterface(const Uuid &, void **)
    {
        return R_SUCCESS;
    }

    //
    Result ImageEngineImpl::initialize()
    {
        UAP_TRACE("ImageEngineImpl::initialize\n");
        return R_SUCCESS;
    }


}; //@namespace uap
