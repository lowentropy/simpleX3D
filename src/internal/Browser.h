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

#ifndef _X3D_BROWSER_H_
#define _X3D_BROWSER_H_

#include "internal/Node.h"
#include "internal/NodeDef.h"
#include "internal/Profile.h"
#include "internal/builtin.h"
#include <list>

using std::list;

namespace X3D {

/**
 * This is the main X3D instance class. The browser controls
 * type registration, scene memory management (TODO), and
 * the execution model. It implements the X3D SAI (TODO).
 * 
 * Feel free to subclass the browser if you really need to
 * change how routing or memory management works, but keep
 * in mind that you should still attempt to support third-
 * party plugins.
 */
class Browser {
private:

	/// all nodes managed by the browser
	list<Node*> nodes;

	/// nodes we shouldn't garbage-collect
	list<Node*> persistent;

    /// nodes which generate events asynchronously
    list<Node*> sources;

	/// root scene nodes
	list<Node*> roots;

	/// singleton instance
	static Browser* _inst;

public:

	/// profile supported by the browser
	Profile* const profile;

	/// Default constructor. Initializes profile.
	Browser();

	/// Default destructor. Cleans up memory.
	virtual ~Browser();

	/**
	 * Create a new node instance of the given qualified
	 * name. The actual type of the node returned will be
	 * determined by the profile, so that plugins can register
	 * their own X3D types.
	 * 
	 * The node returned is managed by the browser automatically.
	 * If you want the node to persist, you must either add the
	 * node to the scene graph as a root node or as a field of
	 * a live node, or you can explicitly tell the browser to
	 * persist the node by calling #persist.
	 * 
	 * @param name qualified X3D node type name
	 * @returns an instance of the registered node type
	 */
	Node* createNode(const std::string& name);

    /**
     * Process routes in a cascade. This function will block until
     * the cascade is complete.
     */
    void route();

	/**
	 * Make the given node persistent, so that it will not be
	 * garbage collecected (until the browser shuts down).
	 * 
	 * @param node pointer to node to persist
	 */
	void persist(Node* node);

	/**
	 * Templatized node creation. This version of createNode
	 * will use the constructor of the actual template type,
	 * so that even if a subclass has been registered for the
	 * named X3D type, the base class can still be instantiated.
	 * 
	 * @param name qualified X3D node type name
	 * @returns an instance of the given (template) node type
	 */
	template <class N>
	N* createNode(const std::string& name) {
		NodeDef* def = profile->getNode(name);
		if (def == NULL)
			return NULL;
		N* node = def->create<N>();
		if (node == NULL)
			return NULL;
		nodes.push_back(node);
        if (node->eventSource())
            sources.push_back(node);
		return node;
	}

	/**
	 * Singleton access.
	 * 
	 * @returns singleton instance
	 */
	static Browser* getSingleton() {
		return _inst;
	}

    /**
     * Create a route between nodes based on field names. If such a route already
     * exists, this function will return the existing route. Otherwise, it will
     * create a new route and hook it up to the fields, then return it.
     * 
     * @param fromNode node to route from
     * @param fromField name of field to route from
     * @param toNode node to route to
     * @param toField name of field to route to
     * @returns new or existing route between fields
     */
    Route* createRoute(Node* fromNode, const string& fromField,
                       Node* toNode, const string& toField) const;

    /**
     * Create a route between nodes based on their field pointers. If such a
     * route already exists, this function will return the existing route. Otherwise,
     * it will create a new route and hook it up to the fields, then return it.
     * 
     * @param fromField field object to route from
     * @param toField field object to route to
     * @returns new or existing route between fields
     */
    Route* createRoute(SAIField* fromField, SAIField* toField) const;

private:

    /**
     * Route events from the given field, which should be marked dirty.
     * 
     * @param field field to route events from
     */
    void routeFrom(SAIField* field);

};

}

#endif // #ifndef _X3D_BROWSER_H_
