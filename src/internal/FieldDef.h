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

#ifndef _X3D_FIELDDEF_H_
#define _X3D_FIELDDEF_H_

#include "internal/SAIField.h"

namespace X3D {

class NodeDef;

/**
 * Field definition structure. Defines the name, type, and access permissions
 * of a given field. This is an abstract class; FieldDefImpl actually contains
 * a type-specific pointer into the node which contains the field.
 */
class FieldDef {
public:
    /// pointer to parent node definition
	NodeDef* const nodeDef;

    /// base name of field (i.e. without set_ or _changed, if InOut)
	const string name;

    /// X3D Field type (i.e. SFINT32, MFNODE, etc.)
	const X3DField::Type type;

    /// Access type (init-only, input-only, output-only, or input-output)
	const SAIField::Access access;

    /**
     * Constructor.
     * 
     * @param nodeDef parent node definition pointer
     * @param name field name
     * @param type field datatype
     * @param access field access level
     */
	FieldDef(
		NodeDef* nodeDef,
		const string& name,
		X3DField::Type type,
		SAIField::Access access) :
		nodeDef(nodeDef),
		name(name),
		type(type),
		access(access) {}
	
    /**
     * Pretty-printing method.
     */
    void print();

    /**
     * Return a pointer to the instance specified by this field
     * definition, owned by the given node pointer.
     * 
     * @param node node to look up field on
     * @returns pointer to field object instance
     */
    virtual SAIField* getField(Node* node) = 0;

    /// @returns true if the field INPUT_ONLY or INPUT_OUTPUT
    bool inputCapable();

    /// @returns true if the field OUTPUT_ONLY or INPUT_OUTPUT
    bool outputCapable();
};

/**
 * Base class for field definitions in a particular node. Contains
 * a generic member pointer into the template-provided node type.
 */
template <class N>
class FieldDefImpl : public FieldDef {
public:
    /// generic member pointer to runtime field
	SAIField N::*const field;

    /**
     * Constructor.
     * 
     * @param nodeDef parent node definition pointer
     * @param name field name
     * @param type field datatype
     * @param access field access level
     * @param field node member pointer
     */
	FieldDefImpl(
		NodeDef* nodeDef,
		const string& name,
		X3DField::Type type,
		SAIField::Access access,
		SAIField N::*field) :
		FieldDef(nodeDef, name, type, access),
		field(field) {}

    /**
     * Initialization method called by the browser when an instance of the
     * parent node type is instantiated. Sets the node pointer on the runtime
     * fields of the node.
     */
    void init(N* node) {
        NodeField<N>* f = static_cast<NodeField<N>*>(&(node->*field));
        f->setNode(node);
        f->definition = this;
    }

    /**
     * Return a pointer to the instance specified by this field
     * definition, owned by the given node pointer.
     * 
     * @param node node to look up field on
     * @returns pointer to field object instance
     */
    virtual SAIField* getField(Node* node) {
        N* ptr = dynamic_cast<N*>(node);
        if (ptr == NULL)
            throw X3DError("called getField() on node of wrong type");
        return &(ptr->*field);
    }
};

}

#endif // #ifndef _X3D_FIELDDEF_H_
