#include "common.h"

static void FooSmartPtrArgumentPointor()
{
    sptr<IFoo> sp;
    FooImpl::createInstance(sp.getaddrof());

    sptr<IFoo> sp1(sp);  // constructor
    sptr<IFoo> sp2(sp1); // constructor
    sptr<IFoo> sp3 = sp; // copy constructor
    sptr<IFoo> sp4;      // default constructor
    sp4 = sp;            // operator=
}

TEST(SmartPtr, SmartPtrArgumentPointor)
{

    FooSmartPtrArgumentPointor();

    EXPECT_EQ(0, FooImpl::memcount);
}

static void FooSmartPtrAs()
{
    Result r;
    sptr<IFooBar> sp;
    FooBarImpl::createInstance(sp.getaddrof());
    sp->foobar();

    sptr<IFoo> spFoo;
    r = sp.as(&spFoo);

    spFoo->foo();
    EXPECT_EQ(r, R_SUCCESS);
}

TEST(SmartPtr, SmartPtrAs)
{
    FooSmartPtrAs();
    EXPECT_EQ(0, FooBarImpl::memcount);
}

static void FooSmartPtrCreateInstace()
{
    Result r;
    sptr<IFooBar> sp;
    FooBarImpl::createInstance(sp.getaddrof());

    sptr<IBar> spBar;
    r = sp->createInstance(IID_IBAR, (void **)spBar.getaddrof());
    EXPECT_EQ(r, R_SUCCESS);
    spBar->bar();
    spBar->setFooBar(sp.get());
}

TEST(SmartPtr, SmartPtrCreateInstance)
{

    FooSmartPtrCreateInstace();

    EXPECT_EQ(0, FooBarImpl::memcount);
    EXPECT_EQ(0, BarImpl::memcount);
}

class FooBar
{
public:
    Result init()
    {
        Result r;
        r = FooBarImpl::createInstance(spFooBar_.getaddrof());

        r = spFooBar_->createInstance(IID_IBAR, (void **)spBar_.getaddrof());
        EXPECT_EQ(r, R_SUCCESS);

        spBar_->setFooBar(spFooBar_.get());


        return r;
    }

private:
    sptr<IFooBar> spFooBar_;

    sptr<IBar> spBar_;
};

static void FooSmartPtrClass()
{
    FooBar *p = new FooBar;

    p->init();

    delete p;
}

TEST(SmartPtr, SmartPtrClass)
{

    FooSmartPtrClass();

    EXPECT_EQ(0, FooBarImpl::memcount);
    EXPECT_EQ(0, BarImpl::memcount);
}
