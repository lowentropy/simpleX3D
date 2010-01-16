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

#ifndef _X3D_CONNECT_H_
#define _X3D_CONNECT_H_

namespace X3D {

/**
 * Represents a <connect> node inside an <IS> statement.
 */
class Connect {
public:
    
    Node* node;
    string nodeField;
    string protoField;

    Connect(Node* node, const string& nodeField, const string& protoField)
        : node(node), nodeField(nodeField), protoField(protoField) {}
};

}

#endif // #ifndef _X3D_CONNECT_H_
