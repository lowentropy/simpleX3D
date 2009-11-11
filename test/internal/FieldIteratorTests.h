#include "internal/FieldIterator.h"

TEST(FieldIterator, TimeSensorHasAllFields) {
    Node* ts = browser()->createNode("TimeSensor");
    ASSERT_THAT(ts, NotNull());
    FieldIterator it = ts->fields();
    string names[] = {
        "metadata",
        "loop",
        "pauseTime",
        "resumeTime",
        "startTime",
        "stopTime",
        "elapsedTime",
        "isPaused",
        "enabled",
        "isActive",
        "cycleInterval",
        "cycleTime",
        "fraction_changed",
        "time"
    };
    for (int i = 0; i < 14; i++) {
        ASSERT_EQ(true, it.hasNext()) << "too few fields returned";
        EXPECT_EQ(names[i], it.nextFieldDef()->name);
    }
    EXPECT_EQ(false, it.hasNext()) << "too many fields returned";
    EXPECT_EQ(NULL, it.nextField());
    EXPECT_EQ(NULL, it.nextFieldDef());
}

TEST(FieldIterator, TimeSensorHasInputFields) {
    Node* ts = browser()->createNode("TimeSensor");
    ASSERT_THAT(ts, NotNull());
    FieldIterator it = ts->fields(FieldIterator::INPUT);
    string names[] = {
        "metadata",
        "loop",
        "pauseTime",
        "resumeTime",
        "startTime",
        "stopTime",
        "enabled",
        "cycleInterval"
    };
    for (int i = 0; i < 8; i++) {
        ASSERT_EQ(true, it.hasNext()) << "too few fields returned";
        EXPECT_EQ(names[i], it.nextFieldDef()->name);
    }
    EXPECT_EQ(false, it.hasNext()) << "too many fields returned";
    EXPECT_EQ(NULL, it.nextField());
    EXPECT_EQ(NULL, it.nextFieldDef());
}

TEST(FieldIterator, TimeSensorHasDirtyFields) {
    Node* ts = browser()->createNode("TimeSensor");
    ASSERT_THAT(ts, NotNull());
    ts->realize();
    ts->getField("enabled")->set(SFBool(false));   // order of these twp
    ts->getField("loop")->set(SFBool(true));       // is switched.
    ts->getField("cycleInterval")->set(SFTime(1)); // this one is unchanged
    FieldIterator it = ts->fields(FieldIterator::DIRTY);
    ASSERT_EQ(true, it.hasNext()) << "too few fields returned";
    EXPECT_EQ("loop", it.nextFieldDef()->name);
    ASSERT_EQ(true, it.hasNext()) << "too few fields returned";
    EXPECT_EQ("enabled", it.nextFieldDef()->name);
    EXPECT_EQ(false, it.hasNext()) << "too many fields returned";
}
