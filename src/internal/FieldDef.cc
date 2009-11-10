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

#include "internal/NodeDef.h"
#include "internal/FieldDef.h"

#include <iostream>

using std::cout;
using std::endl;

namespace X3D {

FieldDef* NodeDef::getFieldDef(const string& name) {
    if (fields[name] != NULL)
        return fields[name];
    if (set_fields[name] != NULL)
        return set_fields[name];
    if (changed_fields[name] != NULL)
        return changed_fields[name];
    return NULL;
}


void FieldDef::print() {
    switch (access) {
        case X3DField::INIT_ONLY:
            cout << "[]";
            break;
        case X3DField::INPUT_ONLY:
            cout << "[in]";
            break;
        case X3DField::OUTPUT_ONLY:
            cout << "[out]";
            break;
        case X3DField::INPUT_OUTPUT:
            cout << "[in,out]";
            break;
    }
}

}
