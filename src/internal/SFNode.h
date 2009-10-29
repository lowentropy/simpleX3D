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

#ifndef _X3D_SFNODE_H_
#define _X3D_SFNODE_H_

class SFAbstractNode : public X3DField {
public:
	inline X3DField::Type getType() const { return SFNODE; }
	inline const string& getTypeName() const { return "SFNode"; }
};

template <class N>
class SFNode : public SFAbstractNode {
public:
	typedef N* TYPE;
	N* value;

	inline SFNode() {}
	inline SFNode(N* value) : value(value) {}
	inline N* operator()() const { return value; }

	inline static N* unwrap(const X3DField& f) {
		if (f.getType() != SFNODE)
			throw X3DError("base type mismatch");
		const SFAbstractNode& n = static_cast<const SFAbstractNode&>(f);
		N* v = dynamic_cast<N*>(n());
		if (v == NULL)
			throw X3DError("node type mismatch");
		return v;
	}

	inline const SFNode<N>& operator=(N* value) { this->value = value; }
	inline const SFNode<N>& operator=(const X3DField& f) {
		value = unwrap(f);
		return *this;
	}
	inline const SFNode<N>& operator=(const SFNode<N>& f) {
		value = f.value;
		return *this;
	}
};

#endif // #ifndef _X3D_SFNODE_H_
