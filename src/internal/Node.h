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

#ifndef _X3D_NODE_H_
#define _X3D_NODE_H_

#include "internal/errors.h"
#include "internal/types.h"
#include "internal/InitField.h"
#include "internal/InField.h"
#include "internal/OutField.h"
#include "internal/InOutField.h"
#include <string>

using std::string;

namespace X3D {

// forward declarations
class NodeDef;
class Browser;

/**
 * Base class for all abstract and concrete node types.
 * This class by itself doesn't do much except track the
 * node lifecycle.
 */
class Node {
friend class NodeDef;
public:
    /// Node lifcycle stage definitions
	typedef enum {
		CREATION,
		SETUP,
		REALIZED,
		DISPOSED
	} Stage;

protected:
    /// Definition of node, which may be a static definition or prototype definition
	NodeDef* definition;

    /// Current stage of node lifecycle
	Stage stage;

private:
    /// Disallow copy constructgor
	Node(const Node& node) { throw X3DError("illegal copy"); }

public:
    /// Empty constructor. Nodes start in stage SETUP.
	Node() : stage(SETUP) {}

    /// Virtual deconstructor.
	virtual ~Node() {}

    /// @returns current lifecycle stage
	Stage getStage() const { return stage; }

    /// @returns whether node is in REALIZED stage
	bool realized() const { return stage == REALIZED; }

    /// Moves the node to the REALIZED stage.
	void realize() { stage = REALIZED; }

    /**
     * Function to provide initialization AFTER the fields
     * have had their node pointer set, allowing us to set default
     * values on our fields. Don't make it virtual; it's provided
     * by contract rather than polymorphism.
     */
    void setup() {}

	/**
	 * Return a reference to the browser. This is a helper function
	 * that simply calls Browser::getSingleton.
	 * 
	 * @returns singleton instance of Browser
	 */
	virtual Browser* browser();
};

}

#endif // #ifndef _X3D_NODE_H_
