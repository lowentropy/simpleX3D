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

#ifndef _X3D_X3DGROUPINGNODE_H_
#define _X3D_X3DGROUPINGNODE_H_

namespace X3D {
namespace Grouping {

class X3DGroupingNode : public X3DChildNode, public X3DBoundedObject {
public:

    class AddChildren : 
        public InField<X3DGroupingNode, MFNode<X3DChildNode> > {
        void action(const MFNode<X3DChildNode>& nodes) {
            node()->add(nodes);
        }
    } addChildren;

    class RemoveChildren :
        public InField<X3DGroupingNode, MFNode<X3DChildNode> > {
        void action(const MFNode<X3DChildNode>& nodes) {
            node()->remove(nodes);
        }
    } removeChildren;

    DefaultInOutField<X3DGroupingNode, MFNode<set, X3DChildNode> > children;

    void setup();

protected:

    void add(const MFNode<X3DChildNode>& nodes);
    void remove(const MFNode<X3DChildNode>& nodes);
};

}}

#endif // #ifndef _X3D_X3DGROUPINGNODE_H_

