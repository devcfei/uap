#include "common.h"

TEST(EVENT, simple)
{
    Result r;

    sptr<IApplication> spApp;

    r = uapCreateApplication(spApp.getaddrof());
    EXPECT_EQ(r, R_SUCCESS);

    sptr<IEvent> spEvent;
    r = spApp->createInstance(IID_IEVENT, (void **)&spEvent);
    EXPECT_EQ(r, R_SUCCESS);

    r = spEvent->initialize(nullptr);
    EXPECT_EQ(r, R_SUCCESS);
}