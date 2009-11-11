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
        ASSERT_EQ(true, it.hasNext());
        EXPECT_EQ(names[i], it.nextFieldDef()->name);
    }
    EXPECT_EQ(false, it.hasNext());
    EXPECT_EQ(NULL, it.nextField());
    EXPECT_EQ(NULL, it.nextFieldDef());
}
