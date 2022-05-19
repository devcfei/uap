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
        return R_OK;
    }

    //
    Result ImageEngineImpl::initialize(IApplication *piApp)
    {
        Result r;
        TRACE("ImageEngineImpl::initialize\n");
        TRACE("refcount_=%d\n", this->refcount_);
        TRACE("piApp=%p\n", piApp);

        spApp_ = piApp;

        uap::sptr<uap::IAttributes> spAttributes;
        r = spApp_->createInterface(IID_IATTRIBUTES, (void **)&spAttributes);
        if (!UAP_SUCCESS(r))
        {
            return r;
        }

        uap::Uint val = 36;
        spAttributes->setUint(UUID_NULL, val);
        spAttributes->getUint(UUID_NULL, val);

        return r;
    }

}; //@namespace uap
