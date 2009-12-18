#include "internal/World.h"

TEST(XmlLoad, LoadedSceneShouldHaveCorrectStructure) {
    World* world = World::read(browser(), "data/foo.xml");
    Node* a = browser()->getNode("A");
    Node* b = browser()->getNode("B");
    ASSERT_THAT(a, NotNull());
    ASSERT_THAT(b, NotNull());
    EXPECT_EQ(SFTime(3), a->getField("cycleInterval")->get());
    EXPECT_EQ(SFTime(5), b->getField("cycleInterval")->get());
    EXPECT_EQ(SFBool(true), a->getField("loop")->get());
    EXPECT_EQ(SFBool(false), b->getField("loop")->get());
    const list<Route*>& routes = a->getField("time")->getOutgoingRoutes();
    EXPECT_EQ(1, routes.size());
    const Route* route = routes.front();
    EXPECT_EQ(a, route->fromField->getNode());
    EXPECT_EQ(b, route->toField->getNode());
    EXPECT_EQ(a->getField("time"), route->fromField);
    EXPECT_EQ(b->getField("pauseTime"), route->toField);
    delete world;
    browser()->reset();
}
