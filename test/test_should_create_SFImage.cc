#include "types.h"
#include <assert.h>

int main(int argc, char** argv) {
	SFImage* image = new SFImage(0,0,0);
	assert(image->bytes == NULL);
	delete image;
	return 0;
}
