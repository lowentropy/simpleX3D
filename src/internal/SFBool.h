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

#ifndef _X3D_SFBOOL_H_
#define _X3D_SFBOOL_H_

#include "internal/X3DField.h"

namespace X3D {

class SFBool : public X3DField {
public:
	typedef bool TYPE;
    typedef bool CONST_TYPE;
	bool value;

	inline X3DField::Type getType() const { return X3DField::SFBOOL; }
	inline string getTypeName() const { return "SFBool"; }

	inline SFBool() : value(0) {}
	inline SFBool(bool x) : value(x) {}
	inline bool operator()() { return value; }

	inline static bool unwrap(const X3DField& f) {
		if (f.getType() != SFBOOL)
			throw X3DError("base type mismatch");
		return (static_cast<const SFBool&>(f)).value;
	}

	inline const SFBool& operator=(bool x) { value = x; return *this; }
	inline const SFBool& operator=(const X3DField& f) {
		value = unwrap(f);
		return *this;
	}
	inline const SFBool& operator=(const SFBool& f) {
		value = f.value;
		return *this;
	}
};

}

#endif // #ifndef _X3D_SFBOOL_H_
