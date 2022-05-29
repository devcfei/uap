#include "common.h"


namespace uap
{

    // globals

    static const Uuid iidGlobal[] =
        {
            IID_IAPPLICATION,
    };

    // component funcitons
    Result CreateInstance(const Uuid &iid, void **ppv)
    {

        Result r = R_NO_SUCH_INTERFACE;

        // UAP_TRACE("CreateInstance\n");

        if (uapUuidIsEqual(iid, IID_IAPPLICATION))
        {
            r = ApplicationImpl::createInstance((IApplication **)ppv);
        }

        return r;
    }

    Result RegisterComponent(const Uuid *iidArr, Ulong *count)
    {
        Result r = R_SUCCESS;

        // UAP_TRACE("RegisterComponent\n");

        if (iidArr == nullptr || count == nullptr)
        {

            *count = sizeof(iidGlobal) / sizeof(iidGlobal[0]);
            r = R_INVALID_PARAMETERS;
            return r;
        }

        if (*count < sizeof(iidGlobal) / sizeof(iidGlobal[0]))
        {
            r = R_BUFFER_TOO_SMALL;
            return r;
        }

        CopyMemory((void *)iidArr, iidGlobal, sizeof(iidGlobal));

        return r;
    }

};