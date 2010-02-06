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

#include "internal/builtin.h"
#include "internal/Event.h"
#include <list>
#include <queue>

using std::list;
using std::priority_queue;
using namespace X3D::Core;
using namespace X3D::Time;

namespace X3D {

/**
 * This is the main X3D instance class. The browser controls
 * type registration, and the execution model.
 * It implements the X3D SAI (TODO).
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

	/// root scene nodes
	list<Node*> roots;

    /// sensors which have recently been created
    vector<X3DSensorNode*> newSensors;

    /// timers
    list<X3DTimeDependentNode*> timers;

    /// event queue
    priority_queue<Event> events;

    /// fields which need to be routed
    vector<SAIField*> dirtyFields;

    /// nodes which should be cleared
    vector<SAIField*> firedFields;

    /// named nodes
    map<string, Node*> defs;

	/// singleton instance
	static Browser* _inst;

    /// simulation time
    double simTime;
    
    /// next time to wake up
    double wakeupTime;

    /// whether simulation has started
    bool started;

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
     * Tell the browser to manage the memory for the given ndoe.
     * The node will not be automatically persisted.
     *
     * @param node node to garbage collect
     */
    void addNode(Node* node);

    /**
     * Gets the current simulation tick time.
     *
     * @returns simulation time
     */
    double now();

    /**
     * Clear the scene graph and free all resources.
     */
    void reset();

    /**
     * Process routes in a cascade. This function will block until
     * the cascade is complete.
     */
    void route();

    /**
     * Clear up fields from routing. Ends the cascade.
     */
    void endRoute();

    /**
     * Take one simulation step by proceeding to the next scheduled
     * time. If the simulation is complete (there is no more secheduled
     * activity), this function returns false.
     *
     * @returns whether simulation can continue
     */
    bool simulate();

    /**
     * Tell the browser to wake up at this time at the latest.
     * The browser may wake up any time before this, but must wake
     * up at least once before or at this time. This call is ignored
     * unless the browser is in simulation mode (as opposed to real-time
     * mode, where the browser simply wakes up as often as possible).
     *
     * @param time next time to wake up
     */
    void wake(double time);

    /**
     * Schedule an event to activate the given sensor at some point
     * in the future. The browser may wake up at any time before this,
     * and is not guaranteed to schedule events before or at the given
     * time. The sensor must be able to handle an arbitrary gap between
     * the time it was scheduled to be activated and the actual activation
     * time.
     *
     * @param time time sensor would like to be evaluated at
     * @param node node to schedule for evaluation
     */
    void schedule(double time, X3DSensorNode* node);

	/**
	 * Make the given node persistent, so that it will not be
	 * garbage collecected (until the browser shuts down).
	 * 
	 * @param node pointer to node to persist
	 */
	void persist(Node* node);

    /**
     * Add a new root node.
     * 
     * @param node node to add as a root
     */
    void addRoot(Node* node);

    /**
     * Add a named node mapping.
     * 
     * Field, event, PROTO, EXTERNPROTO, and node names shall not contain control
     * characters (0x0-0x1f, 0x7f), space (0x20), double or single quotes
     * (0x22: ", 0x27: '), sharp (0x23: #), comma (0x2c: ,), period (0x2e: .),
     * brackets (0x5b, 0x5d: []), backslash (0x5c: \) or braces (0x7b, 0x7d: {}).
     * Further, their first character shall not be a digit (0x30-0x39), plus
     * (0x2b: +), or minus (0x2d: -) character. Otherwise, names may contain any
     * ISO 10646 character encoded using UTF-8. X3D is case-sensitive; "Sphere"
     * is different from "sphere" and "BEGIN" is different from "begin."
     * 
     * @param name name of node
     * @param node node to map to
     */
    void addNamedNode(const string& name, Node* node);

    /**
     * Look up a node by its name, returning NULL if it isn't found.
     * 
     * @param name stored node name
     * @returns stored node
     */
    Node* getNode(const string& name);

    /**
     * Look up a node by its name, returning NULL if it isn't found.
     * Return a type-specific version of the node, and throw an error
     * if the type is incorrect.
     * 
     * @param name stored node name
     * @returns stored node
     */
    template <class N> N* getNode(const string& name) {
        Node* found = getNode(name);
        if (found == NULL)
            return NULL;
        N* node = dynamic_cast<N*>(found);
        if (node == NULL)
            throw X3DError("node type mismatch");
        return node;
    }

    /**
     * Find the first ROOT node which is a descendant of the given type.
     *
     * @returns first instance, or NULL if none
     */
    template <class N> N* getFirst() {
        list<Node*>::iterator it;
        for (it = roots.begin(); it != roots.end(); it++) {
            Node* node = *it;
            N* test = dynamic_cast<N*>(node);
            if (test != NULL)
                return test;
        }
        return NULL;
    }

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
            throw X3DError("no such node " + name);
		N* node = def->create<N>();
		if (node == NULL)
            throw X3DError("node creation failed");
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

    /**
     * Create a route between nodes based on field names. If such a route already
     * exists, this function will return the existing route. Otherwise, it will
     * create a new route and hook it up to the fields, then return it. The nodes
     * are looked up by their DEF name.
     * 
     * @param fromNode name of node to route from
     * @param fromField name of field to route from
     * @param toNode name of node to route to
     * @param toField name of field to route to
     * @returns new or existing route between fields
     */
    Route* createRoute(const string& fromNode, const string& fromField,
                       const string& toNode, const string& toField);

    /**
     * Add a dirty field to the list of
     * fields to route from.
     * 
     * @param field field to route from
     */
    void addDirtyField(SAIField* field);

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
