#ifndef _X3D_ERRORS_H_
#define _X3D_ERRORS_H_

#include "types.h"
#include <stdexcept>

class X3DError : public std::runtime_error {
public:
	X3DError(const char* message) : std::runtime_error(message) {}
};

#endif // #ifndef _X3D_ERRORS_H_
