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
#include "internal/Route.h"

#include <iostream>
#include <sstream>
using std::ostringstream;
using std::cout;
using std::endl;

namespace X3D {

void Route::checkTypes() {
    FieldDef* def = toField->definition;
    if (fromField->getType() != toField->getType()) {
        ostringstream os;
        os << "route field type mismatch (" <<
                   "source=" << fromField->getTypeName() << ", " <<
                   "target=" << toField->getTypeName() << ")";
        throw X3DError(os.str());
    }
}

void Route::activate() const {
    if (!fromField->isDirty())
        return;
    const X3DField& value = fromField->get();
    // logEvent(value);
    toField->set(value);
}

void Route::logEvent(const X3DField& value) const {
    Node* node = fromField->getNode();
    const string& name1 = node->getName();
    cout << "[" << node->definition->name << "] ";
    cout << (name1.empty() ? "noname" : name1);
    cout << "." << fromField->getName() << " --(";
    cout << value << ")--> ";
    node = toField->getNode();
    const string& name2 = node->getName();
    cout << (name2.empty() ? "noname" : name2);
    cout << "." << toField->getName() << " [";
    cout << node->definition->name << "]" << endl;
}

void Route::remove() {
    fromField->removeOutgoingRoute(this);
    toField->removeIncomingRoute(this);
}

void Route::insert() {
    const list<Route*>& outs = fromField->getOutgoingRoutes();
    list<Route*>::const_iterator it;
    for (it = outs.begin(); it != outs.end(); it++) {
        if ((*it)->toField == toField)
            throw X3DError("another identical route exists");
    }
    fromField->getNode()->realize();
    toField->getNode()->realize();
    fromField->addOutgoingRoute(this);
    toField->addIncomingRoute(this);
}

}
