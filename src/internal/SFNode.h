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

#ifndef _X3D_SFNODE_H_
#define _X3D_SFNODE_H_

#include "internal/Node.h"
#include <ios>
#include <sstream>
#include <cstring>


namespace X3D {

/**
 * The root class of all node types. The only job of this class is to present
 * a non-templatized base for the SFNode type.
 */
class SFAbstractNode : public X3DField {
public:
    /// @returns SFNODE
	INLINE X3DField::Type getType() const { return X3DField::SFNODE; }

    /// @returns native but non-specific pointer to node value
	virtual Node* operator()() const = 0;

    virtual void set(Node* node) = 0;

    /**
     * Unwrap a generic field value containing a node.
     * In addition to checking the that the field is of type
     * SFNODE, the target node value must be a descendant of
     * Node. No check is performed, since it is highly unlikely
     * that a non-node pointer is contained in the wrapper.
     * 
     * @param f generic field value
     * @returns native node pointer
     */
	INLINE static Node* unwrap(const X3DField& f) {
		if (f.getType() != X3DField::SFNODE)
			throw X3DError(
                string("base type mismatch; expected SFNode") +
                ", but was " + f.getTypeName());
		const SFAbstractNode& n = static_cast<const SFAbstractNode&>(f);
        return n();
	}

protected:

    // XXX this is because we can't include Browser.h, but we
    // need to be able to look up nodes for parsing.
    Node* getNode(const string& name);

public:

};

/**
 * Templatized field type for node-containing values. The template type indicates
 * the base class for any nodes contained by this wrapper type.
 */
template <class N>
class SFNode : public SFAbstractNode {
public:
	typedef N* TYPE;
    typedef N* CONST_TYPE;

    /// pointer to actual node value
	N* value;

    /// Empty constructor.
	INLINE SFNode() : value(NULL) {}

    /// Initializing constructor.
	INLINE SFNode(N* value) : value(value) {}

    /// @returns native pointer value
	INLINE N* operator()() const { return value; }

    /**
     * Unwrap a generic field value containing a node.
     * In addition to checking the that the field is of type
     * SFNODE, the target node value must be a descendant of
     * this wrapper's template type. To check this, we perform
     * a dynamic cast.
     * 
     * @param f generic field value
     * @returns native node pointer
     */
	INLINE static N* unwrap(const X3DField& f) {
		if (f.getType() != X3DField::SFNODE)
			throw X3DError(
                string("base type mismatch; expected SFNode") +
                ", but was " + f.getTypeName());
		const SFAbstractNode& n = static_cast<const SFAbstractNode&>(f);
        if (n() == NULL)
            return NULL;
		N* v = dynamic_cast<N*>(n());
		if (v == NULL)
			throw X3DError("node type mismatch");
		return v;
	}

    void set(Node* node) {
        if (node == NULL)
            value = NULL;
        else {
            N* n = dynamic_cast<N*>(node);
            if (n == NULL)
                throw X3DError("node type mismatch");
            value = n;
        }
    }

    /// Low-level assignment operator.
	INLINE SFNode<N>& operator=(N* value) { this->value = value; }

    /// High-level assignment operator.
	INLINE SFNode<N>& operator=(const SFNode<N>& f) {
		value = f.value;
		return *this;
	}

    /// High-level assignment operator
    SFNode<N>& operator()(const X3DField& f) {
        return *this = unwrap(f);
    }

    /// Generic comparison operator (equal)
    INLINE bool operator==(const X3DField& f) const { return value == unwrap(f); }

    /// Generic comparison operator (not equal)
    INLINE bool operator!=(const X3DField& f) const { return value != unwrap(f); }

    /// Native comparison operator (equal)
    INLINE bool operator==(const SFNode<N>& n) const { return value == n.value; }

    /// Native comparison operator (not equal)
    INLINE bool operator!=(const SFNode<N>& n) const { return value != n.value; }

    INLINE void realize() {
        if (value != NULL)
            value->realize();
    }

    bool parse(istream& is) {
        std::stringbuf sb;
        is.get(sb);
        if (is.fail())
            return false;
        const string& name = sb.str();
        Node* node = getNode(name);
        if (node == NULL) {
            if (name == "NULL") {
                value = NULL;
            } else {
                throw X3DError(string("can't find node: ") + name);
            }
        } else {
            N* newval = dynamic_cast<N*>(node);
            if (newval == NULL)
                throw X3DError(string("wrong node type: ") + name);
            value = newval;
        }
        return true;
    }

    void print(ostream& os) const {
        if (value == NULL) {
            os << "NULL";
        } else {
            const string& name = value->getName();
            if (name.empty())
                throw X3DError("node has no DEF name");
            os << name;
        }
    }

};

}

#endif // #ifndef _X3D_SFNODE_H_
