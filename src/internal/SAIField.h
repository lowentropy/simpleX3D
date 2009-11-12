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

#ifndef _X3D_SAIFIELD_H_
#define _X3D_SAIFIELD_H_

#include "internal/X3DField.h"
#include <string>
#include <list>

using std::string;
using std::list;

namespace X3D {

class Node;
class Route;

/**
 * Base class for all node-owned field instances. This is not a "definition"
 * class; instances of SAIField actually contain active field information.
 * The high-level interface of fields consists of get(), set(), and isDirty().
 */
class SAIField {
public:

    /// access level for node fields ([], [in], [ou], [in,out])
	typedef enum {
		INIT_ONLY,
		INPUT_ONLY,
		OUTPUT_ONLY,
		INPUT_OUTPUT
	} Access;

    /// Empty constructor.
    SAIField() {}

    /**
     * Get a pointer to the node which owns this field. Subclasses
     * should return a node of a specific type.
     * 
     * @returns node pointer
     */
	virtual Node* getNode() const = 0;

    /**
     * Get the datatype of this field.
     * 
     * @returns field datatype
     */
	virtual X3DField::Type getType() const = 0;

    /**
     * Get the access type of this field.
     * 
     * @returns field access level
     */
    virtual Access getAccess() const = 0;

    /**
     * Get the name of the datatype of this field. XXX: deprecated
     * 
     * @returns field datatype name
     */
	virtual string getTypeName() const = 0;

    /**
     * High-level field value getter.
     * 
     * @returns generic (wrapped) field value
     */
	virtual const X3DField& get() const = 0;

    /**
     * High-level field value setter.
     * 
     * @param value generic (wrapped) field value
     */
	virtual void set(const X3DField& value) = 0;

    /**
     * When a field has been changed since the last event cascade,
     * returns true. Dirty fields will be processed in the next
     * event window, triggering a callback action if any is provided.
     * Any routes from the field are then activated.
     * 
     * @returns whether field is marked as dirty
     */
	virtual bool isDirty() const = 0;

    /**
     * Clear the dirty value.
     */
    virtual void clearDirty() = 0;

    virtual void addIncomingRoute(Route* route) {
        throw X3DError("this field does not support incoming routes");
    }
    virtual void removeIncomingRoute(Route* route) {
        throw X3DError("this field does not support incoming routes");
    }
    virtual const list<Route*>& getIncomingRoutes() const {
        throw X3DError("this field does not support incoming routes");
    }

    virtual void addOutgoingRoute(Route* route) {
        throw X3DError("this field does not support outgoing routes");
    }
    virtual void removeOutgoingRoute(Route* route) {
        throw X3DError("this field does not support outgoing routes");
    }
    virtual const list<Route*>& getOutgoingRoutes() const {
        throw X3DError("this field does not support outgoing routes");
    }

private:

    // no copy constructor
    SAIField(const SAIField& f) { throw X3DError("COPY CONSTRUCTOR"); }
};

/**
 * Field class templatized to a particular node type, to which the field
 * belongs. This class in the hierarchy is used to get and set the
 * node pointer for each field.
 */
template <class N>
class NodeField : public SAIField {
protected:
    /// reference to node which owns this field
	N* node;
public:

    /// Empty constructor.
    NodeField() : node(NULL) {}

    /// @returns pointer to owner node
	N* getNode() const { return node; }

    /// @param node owner node to set
	void setNode(N* node) { this->node = node; }

private:

    // no copy constructor
    NodeField(const NodeField<N>& f) { throw X3DError("COPY CONSTRUCTOR"); }
};

/**
 * The direct base class of the particular field types. This class is
 * templatized both the the type of the node owning the field, and to
 * the data container type of the field. For instance, for an SFInt32
 * field belonging to the Foo node, one would use BaseField<Foo,SFInt32>.
 */
template <class N, class TT>
class BaseField : public NodeField<N> {
public:

    /// Empty constructor.
    BaseField() {}

    /// @returns the data type of the field
	X3DField::Type getType() const { static TT x; return x.getType(); }

    /// @returns the printable name of the field datatype
	string getTypeName() const { static TT x; return x.getTypeName(); }

private:

    // no copy constructor
    BaseField(const BaseField<N,TT>& f) { throw X3DError("COPY CONSTRUCTOR"); }
};

}

#endif // #ifndef _X3D_SAIFIELD_H_
