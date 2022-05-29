#include "common.h"


static void ComponentCreateInstance()
{
    sptr<IFooBar> sp;
    FooBarImpl::createInstance(sp.getaddrof());
}

TEST(Component, CreateInstance)
{

    ComponentCreateInstance(); // Demostrate how to use sptr to create instance without delete

    EXPECT_EQ(0, FooBarImpl::memcount);
}