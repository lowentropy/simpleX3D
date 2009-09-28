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

#ifndef _X3D_MACROS_H_
#define _X3D_MACROS_H_

#include "config.h"
#include "stubs.h"

#define X3D_NODE_HEADER \
	private: static NodeDefinition* definition;

#define X3D_INIT(node, type, name) \
	X3D_VAR(type, name, name)

#define X3D_IN(node, type, name) \
	protected: \
		/**
		   Default virtual action to take on the
		   name input event.

		   @param value type value received with event
		 */ \
		virtual void on_##name(type value) {} \
	X3D_IN_HEAD_CUSTOM(type, name) \
	X3D_IN_FIELD(node, type, name)

#define X3D_IN_ABSTRACT(node, type, name) \
	protected: \
		/**
		   Abstract action to take on the
		   name input event. Implementors MUST
		   provide this function.

		   @param value type value received with event
		 */ \
		virtual on_##name(type, value) = 0; \
	X3D_IN_HEAD_CUSTOM(type, name) \
	X3D_IN_FIELD(node, type, name)

#define X3D_OUT(node, type, name) \
	X3D_VAR(type, name, name) \
	X3D_OUT_HEAD_AUTO(type, name, name, virtual) \
	X3D_OUT_STUB_VIRTUAL(type, name, name) \
	X3D_OUT_FIELD(node, type, get_##name)

#define X3D_OUT_ABSTRACT(node, type, name) \
	X3D_VAR(type, name, name) \
	X3D_OUT_HEAD_AUTO(type, name, name, abstract) \
	X3D_OUT_STUB_ABSTRACT(type, name, name) \
	X3D_OUT_FIELD(node, type, get_##name)

#define X3D_OUT_CUSTOM(node, type, name) \
	X3D_VAR(type, name, name) \
	X3D_OUT_STUB_VIRTUAL(type, name, name) \
	X3D_OUT_HEAD_CUSTOM(type, name, name, virtual) \
	X3D_OUT_FIELD(node, type, get_##name)

#define X3D_OUT_CUSTOM_ABSTRACT(node, type, name) \
	X3D_VAR(type, name, name) \
	X3D_OUT_STUB_ABSTRACT(type, name, name) \
	X3D_OUT_HEAD_CUSTOM(type, name, name, abstract) \
	X3D_OUT_FIELD(node, type, get_##name)

#define X3D_INOUT(node, type, name) \
	X3D_VAR(type, name##_changed, name) \
	X3D_IN_HEAD_AUTO(type, name) \
	X3D_OUT_STUB_VIRTUAL(type, name##_changed, name) \
	X3D_OUT_HEAD_AUTO(type, name##_changed, name, virtual) \
	X3D_IN_FIELD(node, type, set_##name) \
	X3D_OUT_FIELD(node, type, get_##name)

#define X3D_INOUT_ABSTRACT(node, type, name) \
	X3D_VAR(type, name##_changed, name) \
	X3D_IN_HEAD_AUTO(type, name) \
	X3D_OUT_STUB_ABSTRACT(type, name##_changed, name) \
	X3D_OUT_HEAD_AUTO(type, name##_changed, name, abstract) \
	X3D_IN_FIELD(node, type, set_##name) \
	X3D_OUT_FIELD(node, type, get_##name)

#define X3D_INOUT_CUSTOM(node, type, name) \
	X3D_VAR(type, name##_changed, name) \
	X3D_IN_HEAD_AUTO(type, name) \
	X3D_OUT_STUB_VIRTUAL(type, name##_changed, name) \
	X3D_OUT_HEAD_CUSTOM(type, name##_changed, name, virtual) \
	X3D_IN_FIELD(node, type, set_##name) \
	X3D_OUT_FIELD(node, type, get_##name)

#define X3D_INOUT_CUSTOM_ABSTRACT(node, type, name) \
	X3D_VAR(type, name##_changed, name) \
	X3D_IN_HEAD_AUTO(type, name) \
	X3D_OUT_STUB_ABSTRACT(type, name##_changed, name) \
	X3D_OUT_HEAD_CUSTOM(type, name##_changed, name, abstract) \
	X3D_IN_FIELD(node, type, set_##name) \
	X3D_OUT_FIELD(node, type, get_##name)

#endif // #ifndef _X3D_MACROS_H_
