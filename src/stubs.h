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

#ifndef _X3D_STUBS_H_
#define _X3D_STUBS_H_

#define X3D_VAR(type, name, var) \
	/** Holds the last type value sent to name */ \
	protected: type _##var; \
	/**
	   Public accessor for _##var.

	   @returns value of _##var
	 */ \
	public: type get_##var() { return _##var; }

#define X3D_IN_HEAD_AUTO(type, name) \
	public: \
		/**
		   Simply calls name##_changed() with the input value.
		   
		   @param value type value received with event
		 */ \
		void set_##name(type value) { name##_changed(value); }

#define X3D_IN_HEAD_CUSTOM(type, name) \
	public: \
		/**
		   Trigger the input event with the given value.
		   The body of this function should call the virtual
		   function #on_##name.

		   @param value type value received with this event
		 */ \
		void name(type value)

#define X3D_OUT_HEAD_AUTO(type, name, var, subtype) \
	public: \
		/**
		   Trigger the output event with the given value.
		   This function automatically calls the subtype function
		   #on_##name with the new value, sets the output variable,
		   and then queues an event for any routes connected to this
		   field.

		   @param value type value saved and sent with event
		 */ \
		void name(type value) { \
			on_##name(value); \
			_##var = value; \
			output(#var, value); } \

#define X3D_OUT_HEAD_CUSTOM(type, name, var, subtype) \
	public: \
		/**
		   Trigger the output event with the given value.
		   This function should call the subtype function
		   #on_##name with the new value BEFORE setting the
		   output variable, and then queue an event for any
		   routes connectd to this field.

		   @param value type value saved and sent with event
		 */ \
		void name(type value)

#define X3D_OUT_STUB_VIRTUAL(type, name, var) \
	protected: \
		/**
		   Default virtual action to take on the
		   name output event.
           
		   @param value new type value of var
		 */ \
		virtual void on_##name(type value) {}

#define X3D_OUT_STUB_ABSTRACT(type, name, var) \
		 /**
		    Abstract action to take on the
		    name output event. Implementors MUST
		    provide this function.
		  
		    @param value new type value of var
		  */ \
		virtual void on_##name(type value) = 0;

#endif // #ifndef _X3D_STUBS_H_
