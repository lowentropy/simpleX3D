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
#include <map>

using std::string;
using std::list;

namespace X3D {

class Node;
class Route;
class FieldDef;

/**
 * Base class for all node-owned field instances. This is not a "definition"
 * class; instances of SAIField actually contain active field information.
 * The high-level interface of fields consists of get(), set(), and isDirty().
 */
class SAIField {
public:

    FieldDef* definition;

    /// access level for node fields ([], [in], [ou], [in,out])
	typedef enum {
		INIT_ONLY,
		INPUT_ONLY,
		OUTPUT_ONLY,
		INPUT_OUTPUT
	} Access;

    /// Empty constructor.
    SAIField() {}
    virtual ~SAIField() {}

    /** @returns the name of the field */
    virtual const string& getName() const;

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
     * Get access level from string name. Used
     * in prototype and script fields.
     *
     * @param name name of access level
     * @returns actual access level enum
     */
    static Access getAccess(const string& name);

    /**
     * Get the name of the datatype of this field. XXX: deprecated
     * 
     * @returns field datatype name
     */
	virtual const string& getTypeName() const;

    /**
     * Clone this field by initializing its opposite member in
     * another node. Depending on the arguments, this may be recursive.
     *
     * @param node node containing target field
     * @param mapping mapping from old node to new node
     * @param shallow whether clone should stop at first level
     * @returns target field
     */
    SAIField* cloneInto(Node* node, std::map<Node*,Node*>*mapping=NULL, bool shallow=false);

    /**
     * High-level field value getter.
     * 
     * @returns generic (wrapped) field value
     */
	virtual const X3DField& get() const = 0;

    /**
     * Non-const version of value getter.
     * 
     * @returns generic (wrapped) field value
     */
    virtual X3DField& get() = 0;

    /**
     * Returns the field value at any stage.
     *
     * @returns generic (wrapped) field value
     */
    virtual X3DField& getSilently() = 0;

    /**
     * High-level field value setter.
     * 
     * @param value generic (wrapped) field value
     */
	virtual void set(const X3DField& value) = 0;

    /**
     * Sets the field value at any stage and without triggering
     * any events. This method is not safe to use for fields with
     * active routes.
     *
     * @param value generic (wrapped) field value
     */
    virtual void setSilently(const X3DField& value) = 0;

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

    virtual void addIncomingRoute(Route* route);
    virtual void removeIncomingRoute(Route* route);
    virtual const list<Route*>& getIncomingRoutes() const;

    virtual void addOutgoingRoute(Route* route);
    virtual void removeOutgoingRoute(Route* route);
    virtual const list<Route*>& getOutgoingRoutes() const;

    void dispose();

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

    /// Initializing constructor (called only from dynamic fields)
    NodeField(N* node) : node(node) {}

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

    INLINE X3DField::Type getType() const {
        static TT x;
        return x.getType();
    }

private:

    // no copy constructor
    BaseField(const BaseField<N,TT>& f) { throw X3DError("COPY CONSTRUCTOR"); }
};

}

#endif // #ifndef _X3D_SAIFIELD_H_
