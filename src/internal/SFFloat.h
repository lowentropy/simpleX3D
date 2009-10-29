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

#ifndef _X3D_SFFLOAT_H_
#define _X3D_SFFLOAT_H_

#include "internal/X3DField.h"

namespace X3D {

class SFFloat : public X3DField {
public:
	typedef float TYPE;
	float value;

	inline X3DField::Type getType() const { return SFFLOAT; }
	inline string getTypeName() const { return "SFFloat"; }

	inline SFFloat() : value(0) {}
	inline SFFloat(float x) : value(x) {}
	inline float operator()() { return value; }

	inline static float unwrap(const X3DField& f) {
		if (f.getType() != SFFLOAT)
			throw X3DError("base type mismatch");
		return (static_cast<const SFFloat&>(f)).value;
	}

	inline const SFFloat& operator=(float x) { value = x; return *this; }
	inline const SFFloat& operator=(const X3DField& f) {
		value = unwrap(f);
		return *this;
	}
	inline const SFFloat& operator=(const SFFloat& f) {
		value = f.value;
		return *this;
	}
};

}

#endif // #ifndef _X3D_SFFLOAT_H_
