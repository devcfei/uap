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



static void FooSmartPtrCreateInstace()
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


    sptr<IBar> spBar;
    spFoobar->createBar(spBar.getaddrof());

    spBar->bar();


    spFoobar->setBar(spBar.get());

    sptr<IBar> spBar2;

    spFoobar->getBar(spBar2.getaddrof());

    spBar2->bar();


}


TEST(SmartPtr, SmartPtrCreateInstance)
{

    FooSmartPtrCreateInstace();
    
    EXPECT_EQ(0, FooImpl::memcount);
    EXPECT_EQ(0, BarImpl::memcount);

}
