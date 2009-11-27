#include "Test/TestNode.h"
#include "Test/Expect.h"

using X3D::Test::Expect;

TEST(TestNode, ShouldParseNodeWithExpects) {
    // load scene and get components
    World* world;
    ASSERT_NO_THROW(world = World::read(browser(),
        "data/TestNodeShouldParseNodeWithExpects.xml"));
    Node* node = browser()->getNodeByName("test");
    ASSERT_THAT(node, NotNull());
    EXPECT_EQ(SFString("ShouldParseNodeWithExpects"), node->getField("name")->get());
    Expect* e1 = dynamic_cast<Expect*>(node->getField("expect1"));
    ASSERT_THAT(e1, NotNull());
    Expect* e2 = dynamic_cast<Expect*>(node->getField("expect2"));
    ASSERT_THAT(e2, NotNull());
    EXPECT_EQ(X3DField::SFINT32, e1->get().getType());
    EXPECT_EQ(SFInt32(216), e1->get());
    MFString list;
    list.add("foo");
    list.add("bar");
    list.add("baz");
    EXPECT_EQ(X3DField::MFSTRING, e2->get().getType());
    EXPECT_EQ(list, e2->get());
    // TODO: fields need to be deleting their outgoing routes on destruction
    // TODO: replace complex error message construction with custom types
    //       (like basetypemismatch)
    delete world;
    browser()->reset();
}
