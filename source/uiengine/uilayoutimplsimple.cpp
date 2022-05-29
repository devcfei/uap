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
        if (uapUuidIsEqual(rUuid, IID_IUILAYOUT))
        {
            UiLayoutImplSimple *pi = static_cast<UiLayoutImplSimple *>(this);
            addRef();

            *((UiLayoutImplSimple **)ppv) = pi;
            r = R_SUCCESS;
        }
        return r;
    }

    Result UiLayoutImplSimple::initializeLayout(IUiEngine* piUiEngine, IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;

        INFO("UiLayoutImplSimple::initializeLayout\n");
        return r;
    }

    Result UiLayoutImplSimple::draw()
    { 
        Result r = R_SUCCESS;

        return r;
    }

} // @namespace uap