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

#ifndef _X3D_NODE_H_
#define _X3D_NODE_H_

#include "internal/FieldIterator.h"
#include <string>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <map>

using std::string;

namespace X3D {

// forward declarations
class NodeDef;
class Browser;

/**
 * Base class for all abstract and concrete node types.
 * This class by itself doesn't do much except track the
 * node lifecycle.
 */
class Node {
friend class NodeDef;
public:
    /// Node lifcycle stage definitions
	typedef enum {
		CREATION,
		SETUP,
		REALIZED,
		DISPOSED
	} Stage;

    /// Definition of node, which may be a static definition or prototype definition
	NodeDef* definition;

    /// Current stage of node lifecycle
	Stage stage;

private:

    string name;

    /// Disallow copy constructor
	Node(const Node& node) { throw X3DError("illegal copy"); }

public:
    /// Empty constructor. Nodes start in stage SETUP.
	Node() : stage(SETUP), definition(NULL) {}

    /// Virtual deconstructor.
	virtual ~Node() {}
    
    const string& getName() const {
        return name;
    }

    void setName(const string& name) {
        this->name = name;
    }

    /**
     * Clone this node's memory by copying field values into a new
     * node of the same type. Depending on the arguments, this may
     * proceed recursively. If a mapping is provided, a link between
     * original and cloned nodes can be maintained. This is useful to
     * copy routes one the tree structure is complete.
     * The browser will not have a reference to this new node,
     * so memory management is the caller's resposibility.
     * 
     * @param mapping mapping from old node to new node
     * @param shallow whether clone should stop at first level
     * @returns cloned node
     */
    Node* clone(std::map<Node*,Node*>* mapping=NULL, bool shallow=false);

    /**
     * Clone this node's memory by copying field values into a new
     * node of the same type. Depending on the arguments, this may
     * proceed recursively. If a mapping is provided, a link between
     * original and cloned nodes can be maintained. This is useful to
     * copy routes one the tree structure is complete.
     * 
     * @param target target node to clone into
     * @param mapping mapping from old node to new node
     * @param shallow whether clone should stop at first level
     * @returns cloned node
     */
    void cloneInto(Node* target, std::map<Node*,Node*>* mapping=NULL, bool shallow=false);
    
    /**
     * Look up a field on the node and return a reference to it.
     * For input-output fields, either the base name or the set_
     * or _changed modifiers may be used. Currently, they will all
     * return the same field. XXX does the spec want limited-accessor
     * versions? do i care?
     * 
     * @param name name of field
     * @returns pointer to actual field
     */
    virtual SAIField* getField(const string& name);

    /**
     * Look up a field on the node and return a reference to it.
     * For input-output fields, either the base name or the set_
     * or _changed modifiers may be used. Currently, they will all
     * return the same field. XXX does the spec want limited-accessor
     * versions? do i care?
     *
     * This is the type-specific version of getField. If the actual
     * field does not match, an error is thrown.
     * 
     * @param name name of field
     * @returns pointer to actual field
     */
    template <class F> F* getField(const string& name) {
        SAIField* found = getField(name);
        if (found == NULL)
            return NULL;
        F* field = dynamic_cast<F*>(found);
        if (field == NULL)
            throw X3DError("field type mismatch");
        return field;
    }

    /**
     * Create and return an iterator into the run-time fields of this node.
     * The given mode (defaulting to all fields) is used to filter the
     * results.
     * 
     * @param mode filtering mode (defaults to ALL)
     * @returns field iterator for this node
     */
    FieldIterator fields(FieldIterator::IterMode mode = FieldIterator::ALL);

    /// @returns current lifecycle stage
	Stage getStage() const { return stage; }

    /// @returns whether node is in REALIZED stage
	bool realized() const { return stage == REALIZED; }

    /// Moves the node to the REALIZED stage.
	void realize() { stage = REALIZED; }

    /**
     * Function to provide initialization AFTER the fields
     * have had their node pointer set, allowing us to set default
     * values on our fields. Don't make it virtual; it's provided
     * by contract rather than polymorphism.
     */
    void setup() {}

	/**
	 * Return a reference to the browser. This is a helper function
	 * that simply calls Browser::getSingleton.
	 * 
	 * @returns singleton instance of Browser
	 */
	Browser* browser();

    /**
     * Queue a field for routing.
     * FIXME this is not an ideal calling scenario.
     * 
     * @param field field to route from
     */
    void queue(SAIField* field);

    /// @returns the default containerField for this node
    virtual const string& defaultContainerField();

    /**
     * If the given element has a special purpose for this node,
     * parse and handle it in some way and then return true. Otherwise
     * return false.
     * 
     * @param xml xml element to test and/or handle
     * @returns whether special parsing was performed
     */
    virtual bool parseSpecial(xmlNode* xml, const string& filename);
};

}

#endif // #ifndef _X3D_NODE_H_
