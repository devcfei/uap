#include "common.h"


namespace uap
{

    Ulong FooImpl::addRef()
    {
        Ulong ref = ++refcount_;

        UAP_TRACE("FooImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong FooImpl::release()
    {
        Ulong ref = --refcount_;
        UAP_TRACE("FooImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            UAP_TRACE("FooImpl delete !!!!!\n");
            delete this;
        }
        return ref;
    }
    Result FooImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IFOO))
        {
            IFoo *pi = static_cast<IFoo *>(this);
            addRef();

            *((IFoo **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }


    // IFoo

    Result FooImpl::foo()
    {
        Result r = R_SUCCESS;
        UAP_TRACE("FooImpl::foo\n");
        return r;
    }

    ///////////////
    // BarImpl
    Ulong BarImpl::addRef()
    {
        Ulong ref = ++refcount_;

        UAP_TRACE("BarImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong BarImpl::release()
    {
        Ulong ref = --refcount_;
        UAP_TRACE("BarImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            UAP_TRACE("BarImpl delete !!!!!\n");
            delete this;
        }
        return ref;
    }
    Result BarImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IBAR))
        {
            IBar *pi = static_cast<IBar *>(this);
            addRef();

            *((IBar **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }


    // IBar

    Result BarImpl::bar()
    {
        Result r = R_SUCCESS;
        UAP_TRACE("FooImpl::bar\n");
        return r;
    }
    Result BarImpl::setFooBar(IFooBar* piFooBar)
    {
        Result r = R_SUCCESS;
        UAP_TRACE("BarImpl::setFooBar\n");
        spFooBar_ = piFooBar;
        return r;
    }



    ////////////////

    Ulong FooBarImpl::addRef()
    {
        Ulong ref = ++refcount_;

        UAP_TRACE("FooBarImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong FooBarImpl::release()
    {
        Ulong ref = --refcount_;
        UAP_TRACE("FooBarImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            UAP_TRACE("FooBarImpl delete !!!!!\n");
            delete this;
        }
        return ref;
    }
    Result FooBarImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IFOOBAR))
        {
            IFooBar *pi = static_cast<IFooBar *>(this);
            addRef();

            *((IFooBar **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_IFOO))
        {
            IFoo *pi = static_cast<IFoo *>(this);
            addRef();

            *((IFoo **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }


    // IFooBar

    Result FooBarImpl::foobar()
    {
        Result r = R_SUCCESS;
        UAP_TRACE("FooBarImpl::foobar\n");
        return r;
    }

    Result FooBarImpl::createInstance(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        if (uapUuidIsEqual(rUuid, IID_IBAR))
        {
            r = BarImpl::createInstance((IBar **)ppv);
        }

        return r;
    }

    // IFoo
    Result FooBarImpl::foo()
    {
        Result r = R_SUCCESS;
        UAP_TRACE("FooBarImpl::foo\n");
        return r;
    }

}