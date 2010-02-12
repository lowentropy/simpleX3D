#include <sstream>
#include "internal/SFVec.h"

using std::stringstream;

TEST(ParseTests, IntParseShouldSucceedOnGoodString) {
    SFInt32 x;
    stringstream ss("216\t");
    EXPECT_EQ(true, x.parse(ss));
    EXPECT_EQ(216, x());
    browser()->reset();
}

TEST(ParseTests, IntParseShouldSucceedOnNegativeString) {
    SFInt32 x;
    stringstream ss(" -216");
    EXPECT_EQ(true, x.parse(ss));
    EXPECT_EQ(-216, x());
    browser()->reset();
}

TEST(ParseTests, IntShouldFailOnEmptyString) {
    SFInt32 x;
    stringstream ss("");
    EXPECT_EQ(false, x.parse(ss));
    browser()->reset();
}

TEST(ParseTests, IntShouldFailOnBadString) {
    SFInt32 x;
    stringstream ss("foo");
    EXPECT_EQ(false, x.parse(ss));
    browser()->reset();
}

TEST(ParseTests, VecShouldSucceedOnIntString) {
    SFVec3d v;
    stringstream ss("1 2 3");
    EXPECT_EQ(true, v.parse(ss));
    EXPECT_EQ(SFVec3d(1,2,3), v);
    browser()->reset();
}

TEST(ParseTests, VecShouldSucceedOnFloatString) {
    SFVec4f v;
    stringstream ss("1.23 \t 2e3 -3.0123123\n\n\n\n\n-0");
    EXPECT_EQ(true, v.parse(ss));
    EXPECT_EQ(SFVec4f(1.23,2e3,-3.0123123,0.0), v);
    browser()->reset();
}

TEST(ParseTests, VecShouldFailWithCommas) {
    SFVec3f v;
    stringstream ss("1, 2, 3");
    EXPECT_EQ(false, v.parse(ss));
    browser()->reset();
}

TEST(ParseTests, VecShouldFailWithTooFewArguments) {
    SFVec3f v;
    stringstream ss("1 2");
    EXPECT_EQ(false, v.parse(ss));
    browser()->reset();
}

TEST(ParseTests, VecShouldFailWithNonNumberArguments) {
    SFVec2f v;
    stringstream ss("foo 33.3");
    EXPECT_EQ(false, v.parse(ss));
    browser()->reset();
}

TEST(ParseTests, Matrix3ShouldSucceedInGeneralCase) {
    SFMatrix3d m;
    stringstream ss("1 2 3 \n\t4.0 -3.561 1234\n\n-512 123\n3e-12");
    double arr[] = {1, 2, 3, 4, -3.561, 1234, -512, 123, 3e-12};
    EXPECT_EQ(true, m.parse(ss));
    EXPECT_EQ(SFMatrix3d(arr), m);
    browser()->reset();
}

TEST(ParseTests, Matrix4ShouldSucceedInGeneralCase) {
    SFMatrix4d m;
    stringstream ss("1 2 3 124111\n\t4.0 -3.561 1234 -0\n\n-512 123\n3e-12\t2 1 2 3 4");
    double arr[] = {1, 2, 3, 124111, 4, -3.561, 1234, 0, -512, 123, 3e-12, 2.0, 1, 2, 3, 4};
    EXPECT_EQ(true, m.parse(ss));
    EXPECT_EQ(SFMatrix4d(arr), m);
    browser()->reset();
}

TEST(ParseTests, FloatShouldSuceedOnIntegerString) {
    SFFloat f;
    stringstream ss("-216");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(-216, f());
    browser()->reset();
}

TEST(ParseTests, FloatShouldSuceedOnComplexFloatString) {
    SFFloat f;
    stringstream ss("-123.456e-42");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(-123.456e-42, f());
    browser()->reset();
}

TEST(ParseTests, FloatShouldSucceedWithExtraZeros) {
    SFFloat f;
    stringstream ss("00123.456000");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(123.456, f());
    browser()->reset();
}

// XXX this should really fail, but that would require peeking at
// the next character to make sure it's whitespace or eof, which isn't
// fun to do in the value parser. it would be okay to add in the field
// parser, however, and MFs should obey this rule automatically
/*
TEST(ParseTests, FloatShouldFailOnNonNumber) {
    SFFloat f;
    stringstream ss("1.23f5");
    EXPECT_EQ(false, f.parse(ss));
}
*/

