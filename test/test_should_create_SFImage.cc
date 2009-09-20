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
