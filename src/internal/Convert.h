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

#ifndef _X3D_CONVERT_H_
#define _X3D_CONVERT_H_

#include "internal/types.h"

namespace X3D {

class Convert {
public:

	static SFDouble toSFDouble(const string& str) {
		char* end = NULL;
		SFDouble value = strtod(str.c_str(), &end);
		if (end != NULL)
			throw X3DError("invalid conversion to SFDouble");
		return value;
	}

	static SFFloat toSFFloat(const string& str) {
		char* end = NULL;
		SFFloat value = strtof(str.c_str(), &end);
		if (end != NULL)
			throw X3DError("invalid conversion to SFFloat");
		return value;
	}

	static SFInt32 toSFInt32(const string& str) {
		char* end = NULL;
		SFInt32 value = strtoi(str.c_str(), &end);
		if (end != NULL)
			throw X3DError("invalid conversion to SFInt32");
	}

	static SFString toSFString(const string& str) {
		return str;
	}
};

}

#endif // #ifndef _X3D_CONVERT_H_
