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

#ifndef _X3D_ERRORS_H_
#define _X3D_ERRORS_H_

#include <stdexcept>
#include <string>

namespace X3D {

class SAIField;

/**
 * Root class for X3D exceptions.
 */
class X3DError : public std::runtime_error {
public:
	/**
	 * Constructor.
	 * 
	 * @param message error message
	 */
	X3DError(const char* message) : std::runtime_error(message) {}

	/**
	 * Constructor (takes std::string rather than char*).
	 * 
	 * @param message error message
	 */
	X3DError(const std::string& message) : std::runtime_error(message) {}
};

class EventLoopError : public X3DError {
protected:
    SAIField* const field;

public:
    EventLoopError(SAIField* field) : X3DError("event loop detected"), field(field) {}
};

class X3DParserError : public X3DError {
public:
    X3DParserError(const std::string& message) : X3DError(message) {}
};

}

#endif // #ifndef _X3D_ERRORS_H_
