#include "Test/TestSuite.h"

using namespace X3D::Test;

TEST(TestSuite, ExpectShouldFailIfNoEventReceived) {
    // load the world
    World* world = World::read(browser(),
        "data/ExpectShouldFailIfNoEventsReceived.xml");

    // get the test suite
    TestSuite* suite = browser()->getNode<TestSuite>("suite");
    ASSERT_THAT(suite, NotNull());

    // run the tests
    suite->realize(); // TODO: root nodes should be realized automatically...
    suite->runTests();

    // check correct num passed/failed
    EXPECT_EQ(0, suite->numPassed());
    EXPECT_EQ(1, suite->numFailed());

    // get the failed tests
    TestNode* test = suite->failed().getElements().front();
    ASSERT_THAT(test, NotNull());

    // make sure it failed
    EXPECT_EQ("OnlyTest", test->getName());
    EXPECT_EQ(false, test->success());

    // make sure the failure reason is correct
    const list<string>& reasons = test->reasons().getElements();
    EXPECT_EQ(1, reasons.size());
    EXPECT_EQ("NeverActivated expected 216, but was never activated", reasons.front());

    // clean up
    delete world;
    browser()->reset();
}
