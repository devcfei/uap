#include "common.h"

namespace uap
{

    Ulong UiLayoutImplSimple::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong UiLayoutImplSimple::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            UAP_TRACE("UiLayoutImplSimple delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiLayoutImplSimple::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        if (uapUuidIsEqual(rUuid, IID_ILAYOUT))
        {
            UiLayoutImplSimple *pi = static_cast<UiLayoutImplSimple *>(this);
            addRef();

            *((UiLayoutImplSimple **)ppv) = pi;
            r = R_SUCCESS;
        }
        return r;
    }

    Result UiLayoutImplSimple::initializeLayout(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;

        INFO("UiLayoutImplSimple::initializeLayout\n");
        return r;
    }

    Result UiLayoutImplSimple::drawLayout()
    { 
        Result r = R_SUCCESS;

        return r;
    }

    Result UiLayoutImplSimple::addFrame(IUniversal *piDraw)
    {
        return R_SUCCESS;
    }
    
    Result UiLayoutImplSimple::deleteFrame(IUniversal *piDraw)
    {
        return R_SUCCESS;
    }


} // @namespace uap