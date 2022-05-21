#include "comp.h"

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
    Result ImageEngineImpl::initialize(IApplication *piApp)
    {
        Result r;
        UAP_TRACE("ImageEngineImpl::initialize\n");
        UAP_TRACE("refcount_=%d\n", this->refcount_);
        UAP_TRACE("piApp=%p\n", piApp);

        spApp_ = piApp;

        sptr<IAttributes> spAttributes;
        r = spApp_->createInterface(IID_IATTRIBUTES, (void **)&spAttributes);
        if (!UAP_SUCCESS(r))
        {
            return r;
        }

        Uint val = 36;
        spAttributes->setUint(UUID_NULL, val);
        spAttributes->getUint(UUID_NULL, val);

        return r;
    }

}; //@namespace uap
