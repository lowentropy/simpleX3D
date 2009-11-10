#ifndef _X3D_COMPONENT_H_
#define _X3D_COMPONENT_H_

#include "internal/Profile.h"
#include "internal/NodeDef.h"

#include <map>
#include <list>

using std::map;
using std::list;

namespace X3D {

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
	list<NodeDef*> node_list;

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

#endif // #ifndef _X3D_COMPONENT_H_
