#ifndef _X3D_ERRORS_H_
#define _X3D_ERRORS_H_

#include "types.h"
#include <stdexcept>

/**
 * Root class for exceptions in simpleX3D.
 */
class X3DError : public std::runtime_error {
public:
	/**
	 * Constructor.
	 * 
	 * @param message error message
	 */
	X3DError(const char* message) : std::runtime_error(message) {}
};

#endif // #ifndef _X3D_ERRORS_H_
