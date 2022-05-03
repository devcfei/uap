#include "uapbe.h"

namespace uap
{
    const Uuid& CAttributesImpl::uuidof()
    {
        return uuid_;
    }

    Ulong CAttributesImpl::addRef()
    {
        TRACE("CAttributesImpl::addRef\n");

        return InterlockedIncrement(&refcount_);
    }
    Ulong CAttributesImpl::release()
    {
        TRACE("CAttributesImpl::release\n");

        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result CAttributesImpl::queryInterface(const uap::Uuid &, void **)
    {
        return R_OK;
    }

    //
    Result CAttributesImpl::setUint(Ulong key, Uint value)
    {
        TRACE("CAttributesImpl::setUint\n");
        return R_OK;
    }
    Result CAttributesImpl::getUint(Ulong key, Uint &value)
    {
        TRACE("CAttributesImpl::getUint\n");
        return R_OK;
    }

}; //@namespace uap
