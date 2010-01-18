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

#include "internal/Browser.h"
#include "Test/Expect.h"

#include <sstream>
#include <iostream>
using std::cout;
using std::endl;

namespace X3D {
namespace Test {

Expect::Expect(
        TestNode* node, const string& type, const string& name, const string& value,
        double testAt)
            : NodeField<TestNode>(node), name(name), actual(NULL), testAt(testAt) {
    expected = X3DField::create(type);
    std::stringstream ss(value);
    if (!expected->parse(ss))
        throw X3DError(string("invalid field value: ") + value);
}

void Expect::predict() {
    if (testAt >= 0 && node->now() < testAt)
        Browser::getSingleton()->wake(testAt);
}

bool Expect::test(string* reason) {
    std::stringstream ss;
    if (actual == NULL) {
        ss << name << " expected " << *expected << ", but was never activated";
    } else if (*expected != *actual) {
        ss << name << " expected " << *expected << ", but was actually " << *actual;
    } else {
        return true;
    }
    *reason = ss.str();
    return false;
}

Expect::~Expect() {
    if (actual != NULL)
        delete actual;
    delete expected;
}

// unlike in-only, we have a value from the start
const X3DField& Expect::get() const {
    return *expected;
}

X3DField::Type Expect::getType() const {
    return expected->getType();
}

const string& Expect::getTypeName() const {
    return expected->getTypeName();
}

const string& Expect::getName() const {
    return name;
}

SAIField::Access Expect::getAccess() const {
    return SAIField::INPUT_ONLY;
}

// unlike in-only, we have a value from the start
X3DField& Expect::get() {
    return *expected;
}

void Expect::set(const X3DField& value) {
    if (testAt < 0) {
        if (actual == NULL)
            actual = X3DField::create(value.getType());
        (*actual)(value);
    } else if (actual == NULL && node->now() >= testAt) {
        actual = X3DField::create(value.getType());
        (*actual)(value);
    }
}

X3DField& Expect::getSilently() {
    return *expected;
}

// XXX setSilently is only called because of cloning,
// so copy the EXPECTED value, not the ACTUAL. this should
// really be explicit by way of overloading copyInto (?)
void Expect::setSilently(const X3DField& value) {
    *expected = value;
}

bool Expect::isDirty() const {
    return false;
}

void Expect::clearDirty() {
}

void Expect::addIncomingRoute(Route* route) {
    routes.push_back(route);
}
void Expect::removeIncomingRoute(Route* route) {
    routes.remove(route);
}
const list<Route*>& Expect::getIncomingRoutes() const {
    return routes;
}

}}
