#include "Test/TestSuite.h"

using namespace X3D::Test;

TEST(TestSuite, ExpectShouldFailIfNoEventReceived) {
    World* world = World::read(browser(),
        "data/ExpectShouldFailIfNoEventsReceived.xml");
    TestSuite* suite = browser()->getNode<TestSuite>("suite");
    ASSERT_THAT(suite, NotNull());
    suite->realize(); // TODO: root nodes should be realized automatically...
    suite->runTests();
    EXPECT_EQ(0, suite->numPassed());
    EXPECT_EQ(1, suite->numFailed());
    TestNode* test = suite->failed().getElements().front();
    ASSERT_THAT(test, NotNull());
    EXPECT_EQ("OnlyTest", test->getName());
    EXPECT_EQ(false, test->success());
    ASSERT_EQ(true, test->realized()) << "test has not been realized!";
    ASSERT_EQ(true, test->reasons.node()->realized()) << "test* has not been realized!";
    const list<string>& reasons = test->reasons().getElements();
    EXPECT_EQ(1, reasons.size());
    EXPECT_EQ("NeverActivated expected 216, but was never activated", reasons.front());
    delete world;
    browser()->reset();
}
