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

#include "types.h"
#include <assert.h>
#include <stdio.h>

int main(int argc, char** argv) {
	SFImage* image = new SFImage(0,0,0);
	delete image;
	SFVec4d v(1,2,3,4);
	SFMatrix4f m;
	SFVec4f r(m * v);
	assert(r.x == 1);
	assert(r.y == 2);
	assert(r.z == 3);
	assert(r.w == 4);
	return 0;
}
