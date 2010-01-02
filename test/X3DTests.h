void runX3DTest(const char* filename) {

    // load the world
    World* world = World::read(browser(), filename);

    // get the test suite
    TestSuite* suite = browser()->getFirst<TestSuite>(); // ("TestSuite");
    ASSERT_THAT(suite, NotNull());

    // run the tests
    suite->realize(); // TODO: root nodes should be realized automatically...
    suite->runTests();

    // print the failed tests' failure reasons
    list<TestNode*>& failed = suite->failed().getElements();
    list<TestNode*>::iterator it;
    for (it = failed.begin(); it != failed.end(); it++) {
        TestNode* test = *it;
        cout << "FAILED: " << test->getName();
        if (!test->desc().empty())
            cout << ": '" << test->desc() << "'";
        cout << endl;
        list<string>& reasons = test->reasons().getElements();
        list<string>::iterator r_it;
        for (r_it = reasons.begin(); r_it != reasons.end(); r_it++)
            cout << '\t' << *r_it << endl;
    }

    // check correct num passed/failed
    if (suite->numFailed() > 0)
        FAIL() << "Tests for '" << suite->desc() << "' failed";
    else
        SUCCEED();

    // clean up
    browser()->reset();
    delete world;
}
