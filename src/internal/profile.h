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

#ifndef _X3D_PROFILE_H_
#define _X3D_PROFILE_H_

#include "internal/X3DField.h"
#include "internal/SAIField.h"
#include <map>
#include <vector>
#include <iostream> // XXX

using std::map;
using std::vector;
using std::string;

namespace X3D {

// forward declarations
class Profile;
class Component;
class NodeDef;

/**
 * Defines the comformance profile for a given library-plugin combination.
 * Profiles consist of a set of component definitions, which in turn define
 * node comformance.
 */
class Profile {
private:
    /// map of components, by name
	map<string, Component*> comp_map;

    /// flat list of components
	vector<Component*> comp_list;

public:
    /// Empty constructor.
	Profile() {}

    /// Virtual desctructur; frees component definitions.
	virtual ~Profile();

    /**
     * Create a new, empty component defintion. The profile will manage
     * the memory of the returned pointer.
     * 
     * @param name canonical name of component
     * @returns pointer to new component definition
     */
	Component* createComponent(const string& name);

    /**
     * Find and return a node definition given its canonical name.
     * This function will look in each component.
     * 
     * @param name canonical name of node
     * @returns node definition pointer
     */
	NodeDef* getNode(const string& name);

    /**
     * Pretty-print the profile definition, mimicking the format
     * of the X3D spec.
     */
	virtual void print();
};

// forward declaration
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
	const X3DField::Access access;

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
		X3DField::Access access) :
		nodeDef(nodeDef),
		name(name),
		type(type),
		access(access) {}
	
    /**
     * Pretty-printing method.
     */
    void print();
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
		X3DField::Access access,
		SAIField N::*field) :
		FieldDef(nodeDef, name, type, access),
		field(field) {}

    /**
     * Initialization method called by the browser when an instance of the
     * parent node type is instantiated. Sets the node pointer on the runtime
     * fields of the node.
     */
    void init(N* node) {
        std::cout << "calling init() on " << name << " (" << this << ") with " << node << std::endl;
        NodeField<N>* f = static_cast<NodeField<N>*>(&(node->*field));
        f->setNode(node);
    }
};

/**
 * Node definition base class. Defines the inheritance hierarchy for node
 * definitions, and provides a list of the node type's self-declared
 * fields.
 */
class NodeDef {
private:
    /// map of field basename to field definition
	map<string, FieldDef*> fields;

    /// list of node parents
	vector<NodeDef*> parents;

    // allow browser to access creation method
	friend class Browser;

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
		component(component), name(name), abstract(abstract) {}

    /// Virtual destructor.
	virtual ~NodeDef();
    
    /**
     * Add a node defintiion as a parent of this one. The parent node
     * definition must already exist in the system.
     * 
     * @param name name of node definition to be parent
     */
	void inherits(const string& name);

    /**
     * Pretty-print the node definition, in the manner of the X3D spec.
     * 
     * @param full if true, also include fields defined by parents
     */
	virtual void print(bool full = true);

protected:

    /**
     * Create a new node which conforms to this node definition.
     * 
     * @returns new node instance
     */
	virtual Node* create() = 0;

    /**
     * Create an instance of the particular template node type.
     * This will automatically initialize the fields of the node.
     * 
     * @returns new node instance
     */
	template <class N> N* create() {
		if (abstract)
			throw X3DError("can't instantiate abstract nodes");
        N* node = new N();
        node->definition = this;
        initFields<N>(node);
        node->setup();
        return node;
	}

    /**
     * Initialize the fields of the given node by recursively looking
     * up all declared fields and calling their init method.
     * 
     * @param node node instance whose fields to set up
     */
    template <class N> void initFields(N* node) {
        map<string, FieldDef*>::iterator fit = fields.begin();
        for (; fit != fields.end(); fit++) {
            (static_cast<FieldDefImpl<N>*>(fit->second))->init(node);
        }
        vector<NodeDef*>::iterator pit = parents.begin();
        for (; pit != parents.end(); pit++)
            (*pit)->initFields(node);
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

protected:

    /**
     * Create a new instance of the template node type.
     * 
     * @returns new node instance
     */
	N* create() {
		return NodeDef::create<N>();
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
	template <typename T> FieldDef* createField(const string& name, X3DField::Type type, X3DField::Access access, T N::*ptr) {
        SAIField N::*field = (SAIField N::*) ptr;
		FieldDef* def = new FieldDefImpl<N>(this, name, type, access, field);
		addField(def);
		return def;
	}
};

/**
 * A component groups a set of related functionality in the form of
 * a set of node definitions. The components used by simpleX3D are
 * meant to directly mirror those defined in the ISO X3D spec.
 */
class Component {
private:
    /// map of node name to definition
	map<string, NodeDef*> node_map;

    /// flat list of node definitions
	vector<NodeDef*> node_list;

public:
    /// canonical name of component
	const string name;

    /// reference to profile which owns this component
    Profile* const profile;

    /**
     * Constructor.
     * 
     * @param profile parent profile reference
     * @param name canonical component name
     */
	Component(Profile* profile, const string& name) :
        profile(profile), name(name) {}

    /// Virtual destructor.
	virtual ~Component();

    /**
     * Find a node definition by its name. This function will only search
     * nodes defined within this component.
     * 
     * @param name canonical node name
     * @returns node reference, if found, or NULL
     */
	NodeDef* getNode(const string& name);

    /**
     * Pretty-print the entire component definition in the manner
     * of the X3D spec.
     */
	virtual void print();

    /**
     * Create and add a new empty node definition with the given parameters.
     * This function is templatized by the node class represented by the
     * definition.
     * 
     * @param name canonical node name
     * @param abstract whether node definition is abstract
     * @returns new node definition instance
     */
	template <class T> NodeDefImpl<T>* createNode(const string& name, bool abstract=false) {
		NodeDefImpl<T>* def = new NodeDefImpl<T>(this, name, abstract);
		node_map[name] = def;
		node_list.push_back(def);
		return def;
	}

};

}

#endif // #ifndef _X3D_PROFILE_H_
