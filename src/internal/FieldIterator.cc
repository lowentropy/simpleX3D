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

#include "internal/Node.h"
#include "internal/NodeDef.h"
#include "internal/FieldIterator.h"

namespace X3D {

FieldIterator::FieldIterator(Node* node, IterMode mode) :
    node(node),
    mode(mode) {
    reset();
}

void FieldIterator::findNext() {
    while (++field_it != def->field_list.end())
        if (filter())
            return;
    while (++chain_it != node->definition->chain.end()) {
        def = *chain_it;
        if (def->field_list.empty())
            continue;
        field_it = def->field_list.begin();
        if (!filter())
            findNext();
        return;
    }
    atEnd = true;
}

bool FieldIterator::filter() {
    FieldDef* fieldDef = *field_it;
    switch (mode) {
        case INPUT: return fieldDef->inputCapable();
        case OUTPUT: return fieldDef->outputCapable();
        case ALL: return true;
        case DIRTY:
            SAIField* field = fieldDef->getField(node);
            return field->isDirty();
    }
}

SAIField* FieldIterator::nextField() {
    if (atEnd)
        return NULL;
    SAIField* field = (*field_it)->getField(node);
    findNext();
    return field;
}

FieldDef* FieldIterator::nextFieldDef() {
    if (atEnd)
        return NULL;
    FieldDef* def = *field_it;
    findNext();
    return def;
}

bool FieldIterator::hasNext() const {
    return !atEnd;
}

void FieldIterator::reset() {
    chain_it = node->definition->chain.begin();
    def = *chain_it;
    field_it = def->field_list.begin();
    // the first nodedef in chain is X3DNode, which
    // has one field, so we don't have to check here
    // if def->fields is empty.
    atEnd = false;
    if (!filter())
        findNext();
}

}
