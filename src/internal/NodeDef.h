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

#ifndef _X3D_NODEDEF_H_
#define _X3D_NODEDEF_H_

#include "internal/Prototype.h"
#include <map>
#include <list>
#include <vector>

using std::map;
using std::list;
using std::vector;

namespace X3D {

class Component;
class Browser;

/**
 * Node definition base class. Defines the inheritance hierarchy for node
 * definitions, and provides a list of the node type's self-declared
 * fields.
 */
class NodeDef {

    // allow browser to access creation method
	friend class Browser;

    // allow prototype to access createPrototype method
    friend class Prototype;

public:
    /// map of field basename to field definition
	map<string, FieldDef*> fields;

    /// straight list of fields
    list<FieldDef*> field_list;

    /// map of field set_ name to field definition
    map<string, FieldDef*> in_fields;

    /// map of field _changed name to field definition
    map<string, FieldDef*> out_fields;

    /// chain from root ancestor to self
    list<NodeDef*> chain;

private:
    /// list of node parents
	vector<NodeDef*> parents;

protected:
    bool finished;

public:
    /// component in which node is defined
	Component* const component;

    /// canonical name of node
	const string name;

    /// whether node is abstract (and cannot be instantiated)
	const bool abstract;

    /**
     * Constructor.
     * 
     * @param component parent component
     * @param name canonical node name
     * @param abstract whether node definition is abstarct
     */
	NodeDef(Component* component, const string& name, bool abstract) :
		component(component), name(name), abstract(abstract), finished(false) {}

    /// Virtual destructor.
	virtual ~NodeDef();

    /**
     * Access the named field of the given node.
     * 
     * @param name field name
     * @param node node to access field on
     * @returns field object pointer
     */
    virtual SAIField* getField(const string& name, Node* node) = 0;
    
    /**
     * Add a node defintiion as a parent of this one. The parent node
     * definition must already exist in the system.
     * 
     * @param name name of node definition to be parent
     */
	void inherits(const string& name);

    /**
     * This should be called after all inheritance and field declaration
     * has been completed. Any further precomputation should be done.
     */
    void finish();

    /** @returns the name of the node type */
    const string& getName();

    /**
     * Pretty-print the node definition, in the manner of the X3D spec.
     * 
     * @param full if true, also include fields defined by parents
     */
	virtual void print(bool full = true);

    /**
     * Initialize a node by preparing its fields and calling the setup() 
     * chain defined by the node definition hierarchy.
     * 
     * @param node node to initialize
     */
    virtual void setup(Node* node) = 0;

    /**
     * This (non-recursive) function attempts to retrieve a field by its name.
     * It should allow search using the set_ or _changed prefix, for InOut fields.
     * 
     * @param name name of field
     * @returns field definition, if found, or NULL
     */
    FieldDef* getFieldDef(const string& name);

    /**
     * Create a new node which conforms to this node definition.
     * 
     * @returns new node instance
     */
	virtual Node* create() = 0;

protected:

    /**
     * Let the browser manage the memory for this node.
     */
    void manage(Node* node);

    /**
     * Create a new prototype definition which is based on this
     * node definition as its interface.
     * 
     * @returns new prototype definition
     */
    virtual Prototype* createPrototype(const string& name) = 0;

    /**
     * Create a node and return it in its particular type.
     * 
     * @returns new node instance
     */
    template <class N> N* create() {
        return dynamic_cast<N*>(create());
    }

    /** 
     * Add a field definition to this node. Field can be of any
     * access type.
     * 
     * @param field field definition to add
     */
	void addField(FieldDef* field);

    /**
     * Pretty-print the fields of this node.
     * 
     * @param full if true, recursively print field definitions of parents
     */
	void print_fields(bool full);

private:

    /**
     * Grow the inheritance chain recursively. Adds the given definition
     * after its ancestors, ignoring any definitions that already exist in
     * the chain.
     * 
     * @param def definition to add to chain
     */
    void growChain(NodeDef* def);
};


/**
 * Node definition implementation. This class is templatized by the actual
 * node class represented by this definition.
 */
template <class N>
class NodeDefImpl : public NodeDef {
public:
	friend class Browser;

    /**
     * Constructor.
     * 
     * @param comp component in which node is defined
     * @param name canonical name of node
     * @param abstract whether node definition is abstract
     */
	NodeDefImpl(Component* comp, const string& name, bool abstract) :
		NodeDef(comp, name, abstract) {}

    /**
     * Create a new instance of the template node type.
     * 
     * @returns new node instance
     */
	N* create() {
		if (abstract)
			throw X3DError("can't instantiate abstract nodes");
        if (!finished)
            throw X3DError("node definition was never finished");
        N* node = new N();
        node->definition = this;
        list<NodeDef*>::iterator it = chain.begin();
        for (; it != chain.end(); it++)
            (*it)->setup(node);
        manage(node);
        // XXX: possibly memory leak if setup methods fail
        return node;
	}

    /**
     * Create a new prototype definition which is based on this
     * node definition as its interface.
     * 
     * @returns new prototype definition
     */
    PrototypeImpl<N>* createPrototype(const string& name) {
        if (abstract)
            throw X3DError("can't create prototype from abstract node");
        if (!finished)
            throw X3DError("node definition was never finished");
        return new PrototypeImpl<N>(name);
    }

    /**
     * Access the named field of the given node.
     * 
     * @param name field name
     * @param node node to access field on
     * @returns field object pointer
     */
    SAIField* getField(const string& name, Node* node) {
        list<NodeDef*>::const_iterator it;
        for (it = chain.begin(); it != chain.end(); it++) {
            FieldDef* def = (*it)->getFieldDef(name);
            if (def != NULL)
                return def->getField(node);
        }
        return NULL;
    }

protected:

    /**
     * Set up the node by initializing its fields and calling the
     * setup() method defined by this node-definition level.
     * 
     * @param node node to set up
     */
    void setup(Node* node) {
        N* ptr = dynamic_cast<N*>(node);
        if (ptr == NULL)
            throw X3DError("setup() called on node of wrong type");
        initFields(ptr);
        ptr->N::setup();
    }

    /**
     * Initialize the fields of the given node by recursively looking
     * up all declared fields and calling their init method.
     * 
     * @param node node instance whose fields to set up
     */
    void initFields(N* node) {
        list<FieldDef*>::iterator it;
        for (it = field_list.begin(); it != field_list.end(); it++)
            (static_cast<FieldDefImpl<N>*>(*it))->init(node);
    }


public:

    /**
     * Create and return a new field definition for this node. This will
     * automatically add the field to the node definition. This method is
     * templatized by the field type used to declare the field, but generally
     * should not have to be specified manually.
     * 
     * @param name base name of field
     * @param type field data type
     * @param access field access level
     * @param ptr node class pointer to field declaration
     * @returns new field definition
     */
	template <typename T> FieldDef* createField(const string& name, X3DField::Type type, SAIField::Access access, T N::*ptr) {
        SAIField N::*field = (SAIField N::*) ptr;
		FieldDef* def = new FieldDefImpl<N>(this, name, type, access, field);
		addField(def);
		return def;
	}
};

}

#endif // #ifndef _X3D_NODEDEF_H_
