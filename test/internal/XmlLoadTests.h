#include "internal/World.h"

TEST(XmlLoad, LoadedSceneShouldHaveCorrectStructure) {
    World* world = World::read(browser(), "data/foo.xml");
    Node* a = browser()->getNodeByName("A");
    Node* b = browser()->getNodeByName("B");
    ASSERT_THAT(a, NotNull());
    ASSERT_THAT(b, NotNull());
    EXPECT_EQ(SFTime(3), a->getField("cycleInterval")->get());
    EXPECT_EQ(SFTime(5), b->getField("cycleInterval")->get());
}
