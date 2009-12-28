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

#ifndef _X3D_FIELDITERATOR_H_
#define _X3D_FIELDITERATOR_H_

#include "internal/FieldDef.h"

namespace X3D {

class Node;
class NodeDef;

/**
 * This class allows you to easily iterate over the fields of a node,
 * since looking up a field is a two-step process (find the field definition
 * and then dereference its internal pointer). There are four iteration modes
 * which allow you to filter which fields are returned. Use the hasNext() and
 * next() methods to loop through the fields.
 *
 * TODO: write a const version of FieldIterator
 */
class FieldIterator {
public:

    /// Iteration mode lets you filter based on four criteria:
    /// - INPUT: input-capable fields (INPUT_ONLY, INPUT_OUTPUT)
    /// - OUTPUT: output-capable fields (OUTPUT_ONLY, INPUT_OUTPUT)
    /// - DIRTY: all output capable fields which are marked dirty
    /// - CAN_INIT: all initializable fields (INIT_ONLY, INPUT_OUTPUT)
    /// - ALL: all input or output-capable fields
    typedef enum {
        INPUT,
        OUTPUT,
        DIRTY,
        CAN_INIT,
        ALL
    } IterMode;

    /// Node we're looking up fields on
    Node* const node;

    /// Iteration mode
    const IterMode mode;

    /// Constructor.
    FieldIterator(Node* node, IterMode mode);

    /// Reset to the beginning of the list.
    void reset();

    /// @returns whether there are more fields to return
    bool hasNext() const;

    /// @returns the next filtered field
    SAIField* nextField();

    /// @returns the next filtered field definition
    FieldDef* nextFieldDef();

private:

    /// whether we reached the end of the fields
    bool atEnd;

    /// Current node definition in the recursive chain
    NodeDef* def;

    /// The field iterator
    list<FieldDef*>::iterator field_it;

    /// The node definition hierarchy iterator
    list<NodeDef*>::iterator chain_it;

    /// Chomp until the next filtered field is found
    void findNext();

    /// Return true if the current field def passes the filter
    bool filter();
};

}

#endif // #ifndef _X3D_FIELDITERATOR_H_
