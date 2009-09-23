#ifndef _X3D_MACROS_H_
#define _X3D_MACROS_H_

#define X3D_BEGIN_NODE(name) \
	private: \
		/**
		   Runtime definition of node type,
		   containing its name and fields.
		  */ \
		X3D::NodeDefinition* definition; \
	public: \
		/**
		   Static initializer for name.
		   
		   Registers the name node type with X3D, and sets the
		   #definition variable.
		 */ \
		static void init() { \
			definition = new X3D::NodeDefinition(#name);

#define X3D_FIELD_IN(name) definition->addInputField(#name, &##name);
#define X3D_FIELD_VAR(name) definition->addVariableField(#name, &get_##name);
#define X3D_FIELD_OUT(name) definition->addOutputField(#name, &##name);

#define X3D_END_NODE }

#define X3D_INIT(type, name) \
	/** Initialize-only type field. */ \
	public: type name;

#define X3D_IN(type, name) \
	protected: \
		/**
		   Default virtual action to take on the
		   name input event.

		   @param value type value received with event
		 */ \
		virtual void on_##name(type value) {} \
	public: \
		/**
		   Trigger the input event with the given value.
		   The body of this function should call the virtual
		   function #on_##name.

		   @param value type value received with this event
		 */ \
		void name(type value)

#define X3D_IN_ABSTRACT(type, name) \
	protected: \
		/**
		   Abstract action to take on the
		   name input event. Implementors MUST
		   provide this function.

		   @param value type value received with event
		 */ \
		virtual on_##name(type, value) = 0; \
	public: \
		/**
		   Trigger the input event with the given value.
		   The body of this function should call the abstract
		   function #on_##name.

		   @param value type value received with event
		 */ \
		void name(type value)

#define X3D_OUT(type, name) \
	public: \
		/**
		   Trigger the output event with the given value.
		   This function automatically calls the virtual function
		   #on_##name with the new value, sets the output variable,
		   and then queues an event for any routes connected to this
		   field.

		   @param value type value saved and sent with event
		 */ \
		void name(type value) { \
			on_##name(value); \
			name = value; \
			output(#name, value); } \
	protected: \
		/**
		   Default virtual action to take on the
		   name output event.
           
		   @param value new type value of name
		 */ \
		virtual void on_##name(type value) {}

#define X3D_OUT_ABSTRACT(type, name) \
	public: \
		/**
		   Trigger the output event with the given value.
		   This function automatically calls the abstract function
		   #on_##name with the new value, sets the output variable,
		   and then queues an event for any routes connected to this
		   field.

		   @param value type value saved and sent with event
		 */ \
		void name(type value) { \
			on_##name(value); \
			name = value; \
			output(#name, value); } \
	protected: \
		 /**
		    Abstract action to take on the
		    name output event. Implementors MUST
		    provide this function.
		  
		    @param value new type value of name
		  */ \
		virtual void on_##name(type value) = 0;

#define X3D_OUT_CUSTOM(type, name) \
	protected: \
		/**
		   Default virtual action to take on the
		   name output event.
           
		   @param value new type value of name
		 */ \
		virtual void on_##name(type value) {} \
	public: \
		/**
		   Trigger the output event with the given value.
		   This function should call the virtual function
		   #on_##name with the new value BEFORE setting the
		   output variable, and then queue an event for any
		   routes connectd to this field.

		   @param value type value saved and sent with event
		 */ \
		void name(type value)

#define X3D_OUT_CUSTOM_ABSTRACT(type, name) \
	protected: \
		 /**
		    Abstract action to take on the
		    name output event. Implementors MUST
		    provide this function.
		  
		    @param value new type value of name
		  */ \
		virtual void on_##name(type value) = 0; \
	public: \
		/**
		   Trigger the output event with the given value.
		   This function should call the abstract function
		   #on_##name with the new value BEFORE setting the
		   output variable, and then queue an event for any
		   routes connectd to this field.

		   @param value type value saved and sent with event
		 */ \
		void name(type value)

#define X3D_INOUT(type, name) \
	/** Holds the last value sent to name##_changed() */ \
	public: type name; \
	public: \
		/**
		   Simply calls name##_changed() with the input value.
		   
		   @param value type value received with event
		 */ \
		void set_##name(type value) { name##_changed(value); } \
	public: \
		/**
		   Trigger the output event with the given value.
		   This function automatically calls the virtual function
		   #on_##name##_changed with the new value, sets the output variable,
		   and then queues an event for any routes connected to this
		   field.

		   @param value type value saved and sent with event
		 */ \
		void name##_changed(type value) { \
			on_##name##_changed(value); \
			name = value; output(#name, value); } \
	protected: \
		/**
		   Default virtual action to take on the
		   name output event.
           
		   @param value new type value of name
		 */ \
		virtual void on_##name##_changed(type value) {}

#define X3D_INOUT_ABSTRACT(type, name) \
	/** Holds the last value sent to name##_changed() */ \
	public: type name; \
	public: \
		/**
		   Simply calls name##_changed() with the input value.
		   
		   @param value type value received with event
		 */ \
		void set_##name(type value) { name##_changed(value); } \
	public: \
		/**
		   Trigger the output event with the given value.
		   This function automatically calls the abstract function
		   #on_##name##_changed with the new value, sets the output variable,
		   and then queues an event for any routes connected to this
		   field.

		   @param value type value saved and sent with event
		 */ \
		void name##_changed(type value) { \
			on_##name##_changed(value); \
			name = value; output(#name, value); } \
	protected: \
		 /**
		    Abstract action to take on the
		    name output event. Implementors MUST
		    provide this function.
		  
		    @param value new type value of name
		  */ \
		virtual void on_##name##_changed(type value) = 0;

#define X3D_INOUT_CUSTOM(type, name) \
	/** Holds the last value sent to name##_changed() */ \
	public: type name; \
	public: \
		/**
		   Simply calls name##_changed() with the input value.
		   
		   @param value type value received with event
		 */ \
		void set_##name(type value) { name##_changed(value); } \
	protected: \
		/**
		   Default virtual action to take on the
		   name output event.
           
		   @param value new type value of name
		 */ \
		virtual void on_##name##_changed(type value) {} \
	public: \
		/**
		   Trigger the output event with the given value.
		   This function should call the virtual function
		   #on_##name##_changed with the new value BEFORE setting the
		   output variable, and then queue an event for any
		   routes connectd to this field.

		   @param value type value saved and sent with event
		 */ \
		void name##_changed(type value)

#define X3D_INOUT_CUSTOM_ABSTRACT(type, name) \
	/** Holds the last value sent to name##_changed() */ \
	public: type name; \
	public: \
		/**
		   Simply calls name##_changed() with the input value.
		   
		   @param value type value received with event
		 */ \
		void set_##name(type value) { name##_changed(value); } \
	protected: \
		 /**
		    Abstract action to take on the
		    name output event. Implementors MUST
		    provide this function.
		   
		    @param value new type value of name
		  */ \
		virtual void on_##name##_changed(type value) = 0; \
	public: \
		/**
		   Trigger the output event with the given value.
		   This function should call the abstract function
		   #on_##name##_changed with the new value BEFORE setting the
		   output variable, and then queue an event for any
		   routes connectd to this field.

		   @param value type value saved and sent with event
		 */ \
		void name##_changed(type value)

#endif // #ifndef _X3D_MACROS_H_
