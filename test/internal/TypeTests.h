#include "Core/WorldInfo.h"
#include "Time/TimeSensor.h"

using X3D::Core::WorldInfo;
using X3D::Time::TimeSensor;

TEST(TypeSystem, SetupInitFieldHasGetAndSet) {
    WorldInfo* wi = browser()->createNode<WorldInfo>("WorldInfo");
    ASSERT_EQ("", wi->title());
    wi->title("foo");
    ASSERT_EQ("foo", wi->title());
}

TEST(TypeSystem, SetupInOutFieldHasGetAndSet) {
    TimeSensor* ts = browser()->createNode<TimeSensor>("TimeSensor");
    ASSERT_EQ(1.0, ts->cycleInterval());
    ts->cycleInterval(5);
    ASSERT_EQ(5.0, ts->cycleInterval());
    // This is commented because
    //   1) not all SF... wrappers have == and != methods yet
    //   2) none of them have the << operator, so the assertions
    //      won't actually compile
//  SFTime time(5);
//  ASSERT_EQ(time, ts->cycleInterval.get());
}

TEST(TypeSystem, RealizedOutputFieldHasGet) {
    TimeSensor* ts = browser()->createNode<TimeSensor>("TimeSensor");
    ts->realize();
    ASSERT_EQ(0.0, ts->time());
}

TEST(TypeSystem, RealizedInOutFieldHasGetAndSet) {
    TimeSensor* ts = browser()->createNode<TimeSensor>("TimeSensor");
    ts->realize();
    ASSERT_EQ(1.0, ts->cycleInterval());
    ts->cycleInterval(5);
    ASSERT_EQ(5.0, ts->cycleInterval());
}

class InFieldNode : public Node {
public:
    class TestField : public InField<InFieldNode, SFString> {
        void action(const string& str) {
            ASSERT_EQ("foo", str);
        }
    } testField;
};

TEST(TypeSystem, RealizedInputFieldCallsAction) {
    InFieldNode* node = new InFieldNode();
    node->testField.setNode(node);
    ASSERT_ANY_THROW(node->testField("foo"));
    node->realize();
    node->testField("foo");
}

class InOutNode : public Node {
public:
    class TestField : public InOutField<InOutNode, SFInt32> {
        bool filter(int value) {
            EXPECT_EQ(true, node()->realized());
            return value > 3;
        }
        void action() {
        }
    } testField;
};

TEST(TypeSystem, RealizedInputOutputFieldCallsFilter) {
    InOutNode* node = new InOutNode();
    node->testField.setNode(node);
    node->testField(-3);
    node->realize();
    ASSERT_EQ(-3, node->testField());
    node->testField(5);
    ASSERT_EQ(5, node->testField());
    ASSERT_EQ(true, node->testField.isDirty()) << "filter should have returned true, marking field dirty";
    node->testField(2);
    ASSERT_EQ(5, node->testField()) << "filter should have returned false, so value should be unchanged";
}

// TODO: tests of dynamic field lookup and access
//      (like this)  Node* node = browser()->createNode("NodeName");

// TODO: access at bad times should lead to errors
/*
TEST(TypeSystem, SetupInputFieldShouldNotGet) {
    InFieldNode* node = new InFieldNode();
    node->testField.setNode(node);
    ASSERT_ANY_THROW(node->testField());
}
*/
TEST(TypeSystem, UnrealizedInputFieldShouldNotSet) {
    InFieldNode* node = new InFieldNode();
    ASSERT_ANY_THROW(node->testField("foo"));
}
/*
TEST(TypeSystem, UnrealizedOutputFieldShouldNotGet) {
    OutFieldNode* node = new OutFieldNode();
    ASSERT_ANY_THROW(node->testField());
}
*/
/*
TEST(TypeSystem, UnrealizedOutputFieldShouldNotSet) {
    OutFieldNode* node = new OutFieldNode();
    ASSERT_ANY_THROW(node->testField("foo"));
}
*/
/*
TEST(TypeSystem, RealizedInitFieldShouldNotGet) {
    InitFieldNode* node = new InitFieldNode();
    node->realize();
    ASSERT_ANY_THROW(node->testField());
}
*/
/*
TEST(TypeSystem, RealizedInitFieldShouldNotSet) {
    InitFieldNode* node = new InitFieldNode();
    node->realize();
    ASSERT_ANY_THROW(node->testField("foo"));
}
*/
/*
TEST(TypeSystem, RealizedInputFieldShouldNotGet) {
    InFieldNode* node = new InFieldNode();
    node->realize();
    ASSERT_ANY_THROW(node->testField());
}
*/
