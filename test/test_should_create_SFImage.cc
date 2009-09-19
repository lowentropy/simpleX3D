#include "types.h"
#include <assert.h>

int main(int argc, char** argv) {
	SFImage* image = new SFImage(0,0,0);
	delete image;
	SFVec2f a(1,2);
	SFVec2d b(2,4);
	a -= b;
	assert(b.x == 2);
	assert(b.y == 4);
	assert(a.x == -1);
	assert(a.y == -2);
	return 0;
}
