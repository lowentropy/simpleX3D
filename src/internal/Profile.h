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

#include <map>
#include <list>
#include <string>

using std::map;
using std::list;
using std::string;

namespace X3D {

// forward declarations
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
	list<Component*> comp_list;

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

}

#endif // #ifndef _X3D_PROFILE_H_
