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

#ifndef _X3D_ROUTE_H_
#define _X3D_ROUTE_H_

#include "internal/Node.h"
#include "internal/SAIField.h"

namespace X3D {

class Route {
public:
    /// field which is source of event
    SAIField* const from_field;

    /// field which is target of event
    SAIField* const to_field;

    /// Basic constructor.
    Route(SAIField* from, SAIField* to) :
            from_field(from), to_field(to) {
        checkTypes();
    }

    /**
     * Lookup constructor; takes nodes and in/out field names.
     * 
     * @param from_node node which generates event
     * @param from_field name of node output field
     * @param to_node node which receives event
     * @param to_field name of node input field
     */
    Route(Node* from_node, const string& from_field,
          Node* to_node, const string& to_field) :
            from_field(from_node->getField(from_field)),
            to_field(to_node->getField(to_field)) {
        checkTypes();
    }
    
    /**
     * Activate the route, creating an event from the #from_field
     * to the #to_field.
     */
    void activate();

private:

    /// Make sure from and to field types are the same
    void checkTypes();
};

}

#endif // #ifndef _X3D_ROUTE_H_
