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

#include "internal/config.h"
#include "internal/errors.h"
#include "internal/SafePointer.h"
#include <string>

using std::string;

namespace X3D {

// forward declarations
class NodeDefinition;
class Browser;

class Node {
public:
	typedef enum {
		CREATION,
		SETUP,
		REALIZED,
		DISPOSED
	} Stage;

protected:
	NodeDefinition* definition;
	Stage stage;

private:
	Node(const Node& node) {}

public:
	Node() : stage(SETUP) {}
	virtual ~Node() {}

	Stage getStage() const { return stage; }
	bool realized() const { return stage == REALIZED; }
	void realize() { stage = REALIZED; }

	/**
	 * Return a reference to the browser. This is a helper function
	 * that simply calls Browser::getSingleton.
	 * 
	 * @returns singleton instance of Browser
	 */
	virtual Browser* browser();

	template <class T> const T* cast() const {
		const T* node = dynamic_cast<const T*>(this);
		if (node == NULL)
			throw X3DError("illegal node cast");
		return node;
	}

	template <class T> T* cast() {
		T* node = dynamic_cast<T*>(this);
		if (node == NULL)
			throw X3DError("illegal node cast");
		return node;
	}
};

}

#endif // #ifndef _X3D_NODE_H_
