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

#include Grouping/X3DGroupingNode.h

namespace X3D {
namespace Grouping {

void X3DGroupingNode::setup() {
}

void X3DGroupingNode::add(const MFNode<vector, X3DChildNode>& nodes) {
    set<X3DChildNode*>& children = this->children.internal();
    const vector<X3DChildNode*>& list = nodes.internal();
    vector<X3DChildNode*>::const_iterator it;
    for (it = list.begin(); it != list.end(); it++)
        children.insert(*it);
}

void X3DGroupingNode::remove(const MFNode<vector, X3DChildNode>& nodes) {
    list<X3DChildNode*>& children = this->children.getList();
    const list<X3DChildNode*>& list = nodes.getList();
    list<X3DChildNode*>::const_iterator it;
    for (it = list.begin(); it != list.end(); it++)
        children.remove(*it);
}

}}

