#include "internal/Route.h"
using ::testing::Eq;
using ::testing::AnyOf;

class RouteTestNode : public Node {
public:
    string inValue;
    string outValue;
    int inCount;
    int inOutFilterCount;
    int inOutActionCount;

    void setup() {
        inValue = "";
        outValue = "";
        inCount = 0;
        inOutFilterCount = 0;
        inOutActionCount = 0;
    }

    class TestInField : public InField<RouteTestNode,SFString> {
        void action(const string& str) {
            node()->inValue = str;
            node()->inCount++;
        }
    } testIn;

    class TestOutField : public OutField<RouteTestNode,SFString> {
        void action() {
            node()->outValue = value();
        }
    } testOut;

    DefaultInOutField<RouteTestNode,SFString> testInOut;

    class CustomIn : public InField<RouteTestNode,SFString> {
        void action(const string& str) {
            node()->testOut(str+str); // because doubling is good!
        }
    } customIn;

    class CountingInOut : public InOutField<RouteTestNode,SFString> {
        bool filter(const string& str) {
            node()->inOutFilterCount++;
            // just for safety, don't loop forever
            return (node()->inOutFilterCount < 10); 
        }

        void action() {
            node()->inOutActionCount++;
        }
    } countingInOut;
};

bool doneInit = false;

class RoutingTests : public ::testing::Test {
public:
    void SetUp() {
        if (!doneInit) {
            doneInit = true;
            Component* test = browser()->profile->createComponent("RouteTests");
            NodeDefImpl<RouteTestNode>* def =
                test->createNode<RouteTestNode>("RouteTestNode");
            def->createField("testIn", &RouteTestNode::testIn);
            def->createField("testOut", &RouteTestNode::testOut);
            def->createField("testInOut", &RouteTestNode::testInOut);
            def->createField("customIn", &RouteTestNode::customIn);
            def->createField("countingInOut", &RouteTestNode::countingInOut);
            def->finish();
        }
    }
};

TEST_F(RoutingTests, ManuallyRouteOutToIn) {
    RouteTestNode* from = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* to = browser()->createNode<RouteTestNode>("RouteTestNode");
    from->realize();
    to->realize();
    Route* route = browser()->createRoute(from, "testOut", to, "testIn");
    EXPECT_EQ("", from->inValue);
    EXPECT_EQ("", from->outValue);
    EXPECT_EQ("", to->inValue);
    EXPECT_EQ("", to->outValue);
    EXPECT_EQ(0, to->inCount);
    from->testOut("foo");
    EXPECT_EQ("", from->inValue);
    EXPECT_EQ("foo", from->outValue);
    EXPECT_EQ("", to->inValue);
    EXPECT_EQ("", to->outValue);
    EXPECT_EQ(0, to->inCount);
    browser()->route();
    EXPECT_EQ("", from->inValue);
    EXPECT_EQ("foo", from->outValue);
    EXPECT_EQ("foo", to->inValue);
    EXPECT_EQ("", to->outValue);
    EXPECT_EQ(1, to->inCount);
    browser()->reset();
}

TEST_F(RoutingTests, ManuallyRouteOutToInNothingSet) {
    RouteTestNode* from = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* to = browser()->createNode<RouteTestNode>("RouteTestNode");
    from->realize();
    to->realize();
    browser()->createRoute(from, "testOut", to, "testIn");
    browser()->route();
    EXPECT_EQ("", from->inValue);
    EXPECT_EQ("", from->outValue);
    EXPECT_EQ("", to->inValue);
    EXPECT_EQ("", to->outValue);
    EXPECT_EQ(0, to->inCount);
    browser()->reset();
}

TEST_F(RoutingTests, ManuallyRouteFanIn) {
    RouteTestNode* from1 = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* from2 = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* to = browser()->createNode<RouteTestNode>("RouteTestNode");
    from1->realize();
    from2->realize();
    to->realize();
    browser()->createRoute(from1, "testOut", to, "testIn");
    browser()->createRoute(from2, "testOut", to, "testIn");
    EXPECT_EQ("", to->inValue);
    EXPECT_EQ("", to->outValue);
    from1->testOut("foo");
    from2->testOut("foo");
    EXPECT_EQ("", to->inValue);
    EXPECT_EQ("", to->outValue);
    browser()->route();
    EXPECT_EQ("foo", to->inValue);
    EXPECT_EQ("", to->outValue);
    EXPECT_EQ(2, to->inCount);
    browser()->reset();
}

