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

// {42b58fca-6e66-403b-b3b4-1cd51a2a3fd1}
DEFINE_UUID(UUID_IBAR, 
            0x42b58fca, 0x6e66, 0x403b, 0xb3, 0xb4, 0x1c, 0xd5, 0x1a, 0x2a, 0x3f, 0xd1);

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

class IBar : public IUniversal
{
public:
    // IUniversal
    virtual Ulong addRef() = 0;
    virtual Ulong release() = 0;
    virtual Result queryInterface(const Uuid &uuid, void **ppv) = 0;

    // IBar
    virtual Result bar() = 0;

    // uuid
    static const Uuid uuid()
    {
        return uuid_;
    }

private:
    inline static const Uuid uuid_ = UUID_IBAR;
};

class IFooBar : public IFoo
{
public:
    // IFooBar
    virtual Result foobar() = 0;

    virtual Result createBar(IBar** ppiBar) = 0;
    virtual Result setBar(IBar* piBar) = 0;
    virtual Result getBar(IBar** piBar) = 0;


    // uuid
    static const Uuid uuid()
    {
        return uuid_;
    }

private:
    inline static const Uuid uuid_ = UUID_IFOOBAR;
};




class BarImpl : public IBar
{
public:
    // IUniversal
    virtual Ulong addRef()
    {
        ++refcount_;
        UAP_TRACE("BarImpl::addRef = %d\n", refcount_);
        return refcount_;
    }

    virtual Ulong release()
    {
        refcount_--;
        UAP_TRACE("BarImpl::release = %d\n", refcount_);
        if (refcount_ == 0)
        {
            delete this;
        }
        return refcount_;
    }

    virtual Result queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, UUID_IBAR))
        {
            IBar *pi = static_cast<IBar *>(this);

            addRef();

            *((IBar **)ppv) = pi;
            r = R_SUCCESS;
        }


        return r;
    }
    // IBar
    virtual Result bar()
    {
        UAP_TRACE("BarImpl::bar()\n");
        return R_SUCCESS;
    }

    inline static int memcount = 0;
    void *operator new(size_t size)
    {
        memcount++;
        UAP_TRACE("BarImpl::new memcount = %d\n", memcount);

        return malloc(size);
    }

    void operator delete(void *p)
    {
        memcount--;
        UAP_TRACE("BarImpl::delete memcount = %d\n", memcount);
        free(p);
    }
    static Result createInstance(void **ppv)
    {
        BarImpl *p = new BarImpl();
        if (p)
        {
            *(IBar **)ppv = p;
            return R_SUCCESS;
        }
        return R_ERROR;
    }

private:
    BarImpl()
        : refcount_(1)
    {
    }
    Ulong refcount_;

};



class FooImpl : public IFooBar
{
public:
    virtual Ulong addRef()
    {
        ++refcount_;
        UAP_TRACE("FooImpl::addRef = %d\n", refcount_);
        return refcount_;
    }
    virtual Ulong release()
    {
        refcount_--;
        UAP_TRACE("FooImpl::release = %d\n", refcount_);
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
        UAP_TRACE("FooImpl::new memcount = %d\n", memcount);

        return malloc(size);
    }

    void operator delete(void *p)
    {
        memcount--;
        UAP_TRACE("FooImpl::delete memcount = %d\n", memcount);
        free(p);
    }

    Result createBar(IBar** ppiBar)
    {
        sptr<IBar> sp;
        BarImpl::createInstance((void**)&sp);

        *ppiBar = sp.get();
        (*ppiBar)->addRef();

        return R_SUCCESS;
    }
    Result setBar(IBar* piBar)
    {
        spBar_ = piBar;
        return R_SUCCESS;
    }
    Result getBar(IBar* *ppiBar)
    {
        *ppiBar = spBar_.get();
        (*ppiBar)->addRef();
        return R_SUCCESS;
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

    sptr<IBar> spBar_;
};

#endif // _FOO_H_