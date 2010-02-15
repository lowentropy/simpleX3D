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

#ifndef _X3D_PLUGIN_H_
#define _X3D_PLUGIN_H_

#include "internal/Browser.h"
#include "internal/Component.h"

#include <stdlib.h>
#include <dlfcn.h>
#include <list>

namespace X3D {

class Plugin {
private:

    string name;
    string library;
    string version;
    std::list<std::pair<NodeDef*, AbstractFactory*> > factories;

public:

    Plugin(const string& library) : library(library) {}

    void registerPlugin();
    void remove();

    template <class N>
    NodeDef* addFactory(const string& component, const NodeFactory<N>* factory) {
        Browser* browser = Browser::getSingleton();
        Component* comp = browser->profile->getComponent(component);
        NodeDef* def = comp->addFactory(factory);
        factories.push_back(std::pair<NodeDef*,AbstractFactory*>(def, factory));
        return def;
    }

    const string& getName() { return name; }
    const string& getLibrary() { return library; }
    const string& getVersion() { return version; }
};

}

#endif // #ifndef _X3D_PLUGIN_H_