TEST_F(RoutingTests, ManuallyRouteFanInUndeterminedOrder) {
    RouteTestNode* from1 = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* from2 = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* to = browser()->createNode<RouteTestNode>("RouteTestNode");
    from1->realize();
    from2->realize();
    to->realize();
    browser()->createRoute(from1, "testOut", to, "testIn");
    browser()->createRoute(from2, "testOut", to, "testIn");
    EXPECT_EQ("", to->inValue);
    EXPECT_EQ("", to->outValue);
    from1->testOut("foo");
    from2->testOut("bar");
    EXPECT_EQ("", to->inValue);
    EXPECT_EQ("", to->outValue);
    browser()->route();
    EXPECT_THAT(to->inValue, AnyOf(Eq("foo"), Eq("bar")));
    EXPECT_EQ("", to->outValue);
    EXPECT_EQ(2, to->inCount);
    browser()->reset();
}

TEST_F(RoutingTests, ManuallyRouteFanOut) {
    RouteTestNode* from = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* to1 = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* to2 = browser()->createNode<RouteTestNode>("RouteTestNode");
    from->realize();
    to1->realize();
    to2->realize();
    browser()->createRoute(from, "testOut", to1, "testIn");
    browser()->createRoute(from, "testOut", to2, "testIn");
    EXPECT_EQ("", to1->inValue);
    EXPECT_EQ("", to1->outValue);
    EXPECT_EQ("", to2->inValue);
    EXPECT_EQ("", to2->outValue);
    from->testOut("foo");
    EXPECT_EQ("", to1->inValue);
    EXPECT_EQ("", to1->outValue);
    EXPECT_EQ(0, to1->inCount);
    EXPECT_EQ("", to2->inValue);
    EXPECT_EQ("", to2->outValue);
    EXPECT_EQ(0, to2->inCount);
    // additional firings shouldn't do anything
    EXPECT_ANY_THROW(from->testOut("bar"));
    browser()->route();
    EXPECT_EQ("foo", to1->inValue);
    EXPECT_EQ("", to1->outValue);
    EXPECT_EQ(1, to1->inCount);
    EXPECT_EQ("foo", to2->inValue);
    EXPECT_EQ("", to2->outValue);
    EXPECT_EQ(1, to2->inCount);
    browser()->reset();
}

// fanout errors


TEST_F(RoutingTests, ManuallyRouteChainWithInOutField) {
    RouteTestNode* from = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* mid = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* to = browser()->createNode<RouteTestNode>("RouteTestNode");
    from->realize();
    mid->realize();
    to->realize();
    browser()->createRoute(from, "testOut", mid, "set_testInOut");
    browser()->createRoute(mid, "testInOut_changed", to, "testIn");

    from->testOut("foo");
    EXPECT_EQ("foo", from->outValue);
    EXPECT_EQ("", mid->inValue);
    EXPECT_EQ("", mid->outValue);
    EXPECT_EQ("", to->inValue);
    browser()->route();
    EXPECT_EQ("foo", from->outValue);
    EXPECT_EQ("", mid->inValue);
    EXPECT_EQ("", mid->outValue);
    EXPECT_EQ("foo", to->inValue);
    browser()->reset();
}

TEST_F(RoutingTests, ManuallyRouteChainWithCustomInputAction) {
    RouteTestNode* from = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* mid = browser()->createNode<RouteTestNode>("RouteTestNode");
    RouteTestNode* to = browser()->createNode<RouteTestNode>("RouteTestNode");
    from->realize();
    mid->realize();
    to->realize();
    browser()->createRoute(from, "testOut", mid, "customIn");
    browser()->createRoute(mid, "testOut", to, "testIn");

    from->testOut("foo");
    EXPECT_EQ("foo", from->outValue);
    EXPECT_EQ("", mid->inValue);
    EXPECT_EQ("", mid->outValue);
    EXPECT_EQ("", to->inValue);
    browser()->route();
    EXPECT_EQ("foo", from->outValue);
    EXPECT_EQ("", mid->inValue);
    EXPECT_EQ("foofoo", mid->outValue);
    EXPECT_EQ("foofoo", to->inValue);
    browser()->reset();
}

// route from routes any events from a field
// atm, clearing dirty flag of field
// if you had a loop, it would go on infinitely
// should do all routing first, then clear

// two nodes w/ io fields
// route from, to both, each way
// would loop forever
TEST_F(RoutingTests, LoopBreaking) {
    RouteTestNode* node = browser()->createNode<RouteTestNode>("RouteTestNode");
    node->realize();
    browser()->createRoute(node, "countingInOut", node, "countingInOut");

    node->countingInOut("foo");
    browser()->route();

    EXPECT_EQ(2, node->inOutFilterCount);
    EXPECT_EQ(1, node->inOutActionCount);
    browser()->reset();
}
