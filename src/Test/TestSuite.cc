/*
 * Copyright 2009 Nathan Matthews <lowentropy@gmail.com>
 *
 * This file is part of SimpleX3D.
 * 
 * SimpleX3D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * SimpleX3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with SimpleX3D.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Test/TestSuite.h"

namespace X3D {
namespace Test {

void TestSuite::setup() {
}

void TestSuite::reset() {
    numPassed(0);
    numFailed(0);
    passed().clear();
    failed().clear();
}

void TestSuite::signal() {
    numPassed.changed();
    numFailed.changed();
    passed.changed();
    failed.changed();
}

void TestSuite::runTests() {
    reset();
    list<TestNode*> tests = this->tests().getElements();
    list<TestNode*>::iterator it;
    for (it = tests.begin(); it != tests.end(); it++) {
        if ((*it)->runTest()) {
            passed().add(*it);
            numPassed.value++;
        } else {
            failed().add(*it);
            numFailed.value++;
        }
    }
    signal();
}

}}
