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

namespace X3D {

class Route {
public:
    /// field which is source of event
    SAIField* const fromField;

    /// field which is target of event
    SAIField* const toField;

    /// Basic constructor.
    Route(SAIField* from, SAIField* to) :
            fromField(from), toField(to) {
        if (from == NULL)
            throw X3DError("source field is null");
        if (to == NULL)
            throw X3DError("target field is null");
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
            fromField(from_node->getField(from_field)),
            toField(to_node->getField(to_field)) {
        checkTypes();
    }
    
    /**
     * Activate the route, creating an event from the #fromField
     * to the #toField.
     */
    void activate() const;

    /**
     * Remove this route from the scene by de-listing it, but don't free its
     * memory. After calling this method, the route is dangling (not part of
     * the scene).
     */
    void remove();

    /**
     * Assuming this route is dangling (not inserted into the scene), insert it.
     */
    void insert();

private:

    /// Make sure from and to field types are the same
    void checkTypes();
};

}

#endif // #ifndef _X3D_ROUTE_H_
