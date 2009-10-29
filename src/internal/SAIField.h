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

#ifndef _X3D_SAIFIELD_H_
#define _X3D_SAIFIELD_H_

#include "internal/X3DField.h"
#include <string>

using std::string;

namespace X3D {

class Node;

class SAIField {
public:
	virtual Node* getNode() const = 0;
	virtual X3DField::Type getType() const = 0;
	virtual const string& getTypeName() const = 0;
	virtual const X3DField& get() const = 0;
	virtual void set(const X3DField& value) = 0;
	virtual void route() = 0;
};

template <class N>
class NodeField : public SAIField {
protected:
	N* node;
public:
	N* getNode() const { return node; }
	void setNode(N* node) { this->node = node; }
};

template <class N, class TT>
class BaseField : public NodeField<N> {
public:
	X3DField::Type getType() const { static TT x; return x.getType(); }
	const string& getTypeName() const { static TT x; return x.getTypeName(); }
};

}

#endif // #ifndef _X3D_SAIFIELD_H_
