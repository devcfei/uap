#include "uapbe.h"

namespace uap
{
    const Uuid& AttributesImpl::uuidof()
    {
        return uuid_;
    }

    Ulong AttributesImpl::addRef()
    {
        TRACE("AttributesImpl::addRef\n");

        return InterlockedIncrement(&refcount_);
    }
    Ulong AttributesImpl::release()
    {
        TRACE("AttributesImpl::release\n");

        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result AttributesImpl::queryInterface(const uap::Uuid &, void **)
    {
        return R_OK;
    }

    //
    Result AttributesImpl::setUint(Ulong key, Uint value)
    {
        TRACE("AttributesImpl::setUint - value=%d\n", value);
        return R_OK;
    }
    Result AttributesImpl::getUint(Ulong key, Uint &value)
    {
        TRACE("AttributesImpl::getUint\n");
        return R_OK;
    }

}; //@namespace uap
