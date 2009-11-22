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

#ifndef _X3D_WORLD_H_
#define _X3D_WORLD_H_

#include "internal/Browser.h"
#include <string>
#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace X3D::Core;

namespace X3D {

class World {
protected:
	
	string version;
	string profile;
	WorldInfo* info;
	Browser* browser;
	
public:

	World(  Browser* browser,
			const string& version,
			const string& profile,
			const MFString& meta) :
		browser(browser),
		version(version),
		profile(profile) {
		info = browser->createNode<WorldInfo>("WorldInfo");
		info->info(meta);
	}

	static World* read(Browser* browser, const char* filename);

protected:

    void parseRoot(xmlNode* xml);
    void parseHead(xmlNode* xml);
    void parseScene(xmlNode* xml, Node* node);
    void parseComponent(xmlNode* xml);
    void parseMeta(xmlNode* xml);
    void parseProtoDeclare(xmlNode* xml);
    void parseExternProtoDeclare(xmlNode* xml);
    void parseProtoInstance(xmlNode* xml, Node* parent);
    void parseRoute(xmlNode* xml);
    void parseNode(xmlNode* xml, Node* parent);
    void parseImport(xmlNode* xml);
    void parseExport(xmlNode* xml);
};

}

#endif // #ifndef _X3D_WORLD_H_
