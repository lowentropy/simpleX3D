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

#ifndef _X3D_EXPECT_H_
#define _X3D_EXPECT_H_

#include "internal/Route.h"
#include "Test/TestNode.h"

namespace X3D {
namespace Test {

class Expect : public NodeField<TestNode> {
private:

    X3DField* expected;
    const X3DField* actual;
    list<Route*> routes;

public:

    const string name;

    Expect(TestNode* node, const string& type, const string& name, const string& value);
    virtual ~Expect();
    SAIField::Access getAccess() const;
    const X3DField& get() const;
    X3DField& get();
    void set(const X3DField& value);
    X3DField& getSilently();
    void setSilently(const X3DField& value);
    X3DField::Type getType() const;
    const string& getTypeName() const;
    bool isDirty() const;
    void clearDirty();
    void addIncomingRoute(Route* route);
    void removeIncomingRoute(Route* route);
    const list<Route*>& getIncomingRoutes() const;
    bool test(string* reason);

};

}}

#endif // #ifndef _X3D_EXPECT_H_
