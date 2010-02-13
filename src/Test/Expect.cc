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
        TestNode* node, const string& field, const string& value, double time)
            : NodeField<TestNode>(node), field(field), actual(NULL), time(time) {
    Browser* browser = Browser::getSingleton();
    size_t splitPos = field.find('.');
    if (splitPos == string::npos)
        throw X3DError("invalid node.field identifier");
    string nodeName = field.substr(0, splitPos);
    string fieldName = field.substr(splitPos+1, field.size()-splitPos-1);
    Node* from = browser->getNode(nodeName);
    if (from == NULL)
        throw X3DError(string("source node not found: ") + nodeName);
    SAIField* fromField = from->getField(fieldName);
    if (fromField == NULL)
        throw X3DError(string("source field not found: ") + fieldName);
    expected = X3DField::create(fromField->getType());
    std::stringstream ss(value);
    if (!expected->parse(ss))
        throw X3DError(string("invalid field value: ") + value);
    browser->createRoute(fromField, this);
}

void Expect::predict() {
    Browser::getSingleton()->wake(time);
}

bool Expect::test(string* reason) {
    std::stringstream ss;
    if (actual == NULL) {
        ss << field << " should be " << *expected << ", but was never activated";
    } else if (!expected->equals(*actual)) {
        ss << field << " should be " << *expected << ", but was actually " << *actual;
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
    throw X3DError("Abstract");
}

SAIField::Access Expect::getAccess() const {
    return SAIField::INPUT_ONLY;
}

// unlike in-only, we have a value from the start
X3DField& Expect::get() {
    return *expected;
}

void Expect::set(const X3DField& value) {
    if (actual == NULL && node->now() >= time) {
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
