#include "framework.h"


Ulong SettingFrameImpl::addRef()
{
    Ulong ref = InterlockedIncrement(&refcount_);
    // UAP_TRACE("SettingFrameImpl::addRef- refcount=%d\n", ref);
    return ref;
}
Ulong SettingFrameImpl::release()
{
    Ulong ref = InterlockedDecrement(&refcount_);
    // UAP_TRACE("SettingFrameImpl::release - refcount=%d\n", ref);
    if (!ref)
    {
        UAP_TRACE("SettingFrameImpl delete!!!!\n");
        delete this;
    }
    return ref;
}
Result SettingFrameImpl::queryInterface(const Uuid &rUuid, void **ppv)
{
    Result r = R_NO_SUCH_INTERFACE;

    if (uapUuidIsEqual(rUuid, IID_IFRAME))
    {
        IFrame *pi = static_cast<IFrame *>(this);
        addRef();

        *((IFrame **)ppv) = pi;
        r = R_SUCCESS;
    }
    return r;
}

Result SettingFrameImpl::drawFrame()
{
    Result r = R_SUCCESS;

    spDraw_->addText("Setting...",false);

    return r;
}