TEST(ParseTests, FloatShouldFailWithUnmixedNonNumber) {
    SFFloat f;
    stringstream ss("f123");
    EXPECT_EQ(false, f.parse(ss));
    browser()->reset();
}

TEST(ParseTests, DoubleShouldSuceedOnIntegerString) {
    SFDouble f;
    stringstream ss("-216");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(-216, f());
    browser()->reset();
}

TEST(ParseTests, DoubleShouldSuceedOnComplexDoubleString) {
    SFDouble f;
    stringstream ss("-123.456e-42");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(-123.456e-42, f());
    browser()->reset();
}

TEST(ParseTests, DoubleShouldSucceedWithExtraZeros) {
    SFDouble f;
    stringstream ss("00123.456000");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(123.456, f());
    browser()->reset();
}

// XXX this should really fail, but that would require peeking at
// the next character to make sure it's whitespace or eof, which isn't
// fun to do in the value parser. it would be okay to add in the field
// parser, however, and MFs should obey this rule automatically
/*
TEST(ParseTests, DoubleShouldFailOnNonNumber) {
    SFDouble f;
    stringstream ss("1.23f5");
    EXPECT_EQ(false, f.parse(ss));
}
*/

TEST(ParseTests, DoubleShouldFailWithUnmixedNonNumber) {
    SFDouble f;
    stringstream ss("f123");
    EXPECT_EQ(false, f.parse(ss));
    browser()->reset();
}

TEST(ParseTests, BoolShouldSucceedWithLowercase) {
    SFBool b;
    stringstream strue("true");
    EXPECT_EQ(true, b.parse(strue));
    EXPECT_EQ(true, b());
    stringstream sfalse("false");
    EXPECT_EQ(true, b.parse(sfalse));
    EXPECT_EQ(false, b());
    browser()->reset();
}

TEST(ParseTests, BoolShouldFailWithMixedCase) {
    SFBool b;
    stringstream strue("TRuE");
    EXPECT_EQ(false, b.parse(strue));
    stringstream sfalse("fAlSe");
    EXPECT_EQ(false, b.parse(sfalse));
    browser()->reset();
}

TEST(ParseTests, TimeShouldParseAnywayBecauseItsJustADouble) {
    SFTime t;
    stringstream ss("123.456");
    EXPECT_EQ(true, t.parse(ss));
    EXPECT_FLOAT_EQ(123.456, t());
    browser()->reset();
}

TEST(ParseTests, ColorShouldSucceedIfInBounds) {
    SFColor c;
    stringstream ss("0.3 0.4 1");
    EXPECT_EQ(true, c.parse(ss));
    EXPECT_EQ(SFColor(0.3,0.4,1), c);
    browser()->reset();
}

TEST(ParseTests, ColorShouldFailIfOutOfBounds) {
    SFColor c;
    stringstream ss("0.3 0.4 1.1");
    EXPECT_EQ(false, c.parse(ss));
    browser()->reset();
}

TEST(ParseTests, ColorRGBAShouldSucceedIfInBounds) {
    SFColorRGBA c;
    stringstream ss("0.3 0.4 0 1");
    EXPECT_EQ(true, c.parse(ss));
    EXPECT_EQ(SFColorRGBA(0.3,0.4,0,1), c);
    browser()->reset();
}

TEST(ParseTests, ColorRGBAShouldFailIfOutOfBounds) {
    SFColorRGBA c;
    stringstream ss("0.3 0.4 0.2 -0.5");
    EXPECT_EQ(false, c.parse(ss));
    browser()->reset();
}

TEST(ParseTests, RotationShouldSucceedInGeneralCase) {
    SFRotation r;
    stringstream ss("1 2 3 4");
    EXPECT_EQ(true, r.parse(ss));
    EXPECT_EQ(SFRotation(1,2,3,4), r);
    browser()->reset();
}

TEST(ParseTests, StringShouldSuceedIfWellFormed) {
    SFString s;
    stringstream ss("\t\"foo adsgk ads' adsf \n\t\"  ");
    EXPECT_EQ(true, s.parse(ss));
    ss >> std::ws;
    EXPECT_EQ(true, ss.eof());
    EXPECT_EQ("foo adsgk ads' adsf \n\t", s());
    browser()->reset();
}

TEST(ParseTests, StringShouldFailIfMissingLeadingQuote) {
    SFString s;
    stringstream ss("adf asd\"");
    EXPECT_EQ(false, s.parse(ss));
    browser()->reset();
}

