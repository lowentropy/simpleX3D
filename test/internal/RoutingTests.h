#include "internal/Route.h"

class RouteTestNode : public Node {
public:
    class TestOutField : public OutField<RouteTestNode,SFString> {
        void action() {
            EXPECT_EQ("foo", value());
        }
    } testOut;
    class TestInField : public InField<RouteTestNode,SFString> {
        void action(const string& str) {
            EXPECT_EQ("foo", str);
        }
    } testIn;
};

bool doneInit = false;

class RoutingTests : public ::testing::Test {
public:
    void SetUp() {
        if (doneInit) return;
        doneInit = true; // XXX
        Component* test = browser()->profile->createComponent("RouteTests");
        NodeDefImpl<RouteTestNode>* def =
            test->createNode<RouteTestNode>("RouteTestNode");
        def->createField("testIn",
            X3DField::SFSTRING, SAIField::INPUT_ONLY,
            &RouteTestNode::testIn);
        def->createField("testOut",
            X3DField::SFSTRING, SAIField::OUTPUT_ONLY,
            &RouteTestNode::testOut);
        def->finish();
    }
};

TEST_F(RoutingTests, ManuallyRouteOutToIn) {
    RouteTestNode* from = browser()->createNode<RouteTestNode>("RouteTestNode");
    Node* to = browser()->createNode("RouteTestNode");
    from->realize();
    to->realize();
    browser()->addSource(from);
    browser()->createRoute(from, "testOut", to, "testIn");
    from->testOut("foo");
    browser()->route();
}
