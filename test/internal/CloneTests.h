#include "Test/TestSuite.h"
#include "Test/TestNode.h"

using namespace X3D::Test;

TEST(Cloning, ShouldCloneComplexTree) {
    // set up the source structure
    TestSuite* suite = browser()->createNode<TestSuite>("TestSuite");
    suite->name("Root");
    TestNode* test1 = browser()->createNode<TestNode>("Test");
    TestNode* test2 = browser()->createNode<TestNode>("Test");
    suite->tests().add(test1);
    suite->tests().add(test2);
    test1->setName("Test1");
    test2->setName("Test2");
    test1->continuous(true);
    test2->continuous(false);
    test1->timeout(216);
    test2->timeout(666);

    // clone and map the structure
    map<Node*,Node*> mapping;
    TestSuite* clone = browser()->createNode<TestSuite>("TestSuite");
    suite->cloneInto(clone, &mapping, false);

    // test the clone
    EXPECT_EQ("Root", clone->name());
    list<TestNode*>& tests = clone->tests().getElements();
    EXPECT_EQ(2, tests.size());
    list<TestNode*>::iterator it = tests.begin();
    
    TestNode* test = *it++;
    EXPECT_EQ("Test1", test->getName());
    EXPECT_EQ(true, test->continuous());
    EXPECT_EQ(216, test->timeout());

    test = *it++;
    EXPECT_EQ("Test2", test->getName());
    EXPECT_EQ(false, test->continuous());
    EXPECT_EQ(666, test->timeout());
}
