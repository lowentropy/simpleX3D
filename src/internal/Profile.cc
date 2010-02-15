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

#include "internal/Component.h"

#include <iostream>

using std::cout;
using std::endl;

namespace X3D {

Profile::~Profile() {
	list<Component*>::iterator it = comp_list.begin();
	for (; it != comp_list.end(); it++)
		delete *it;
}

Component* Profile::createComponent(const string& name) {
	Component* comp = new Component(this, name);
	comp_map[name] = comp;
	comp_list.push_back(comp);
	return comp;
}

Component* Profile::getComponent(const string& name) {
    if (!comp_map.count(name))
        throw new X3DError(string("no such component: ") + name);
    return comp_map[name];
}

void Profile::print() {
	cout << "PROFILE" << endl;
	list<Component*>::iterator it = comp_list.begin();
	for (; it != comp_list.end(); it++)
		(*it)->print();
}

NodeDef* Profile::getNode(const string& name) {
	list<Component*>::iterator it = comp_list.begin();
	for (; it != comp_list.end(); it++) {
		NodeDef* def = (*it)->getNode(name);
		if (def != NULL)
			return def;
	}
	return NULL;
}


}
