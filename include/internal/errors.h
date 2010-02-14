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
#include <libxml/tree.h>
#include <sstream>

// XXX
#include <iostream>
using std::cout;
using std::endl;

using std::string;

namespace X3D {

class SAIField;
class Node;

/**
 * Root class for X3D exceptions.
 */
class X3DError : public std::exception {
protected:
    string fullError;
    string message;
    const Node* node;
public:
    X3DError() : message("<no message set>"), node(NULL) {
        constructError();
    }
	X3DError(const std::string& message) : message(message), node(NULL) {
        constructError();
    }
	X3DError(const std::string& message, const Node* node) : message(message), node(node) {
        constructError();
    }
    void constructError();
    virtual ~X3DError() throw () {}
    const char* what() const throw ();
};

class EventLoopError : public X3DError {
public:
    const SAIField* const field;
    EventLoopError(SAIField* field) : X3DError("event loop detected"), field(field) {}
};

class X3DParserError : public X3DError {
private:
    xmlNode* xml;
    string filename;
public:
    X3DParserError(const std::string& message, const string& filename, xmlNode* xml=NULL)
        : X3DError(), filename(filename), xml(xml) {
        std::stringstream ss;
        bool any = false;
        if (!filename.empty()) {
            ss << filename << ":";
            any = true;
        }
        if (xml != NULL) {
            ss << xmlGetLineNo(xml) << ":";
            any = true;
        }
        if (any)
            ss << " ";
        ss << message;
        this->message = ss.str();
        constructError(); // XXX duplicate...
    }
    virtual ~X3DParserError() throw () {}
};

}

#endif // #ifndef _X3D_ERRORS_H_
