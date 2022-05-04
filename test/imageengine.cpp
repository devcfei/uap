#include <gtest/gtest.h>
#include <uap.h>
#include <uapimageengine.h>




TEST(imageengine, Interface)
{
    uap::Result r;

    uap::sptr<uap::IImageEngine> sp;

    r = uap::uapGetInterface(IID_IMAGEENGINE, (uap::IUnknown**)&sp);
    EXPECT_EQ(r, uap::R_OK);

    r = sp->initialize();
    EXPECT_EQ(r, uap::R_OK);

}
