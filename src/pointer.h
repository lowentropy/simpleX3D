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

#ifndef _X3D_POINTER_H_
#define _X3D_POINTER_H_

#include <typeinfo>
#include <sstream>
#include "errors.h"

namespace X3D {

class SafePointer {
private:
	const std::type_info* type;
public:
	const void* const ptr;
	template <typename T> SafePointer(const T& value) : ptr(&value), type(&typeid(T)) {}
	template <typename T> SafePointer(T* const ptr) : ptr(ptr), type(&typeid(T)) {}
	template <typename T> T* const cast() const {
#if SAFE_POINTER
		if (type != &typeid(T)) {
			std::ostringstream os;
			os << "bad cast from " << type->name() << " to " << typeid(T).name();
			throw X3DError(os.str().c_str());
		}
#endif
		return (T* const) ptr;
	}
};

}

#endif // #ifndef _X3D_POINTER_H_
