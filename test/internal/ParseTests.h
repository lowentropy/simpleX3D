#include <sstream>
#include "internal/SFVec.h"

using std::stringstream;

TEST(ParseTests, IntParseShouldSucceedOnGoodString) {
    SFInt32 x;
    stringstream ss("216\t");
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

TEST(ParseTests, VecShouldSucceedOnIntString) {
    SFVec3d v;
    stringstream ss("1 2 3");
    EXPECT_EQ(true, v.parse(ss));
    SFVec3d w(1,2,3);
    EXPECT_EQ(true, w == v);
}

TEST(ParseTests, VecShouldSucceedOnFloatString) {
    SFVec4f v;
    stringstream ss("1.23 \t 2e3 -3.0123123\n\n\n\n\n-0");
    EXPECT_EQ(true, v.parse(ss));
    SFVec4f w(1.23,2e3,-3.0123123,0.0);
    EXPECT_EQ(true, w == v);
}

TEST(ParseTests, VecShouldFailWithCommas) {
    SFVec3f v;
    stringstream ss("1, 2, 3");
    EXPECT_EQ(false, v.parse(ss));
}

TEST(ParseTests, VecShouldFailWithTooFewArguments) {
    SFVec3f v;
    stringstream ss("1 2");
    EXPECT_EQ(false, v.parse(ss));
}

TEST(ParseTests, VecShouldFailWithNonNumberArguments) {
    SFVec2f v;
    stringstream ss("foo 33.3");
    EXPECT_EQ(false, v.parse(ss));
}

TEST(ParseTests, Matrix3ShouldSucceedInGeneralCase) {
    SFMatrix3d m;
    stringstream ss("1 2 3 \n\t4.0 -3.561 1234\n\n-512 123\n3e-12");
    double arr[] = {1, 2, 3, 4, -3.561, 1234, -512, 123, 3e-12};
    SFMatrix3d e(arr);
    EXPECT_EQ(true, m.parse(ss));
    EXPECT_EQ(true, e == m);
}

TEST(ParseTests, Matrix4ShouldSucceedInGeneralCase) {
    SFMatrix4d m;
    stringstream ss("1 2 3 124111\n\t4.0 -3.561 1234 -0\n\n-512 123\n3e-12\t2 1 2 3 4");
    double arr[] = {1, 2, 3, 124111, 4, -3.561, 1234, 0, -512, 123, 3e-12, 2.0, 1, 2, 3, 4};
    SFMatrix4d e(arr);
    EXPECT_EQ(true, m.parse(ss));
    EXPECT_EQ(true, e == m);
}

TEST(ParseTests, FloatShouldSuceedOnIntegerString) {
    SFFloat f;
    stringstream ss("-216");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(-216, f());
}

TEST(ParseTests, FloatShouldSuceedOnComplexFloatString) {
    SFFloat f;
    stringstream ss("-123.456e-42");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(-123.456e-42, f());
}

TEST(ParseTests, FloatShouldSucceedWithExtraZeros) {
    SFFloat f;
    stringstream ss("00123.456000");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(123.456, f());
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
}

TEST(ParseTests, DoubleShouldSuceedOnIntegerString) {
    SFDouble f;
    stringstream ss("-216");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(-216, f());
}

TEST(ParseTests, DoubleShouldSuceedOnComplexDoubleString) {
    SFDouble f;
    stringstream ss("-123.456e-42");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(-123.456e-42, f());
}

TEST(ParseTests, DoubleShouldSucceedWithExtraZeros) {
    SFDouble f;
    stringstream ss("00123.456000");
    EXPECT_EQ(true, f.parse(ss));
    EXPECT_FLOAT_EQ(123.456, f());
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
}

TEST(ParseTests, BoolShouldSucceedWithLowercase) {
    SFBool b;
    stringstream strue("true");
    EXPECT_EQ(true, b.parse(strue));
    EXPECT_EQ(true, b());
    stringstream sfalse("false");
    EXPECT_EQ(true, b.parse(sfalse));
    EXPECT_EQ(false, b());
}

TEST(ParseTests, BoolShouldFailWithMixedCase) {
    SFBool b;
    stringstream strue("TRuE");
    EXPECT_EQ(false, b.parse(strue));
    stringstream sfalse("fAlSe");
    EXPECT_EQ(false, b.parse(sfalse));
}

TEST(ParseTests, TimeShouldParseAnywayBecauseItsJustADouble) {
    SFTime t;
    stringstream ss("123.456");
    EXPECT_EQ(true, t.parse(ss));
    EXPECT_FLOAT_EQ(123.456, t());
}

TEST(ParseTests, ColorShouldSucceedIfInBounds) {
    SFColor c;
    stringstream ss("0.3 0.4 1");
    EXPECT_EQ(true, c.parse(ss));
    EXPECT_FLOAT_EQ(0.3, c.r);
    EXPECT_FLOAT_EQ(0.4, c.g);
    EXPECT_FLOAT_EQ(1.0, c.b);
}

TEST(ParseTests, ColorShouldFailIfOutOfBounds) {
    SFColor c;
    stringstream ss("0.3 0.4 1.1");
    EXPECT_EQ(false, c.parse(ss));
}

TEST(ParseTests, ColorRGBAShouldSucceedIfInBounds) {
    SFColorRGBA c;
    stringstream ss("0.3 0.4 0 1");
    EXPECT_EQ(true, c.parse(ss));
    EXPECT_FLOAT_EQ(0.3, c.r);
    EXPECT_FLOAT_EQ(0.4, c.g);
    EXPECT_FLOAT_EQ(0.0, c.b);
    EXPECT_FLOAT_EQ(1.0, c.a);
}

TEST(ParseTests, ColorRGBAShouldFailIfOutOfBounds) {
    SFColorRGBA c;
    stringstream ss("0.3 0.4 0.2 -0.5");
    EXPECT_EQ(false, c.parse(ss));
}

TEST(ParseTests, RotationShouldSucceedInGeneralCase) {
    SFRotation r;
    stringstream ss("1 2 3 4");
    EXPECT_EQ(true, r.parse(ss));
    EXPECT_FLOAT_EQ(1, r.x);
    EXPECT_FLOAT_EQ(2, r.y);
    EXPECT_FLOAT_EQ(3, r.z);
    EXPECT_FLOAT_EQ(4, r.a);
}

TEST(ParseTests, StringShouldSuceedIfWellFormed) {
    SFString s;
    stringstream ss("\t\"foo adsgk ads' adsf \n\t\"  ");
    EXPECT_EQ(true, s.parse(ss));
    ss >> std::ws;
    EXPECT_EQ(true, ss.eof());
    EXPECT_EQ("foo adsgk ads' adsf \n\t", s());
}

TEST(ParseTests, StringShouldFailIfMissingLeadingQuote) {
    SFString s;
    stringstream ss("adf asd\"");
    EXPECT_EQ(false, s.parse(ss));
}

TEST(ParseTests, StringShouldFailIfMissingTrailingQuote) {
    SFString s("foo");
    stringstream ss("\"asdlkfads");
    EXPECT_EQ(false, s.parse(ss));
    EXPECT_EQ("foo", s());
}

TEST(ParseTests, NodeShouldSucceedWithNullValue) {
    TimeSensor* ts = new TimeSensor();
    SFNode<TimeSensor> n(ts);
    stringstream ss("NULL");
    EXPECT_EQ(true, n.parse(ss));
    EXPECT_EQ(NULL, n());
}

TEST(ParseTests, NodeShouldSucceedWithNamedNode) {
    Node* node = browser()->createNode("TimeSensor");
    browser()->addNamedNode("parse_tests_foo", node);
    SFNode<TimeSensor> n;
    stringstream ss("parse_tests_foo");
    EXPECT_EQ(true, n.parse(ss));
    EXPECT_EQ(node, n());
}

TEST(ParseTests, NodeShouldFailWithUnknwonNode) {
    SFNode<TimeSensor> n;
    stringstream ss("googlyfoozit");
    EXPECT_ANY_THROW(n.parse(ss));
}

TEST(ParseTests, NodeShouldFailWithWrongNodeType) {
    Node* node = browser()->createNode("WorldInfo");
    browser()->addNamedNode("parse_tests_bar", node);
    SFNode<TimeSensor> n;
    stringstream ss("parse_tests_bar");
    EXPECT_ANY_THROW(n.parse(ss));
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
}

TEST(ParseTests, ImageShouldFailWithNotEnoughPixels) {
    SFImage img(0,0,0);
    stringstream ss("2 2 1 216 0xa3 11");
    EXPECT_EQ(false, img.parse(ss));
}

TEST(ParseTests, ImageShouldFailIfPixelOutOfBounds) {
    SFImage img(0,0,0);
    stringstream ss("2 2 1 216 0xa3 1111");
    EXPECT_EQ(false, img.parse(ss));
}
