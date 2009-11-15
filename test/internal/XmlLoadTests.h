#include "internal/World.h"

TEST(XmlLoad, LoadedSceneShouldHaveCorrectStructure) {
    World* world = World::read(browser(), "data/foo.xml");
}
