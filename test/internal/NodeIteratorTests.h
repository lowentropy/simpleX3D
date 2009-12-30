#include "internal/NodeIterator.h"
#include "Core/X3DSensorNode.h"
#include "Time/TimeSensor.h"

TEST(NodeIterator, IteratorShouldWalkThroughMFNode) {
    MFNode<X3DSensorNode> mf;
    TimeSensor t1, t2, t3;
    mf.add(&t1);
    mf.add(&t2);
    mf.add(&t3);
    NodeIterator it = mf.nodes();
    ASSERT_TRUE(it.hasNext()) << "iteration stopped short";
    EXPECT_EQ(&t1, it.next());
    ASSERT_TRUE(it.hasNext()) << "iteration stopped short";
    EXPECT_EQ(&t2, it.next());
    ASSERT_TRUE(it.hasNext()) << "iteration stopped short";
    EXPECT_EQ(&t3, it.next());
    EXPECT_FALSE(it.hasNext()) << "iteration should have stopped";
}
