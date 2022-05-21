#include "headers.h"


static void ComponentCreateInstance()
{
    sptr<IFoo> sp;
    FooImpl::createInstance((void **)&sp);
}

TEST(Component, CreateInstance)
{

    ComponentCreateInstance(); // Demostrate how to use sptr to create instance without delete

    EXPECT_EQ(0, FooImpl::memcount);
}