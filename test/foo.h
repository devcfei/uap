#ifndef _FOO_H_
#define _FOO_H_

#include <uap.h>
using namespace uap;

// {d9077bcd-f78b-4afd-ab4c-5c1f0be91283}
DEFINE_UUID(UUID_IFOO,
            0xd9077bcd, 0xf78b, 0x4afd, 0xab, 0x4c, 0x5c, 0x1f, 0x0b, 0xe9, 0x12, 0x83);

// {825c724c-e1a5-4272-9225-8158de6de005}
DEFINE_UUID(UUID_IFOOBAR,
            0x825c724c, 0xe1a5, 0x4272, 0x92, 0x25, 0x81, 0x58, 0xde, 0x6d, 0xe0, 0x05);

class IFoo : public IUniversal
{
public:
    // IUniversal
    virtual Ulong addRef() = 0;
    virtual Ulong release() = 0;
    virtual Result queryInterface(const Uuid &uuid, void **ppv) = 0;

    // IFoo
    virtual Result foo() = 0;

    // uuid
    static const Uuid uuid()
    {
        return uuid_;
    }

private:
    inline static const Uuid uuid_ = UUID_IFOO;
};

class IFooBar : public IFoo
{
public:
    // IFooBar
    virtual Result foobar() = 0;

    // uuid
    static const Uuid uuid()
    {
        return uuid_;
    }

private:
    inline static const Uuid uuid_ = UUID_IFOOBAR;
};

class FooImpl : public IFooBar
{
public:
    virtual Ulong addRef()
    {
        ++refcount_;
        UAP_TRACE("addRef = %d\n", refcount_);
        return refcount_;
    }
    virtual Ulong release()
    {
        refcount_--;
        UAP_TRACE("release = %d\n", refcount_);
        if (refcount_ == 0)
        {
            delete this;
        }
        return refcount_;
    }

    virtual Result queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, UUID_IFOO))
        {
            IFoo *pi = static_cast<IFoo *>(this);

            addRef();

            *((IFoo **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, UUID_IFOOBAR))
        {
            IFooBar *pi = static_cast<IFooBar *>(this);
            addRef();

            *((IFooBar **)ppv) = pi;

            r = R_SUCCESS;
        }

        return r;
    }

    inline static int memcount = 0;
    void *operator new(size_t size)
    {
        memcount++;
        UAP_TRACE("new memcount = %d\n", memcount);

        return malloc(size);
    }

    void operator delete(void *p)
    {
        memcount--;
        UAP_TRACE("delete memcount = %d\n", memcount);
        free(p);
    }

    static Result createInstance(void **ppv)
    {
        FooImpl *p = new FooImpl();
        if (p)
        {
            *(IFoo **)ppv = p;
            return R_SUCCESS;
        }
        return R_ERROR;
    }
    virtual Result foo()
    {
        UAP_TRACE("FooImpl::foo()\n");
        return R_SUCCESS;
    }

    virtual Result foobar()
    {
        UAP_TRACE("FooImpl::foobar()\n");
        return R_SUCCESS;
    }

private:
    FooImpl()
        : refcount_(1)
    {
    }

    Ulong refcount_;
};

#endif // _FOO_H_