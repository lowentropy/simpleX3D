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

#ifndef _X3D_TEST_H_
#define _X3D_TEST_H_

#include <Core/X3DChildNode.h>

using X3D::Core::X3DChildNode;

namespace X3D {
namespace Time {

class Test : public X3DChildNode {
public:

    InitField<Test, SFString> name;
    InitField<Test, SFString> eventMode;
    InitField<Test, SFTime> timeout;

    class Run : public InField<Test, SFBool> {
        void action(bool unused) {
            // TODO
        }
    } run;

    const string& defaultContainerField() {
        static string field = "tests";
        return field;
    }

    void setup() {
        eventMode("discrete");
        timeout(0);
    }
};

}}

#endif // #ifndef _X3D_TEST_H_
