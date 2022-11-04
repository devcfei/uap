#include "framework.h"


Ulong GenericFrameImpl::addRef()
{
    Ulong ref = InterlockedIncrement(&refcount_);
    // UAP_TRACE("GenericFrameImpl::addRef- refcount=%d\n", ref);
    return ref;
}
Ulong GenericFrameImpl::release()
{
    Ulong ref = InterlockedDecrement(&refcount_);
    // UAP_TRACE("GenericFrameImpl::release - refcount=%d\n", ref);
    if (!ref)
    {
        UAP_TRACE("GenericFrameImpl delete!!!!\n");
        delete this;
    }
    return ref;
}
Result GenericFrameImpl::queryInterface(const Uuid &rUuid, void **ppv)
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

Result GenericFrameImpl::drawFrame()
{
    Result r = R_SUCCESS;

    spDraw_->addText("text",false);
    spDraw_->addButton("button",false);
    static Boolean checked =false;
    spDraw_->addCheckBox("checkbox", false, &checked);


    // Path browse
    static char path[MAX_PATH];
    spDraw_->addText("Path",false);
    spDraw_->addEdit("##Edit", true,  path, MAX_PATH);
    spDraw_->addButton("Browse...",true);
    




    return r;
}