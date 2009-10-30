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

#ifndef _X3D_SFSTRING_H_
#define _X3D_SFSTRING_H_

#include "internal/X3DField.h"
#include <string>

using std::string;

namespace X3D {

class SFString : public X3DField {
public:
	typedef const string& TYPE;
	string value;

	inline X3DField::Type getType() const { return X3DField::SFSTRING; }
	inline string getTypeName() const { return "SFString"; }

	inline SFString() : value("") {}
	inline SFString(const string& init) : value(init) {}
	inline const string& operator()() { return value; }

	inline static const string& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::SFSTRING)
			throw X3DError("base type mismatch");
		return (static_cast<const SFString&>(f)).value;
	}

	inline const SFString& operator=(const string& x) {
		value = x;
		return *this;
	}
	inline const SFString& operator=(const X3DField& f) {
		value = unwrap(f);
		return *this;
	}
	inline const SFString& operator=(const SFString& f) {
		value = f.value;
		return *this;
	}
};

}

#endif // #ifndef _X3D_SFSTRING_H_
