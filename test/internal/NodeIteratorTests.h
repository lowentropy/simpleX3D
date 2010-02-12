#include "Core/X3DSensorNode.h"
#include "Time/TimeSensor.h"

TEST(NodeIterator, IteratorShouldWalkThroughMFNode) {
    MFNodeArray<X3DSensorNode> mf;
    TimeSensor t1, t2, t3;
    mf.add(&t1);
    mf.add(&t2);
    mf.add(&t3);
    MFNode<X3DSensorNode>::iterator it = mf.begin();
    EXPECT_EQ(&t1, *it++);
    EXPECT_EQ(&t2, *it++);
    EXPECT_EQ(&t3, *it++);
    EXPECT_TRUE(mf.end() == it);
}
