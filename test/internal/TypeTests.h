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
}

TEST(TypeSystem, RealizedInOutFieldHasGetAndSet) {
}

TEST(TypeSystem, RealizedInputFieldCallsAction) {
}

TEST(TypeSystem, RealizedInputOutputFieldCallsFilter) {
    // making sure to test that if filter is false, the
    // value of the field is unchanged
}

// TODO: tests of dynamic field lookup and access
//      (like this)  Node* node = browser()->createNode("NodeName");
