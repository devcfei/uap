#include "headers.h"



static void FooSmartPtrArgumentPointor()
{
    sptr<IFoo> p;
    FooImpl::createInstance((void **)&p);

    sptr<IFoo> sp(p);   // constructor
    sptr<IFoo> sp2(sp); // constructor
    sptr<IFoo> sp3 = p; // copy constructor
    sptr<IFoo> sp4;     // default constructor
    sp4 = p;            // operator=
}

TEST(SmartPtr, SmartPtrArgumentPointor)
{

    FooSmartPtrArgumentPointor();

    EXPECT_EQ(0, FooImpl::memcount);
}

static void FooSmartPtrAs()
{
    Result r;
    sptr<IUniversal> sp;
    FooImpl::createInstance((void **)&sp);

    sptr<IFoo> spFoo;
    r = sp.as(&spFoo);

    EXPECT_EQ(r, R_SUCCESS);

    spFoo->foo();

    sptr<IFooBar> spFoobar;
    r = sp.as(&spFoobar);

    EXPECT_EQ(r, R_SUCCESS);

    spFoobar->foobar();
}

TEST(SmartPtr, SmartPtrAs)
{
    FooSmartPtrAs();
    EXPECT_EQ(0, FooImpl::memcount);
}