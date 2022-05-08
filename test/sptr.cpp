#include <gtest/gtest.h>
#include <uap.h>



class iptr : public uap::IUnknown
{
public:
    virtual const uap::Uuid& uuidof() = 0;
    virtual uap::Ulong addRef() = 0;
    virtual uap::Ulong release() = 0;
    virtual uap::Result queryInterface(const uap::Uuid &, void **) = 0;
};

class ptrimpl: public iptr
{
public:
    ptrimpl()
    :refcount_(1)
    {
    }
        virtual const uap::Uuid& uuidof()
        {
            return uuid_;
        }
    virtual uap::Ulong addRef()
    {
        return ++refcount_;

    }
    virtual uap::Ulong release()
    {
        refcount_--;
        if(refcount_==0)
        {
            delete this;
        }
        return refcount_;
    }

    virtual uap::Result queryInterface(const uap::Uuid &, void **)
    {
        return uap::R_OK;
    }
private:
    const uap::Uuid uuid_= IDD_IAPP;
    uap::Ulong refcount_;
};




TEST(sptr, copy)
{
    //uap::Result r;

    ptrimpl* p=new ptrimpl();

    uap::sptr<iptr> sp;
    sp = p;

    uap::sptr<iptr> spApp_;
    spApp_ = sp.get();
}
