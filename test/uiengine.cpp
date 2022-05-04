#include <gtest/gtest.h>
#include <uap.h>
#include <uapuiengine.h>




TEST(uiengine, Interface)
{
    uap::Result r;

    uap::sptr<uap::IUiEngine> sp;

    r = uap::uapGetInterface(IID_IMAGEENGINE, (uap::IUnknown**)&sp);
    EXPECT_EQ(r, uap::R_OK);

    r = sp->initialize();
    EXPECT_EQ(r, uap::R_OK);

}
