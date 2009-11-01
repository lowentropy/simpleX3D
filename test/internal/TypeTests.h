#include "Core/WorldInfo.h"

using X3D::Core::WorldInfo;

TEST(TypeSystem, SetupInitFieldHasGetAndSet) {
    WorldInfo* wi = browser()->createNode<WorldInfo>("WorldInfo");
    wi->title = "foo";
    ASSERT_EQ("foo", wi->title());
}

TEST(TypeSystem, SetupInOutFieldHasGetAndSet) {
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
