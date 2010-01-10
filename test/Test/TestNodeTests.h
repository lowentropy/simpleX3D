#include "Test/TestNode.h"
#include "Test/Expect.h"

using X3D::Test::Expect;

TEST(TestNode, ShouldParseNodeWithExpects) {
    // load scene and get components
    World* world;
    ASSERT_NO_THROW(world = World::read(browser(), "data/Expects.xml"));
    Node* node = browser()->getNode("test");
    ASSERT_THAT(node, NotNull());
    Expect* e1 = node->getField<Expect>("expect1");
    Expect* e2 = node->getField<Expect>("expect2");
    ASSERT_THAT(e1, NotNull());
    ASSERT_THAT(e2, NotNull());
    EXPECT_EQ(X3DField::SFINT32, e1->get().getType());
    EXPECT_EQ(SFInt32(216), e1->get());
    MFString list;
    list.add("foo");
    list.add("bar");
    list.add("baz");
    EXPECT_EQ(X3DField::MFSTRING, e2->get().getType());
    EXPECT_EQ(list, e2->get());
    // TODO: replace complex error message construction with custom types
    //       (like basetypemismatch)
    delete world;
    browser()->reset();
}
