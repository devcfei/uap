#include "common.h"

namespace uap
{

    Ulong DrawImpl::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }

    Ulong DrawImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            UAP_TRACE("DrawImpl delete!!!!\n");
            delete this;
        }
        return ref;
    }

    Result DrawImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        if (uapUuidIsEqual(rUuid, IID_IDRAW))
        {
            IDraw *pi = static_cast<IDraw *>(this);
            addRef();

            *((IDraw **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }



}; //@namespace uap