TEST(ParseTests, StringShouldFailIfMissingTrailingQuote) {
    SFString s("foo");
    stringstream ss("\"asdlkfads");
    EXPECT_EQ(false, s.parse(ss));
    EXPECT_EQ("foo", s());
    browser()->reset();
}

TEST(ParseTests, NodeShouldSucceedWithNullValue) {
    TimeSensor* ts = new TimeSensor();
    SFNode<TimeSensor> n(ts);
    stringstream ss("NULL");
    EXPECT_EQ(true, n.parse(ss));
    EXPECT_EQ(NULL, n());
    delete ts;
    browser()->reset();
}

TEST(ParseTests, NodeShouldSucceedWithNamedNode) {
    Node* node = browser()->createNode("TimeSensor");
    browser()->addNamedNode("parse_tests_foo", node);
    SFNode<TimeSensor> n;
    stringstream ss("parse_tests_foo");
    EXPECT_EQ(true, n.parse(ss));
    EXPECT_EQ(node, n());
    browser()->reset();
}

TEST(ParseTests, NodeShouldFailWithUnknwonNode) {
    SFNode<TimeSensor> n;
    stringstream ss("googlyfoozit");
    EXPECT_ANY_THROW(n.parse(ss));
    browser()->reset();
}

TEST(ParseTests, NodeShouldFailWithWrongNodeType) {
    Node* node = browser()->createNode("WorldInfo");
    browser()->addNamedNode("parse_tests_bar", node);
    SFNode<TimeSensor> n;
    stringstream ss("parse_tests_bar");
    EXPECT_ANY_THROW(n.parse(ss));
    browser()->reset();
}

TEST(ParseTests, ImageShouldSucceedWithMixedDecimalModes) {
    SFImage img(0,0,0);
    stringstream ss("2 2 1 216 0xa3 11 0");
    EXPECT_EQ(true, img.parse(ss));
    EXPECT_EQ(2, img.getWidth());
    EXPECT_EQ(2, img.getHeight());
    EXPECT_EQ(1, img.getComponents());
    EXPECT_EQ(216, img.array()[0]);
    EXPECT_EQ(0xa3, img.array()[1]);
    EXPECT_EQ(11, img.array()[2]);
    EXPECT_EQ(0, img.array()[3]);
    browser()->reset();
}

TEST(ParseTests, ImageShouldSucceedWithMultipleChannels) {
    SFImage img(0,0,0);
    stringstream ss("1 1 2 0x1234");
    EXPECT_EQ(true, img.parse(ss));
    EXPECT_EQ(1, img.getWidth());
    EXPECT_EQ(1, img.getHeight());
    EXPECT_EQ(2, img.getComponents());
    EXPECT_EQ(0x12, img.array()[0]);
    EXPECT_EQ(0x34, img.array()[1]);
    browser()->reset();
}

TEST(ParseTests, ImageShouldFailWithNotEnoughPixels) {
    SFImage img(0,0,0);
    stringstream ss("2 2 1 216 0xa3 11");
    EXPECT_EQ(false, img.parse(ss));
    browser()->reset();
}

TEST(ParseTests, ImageShouldFailIfPixelOutOfBounds) {
    SFImage img(0,0,0);
    stringstream ss("2 2 1 216 0xa3 1111");
    EXPECT_EQ(false, img.parse(ss));
    browser()->reset();
}

TEST(ParseTests, MFVecShouldSucceedInGeneralCase) {
    MFVec3fArray mf;
    stringstream ss("1 2 3  \n, 4 5 6, 7 8 9 , ");
    EXPECT_EQ(true, mf.parse(ss));
    EXPECT_EQ(3, mf.size());
    MFVec3f::iterator it;
    int i = 1;
    for (it = mf.begin(); it != mf.end(); it++) {
        if (i > 9)
            break;
        EXPECT_FLOAT_EQ((float) i++, it->x);
        EXPECT_FLOAT_EQ((float) i++, it->y);
        EXPECT_FLOAT_EQ((float) i++, it->z);
    }
    EXPECT_TRUE(mf.end() == it);
    browser()->reset();
}

TEST(ParseTests, MFVecShouldFailOnLeadingComma) {
    MFVec3fArray mf;
    stringstream ss(",1 2 3  \n, 4 5 6, 7 8 9 , ");
    EXPECT_EQ(false, mf.parse(ss));
    browser()->reset();
}
