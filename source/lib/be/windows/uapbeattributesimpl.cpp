#include "uapbe.h"

namespace uap
{

    Ulong CAttributesImpl::addRef()
    {
        return 0;
    }
    Ulong CAttributesImpl::release()
    {
        return 0;
    }
    Result CAttributesImpl::queryInterface()
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
