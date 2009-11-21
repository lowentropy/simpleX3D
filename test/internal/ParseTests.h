#include <sstream>
#include "internal/SFVec.h"

using std::stringstream;

TEST(ParseTests, IntParseShouldSucceedOnGoodString) {
    SFInt32 x;
    stringstream ss("216");
    EXPECT_EQ(true, x.parse(ss));
    EXPECT_EQ(216, x());
}

TEST(ParseTests, IntParseShouldSucceedOnNegativeString) {
    SFInt32 x;
    stringstream ss(" -216");
    EXPECT_EQ(true, x.parse(ss));
    EXPECT_EQ(-216, x());
}

TEST(ParseTests, IntShouldFailOnEmptyString) {
    SFInt32 x;
    stringstream ss("");
    EXPECT_EQ(false, x.parse(ss));
}

TEST(ParseTests, IntShouldFailOnBadString) {
    SFInt32 x;
    stringstream ss("foo");
    EXPECT_EQ(false, x.parse(ss));
}

TEST(ParseTests, VecShouldSucceedOnGoodString) {
    SFVec3d v;
    stringstream ss("1 2 3");
    EXPECT_EQ(true, v.parse(ss));
    SFVec3d w(1,2,3);
    EXPECT_EQ(true, w == v);
}
