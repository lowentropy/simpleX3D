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

#include "Grouping/X3DGroupingNode.h"
#include <set>
using std::set;

namespace X3D {
namespace Grouping {

void X3DGroupingNode::setup() {
}

void X3DGroupingNode::add(const MFNode<X3DChildNode>& nodes) {
    MFNode<X3DChildNode>::const_iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
        children().add(*it);
    children.changed();
}

void X3DGroupingNode::remove(const MFNode<X3DChildNode>& nodes) {
    MFNode<X3DChildNode>::const_iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
        children().remove(*it);
    children.changed();
}

}}

