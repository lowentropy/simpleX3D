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

#include "Core/X3DNode.h"
#include "internal/Browser.h"

namespace X3D {
namespace Core {

void X3DNode::assignMetadata(const map<string,string>& meta, bool quiet) {
	if (metadata == NULL)
		set("metadata", browser()->createNode("MetadataSet"), quiet);
	metadata->assignFromMap(meta, quiet);
}

Browser* X3DNode::browser() {
	return Browser::getSingleton();
}

void X3DNode::set(const string& field, const SafePointer& value, bool quiet) {
	definition->set(this, field, value, quiet);
}

SafePointer X3DNode::get(const string& field) const {
	return definition->get(this, field);
}

void X3DNode::changed(const string& field) const {
	return definition->changed(this, field);
}

}}
