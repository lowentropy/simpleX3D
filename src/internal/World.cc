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

#include "internal/World.h"

namespace X3D {

World* World::read(Browser* browser, const char* filename) {
    World* world = new World(browser, "", "", MFString());
    xmlDoc* doc;
    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL)
        throw X3DError("failed to parse file");
    world->construct(xmlDocGetRootElement(doc));
    xmlFreeDoc(doc);
}

void World::construct(xmlNode* node, int level) {
    // TODO: load
    // XXX
    /*
    xmlNode* child;
    for (child = node; child != NULL; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            for (int i = 0; i < level; i++)
                cout << "  ";
            cout << child->name << endl;;
            construct(child->children, level+1);
        }
    }
    */
}

}
