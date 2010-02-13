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

#ifndef _X3D_TESTNODE_H_
#define _X3D_TESTNODE_H_

#include "Core/X3DChildNode.h"

using X3D::Core::X3DChildNode;

namespace X3D {
namespace Test {

class Expect;

class TestNode : public X3DChildNode {
private:

    list<Expect*> expects;

public:

    DefaultInOutField < TestNode, SFString      > desc;
    DefaultInOutField < TestNode, SFBool        > continuous;
    DefaultInOutField < TestNode, SFTime        > timeout;
    DefaultInOutField < TestNode, SFString      > should;
    DefaultInOutField < TestNode, MFStringArray > failWith;
    DefaultOutField   < TestNode, SFBool        > success;
    DefaultOutField   < TestNode, MFStringArray > reasons;

    class Run : public InField<TestNode, SFBool> {
        void action(bool unused) {
            node()->runTest();
        }
    } run;

    virtual ~TestNode();
    void setup();
    const string& defaultContainerField();
    virtual bool parseSpecial(xmlNode* xml, const string& filename);
    bool runTest();
};

}}

#endif // #ifndef _X3D_TEST_H_
