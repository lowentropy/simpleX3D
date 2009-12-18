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

#include "internal/SAIField.h"

namespace X3D {

const string& SAIField::getName() const {
    return definition->name;
}

void SAIField::addIncomingRoute(Route* route) {
    throw X3DError("this field does not support incoming routes");
}

void SAIField::removeIncomingRoute(Route* route) {
    throw X3DError("this field does not support incoming routes");
}

const list<Route*>& SAIField::getIncomingRoutes() const {
    throw X3DError("this field does not support incoming routes");
}

void SAIField::addOutgoingRoute(Route* route) {
    throw X3DError("this field does not support outgoing routes");
}

void SAIField::removeOutgoingRoute(Route* route) {
    throw X3DError("this field does not support outgoing routes");
}

const list<Route*>& SAIField::getOutgoingRoutes() const {
    throw X3DError("this field does not support outgoing routes");
}

}
