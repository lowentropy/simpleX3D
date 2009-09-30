#include <string>
#include "profile.h"
#include "Core/X3DNode.h"
#include "Core/X3DChildNode.h"
#include "Core/X3DBindableNode.h"
#include "Core/X3DInfoNode.h"
#include "Core/X3DMetadataObject.h"
#include "Core/X3DPrototypeInstance.h"
#include "Core/X3DSensorNode.h"
#include "Core/MetadataDouble.h"
#include "Core/MetadataFloat.h"
#include "Core/MetadataInteger.h"
#include "Core/MetadataSet.h"
#include "Core/MetadataString.h"
#include "Core/WorldInfo.h"

namespace X3D {

void foo() {
	Profile profile;

	// Core component
	Component* core = profile.createComponent("Core");
	{
		using namespace X3D::Core;

		// X3DNode
		NodeDefinitionImpl<X3DNode>* node =
			core->createNode<X3DNode>("X3DNode");
		{
			// SFNode [in,out] metadata NULL [X3DMetadataObject]
			node->createInitField<const X3DMetadataObject*>(
				"metadata", SFNodeType,
				&X3DNode::metadata);			// last set value
		}

		// X3DChildNode : X3DNode
		NodeDefinition* child =
			core->createNode<X3DChildNode>("X3DChildNode");
		{
			child->inherits("X3DNode");
		}

		// X3DBindableNode : X3DChildNode
		NodeDefinitionImpl<X3DBindableNode>* bind =
			core->createNode<X3DBindableNode>("X3DBindableNode");
		{
			bind->inherits("X3DChildNode");

			// SFBool [in] set_bind
			bind->createInputField<SFBool>(
				"set_bind", SFBoolType,
				&X3DBindableNode::set_bind);	// input action

			// SFTime [out] bindTime
			bind->createOutputField<SFTime>(
				"bindTime", SFTimeType,
				&X3DBindableNode::bindTime);	// last set value

			// SFBool [out] isBound
			bind->createOutputField<SFBool>(
				"isBound", SFBoolType,
				&X3DBindableNode::isBound,		// last set value
				&X3DBindableNode::on_isBound);	// output action
		}

		// X3DInfoNode : X3DChildNode
		NodeDefinition* info =
			core->createNode<X3DInfoNode>("X3DInfoNode");
		{
			info->inherits("X3DChildNode");
		}

		// X3DMetadataObject
		NodeDefinitionImpl<X3DMetadataObject>* meta_obj =
			core->createNode<X3DMetadataObject>("X3DMetadataObject");
		{
			// XXX according to the spec, X3DMetadataObject is abstract
			meta_obj->inherits("X3DNode");

			// SFString [in,out] name ""
			meta_obj->createInputOutputField<SFString>(
				"name", SFStringType,
				&X3DMetadataObject::name);		// last set value

			// SFString [in,out] reference ""
			meta_obj->createInputOutputField<SFString>(
				"reference", SFStringType,
				&X3DMetadataObject::reference);	// last set value
		}

		// X3DPrototypeInstance : X3DNode
		NodeDefinition* prof_inst =
			core->createNode<X3DPrototypeInstance>("X3DPrototypeInstance");
		{
		}

		// X3DSensorNode : X3DChildNode
		NodeDefinitionImpl<X3DSensorNode>* sensor =
			core->createNode<X3DSensorNode>("X3DSensorNode");
		{
			sensor->inherits("X3DChildNode");

			// SFBool [in,out] enabled TRUE
			sensor->createInputOutputField<SFBool>(
				"enabled", SFBoolType,
				&X3DSensorNode::enabled,		// last set value
				NULL,							// input action (none)
				&X3DSensorNode::on_enabled);	// output action

			// SFBool [out] isActive
			sensor->createOutputField<SFBool>(
				"isActive", SFBoolType,
				&X3DSensorNode::active,			// last set value
				&X3DSensorNode::on_isActive);	// output action
		}

		// MetadataDouble : X3DNode, X3DMetadataObject
		NodeDefinitionImpl<MetadataDouble>* meta_double =
			core->createNode<MetadataDouble>("MetadataDouble");
		{
//			meta_double->inherits("X3DNode");
			meta_double->inherits("X3DMetadataObject");

			// MFDouble [in,out] value []
			meta_double->createInputOutputField<MFDouble>(
				"value", MFDoubleType,
				&MetadataDouble::value);		// last set value
		}

		// MetadataFloat : X3DNode, X3DMetadataObject
		NodeDefinitionImpl<MetadataFloat>* meta_float =
			core->createNode<MetadataFloat>("MetadataFloat");
		{
//			meta_float->inherits("X3DNode");
			meta_float->inherits("X3DMetadataObject");

			// MFFloat [in,out] value []
			meta_float->createInputOutputField<MFFloat>(
				"value", MFFloatType,
				&MetadataFloat::value);			// last set value
		}

		// MetadataInteger : X3DNode, X3DMetadataObject
		NodeDefinitionImpl<MetadataInteger>* meta_int =
			core->createNode<MetadataInteger>("MetadataInteger");
		{
//			meta_int->inherits("X3DNode");
			meta_int->inherits("X3DMetadataObject");

			// MFInteger [in,out] value []
			meta_int->createInputOutputField<MFInt32>(
				"value", MFInt32Type,
				&MetadataInteger::value);		// last set value
		}

		// MetadataSet : X3DNode, X3DMetadataObject
		NodeDefinitionImpl<MetadataSet>* meta_set =
			core->createNode<MetadataSet>("MetadataSet");
		{
//			meta_set->inherits("X3DNode");
			meta_set->inherits("X3DMetadataObject");

			// MFNode [in,out] value [] [X3DMetadataObject]
			meta_set->createInputOutputField<vector<X3DMetadataObject*> >(
				"value", MFNodeType,
				&MetadataSet::value);			// last set value
		}

		// MetadataString : X3DNode, X3DMetadataObject
		NodeDefinitionImpl<MetadataString>* meta_str =
			core->createNode<MetadataString>("MetadataString");
		{
//			meta_str->inherits("X3DNode");
			meta_str->inherits("X3DMetadataObject");

			// MFString [in,out] value []
			meta_str->createInputOutputField<MFString>(
				"value", MFStringType,
				&MetadataString::value);		// last set value
		}

		// WorldInfo : X3DInfoNode
		NodeDefinitionImpl<WorldInfo>* world =
			core->createNode<WorldInfo>("WorldInfo");
		{
			world->inherits("X3DInfoNode");
			
			// MFString [] info []
			world->createInitField<MFString>(
				"info", MFStringType,
				&WorldInfo::info);				// last set value

			// SFString [] title ""
			world->createInitField<SFString>(
				"title", SFStringType,
				&WorldInfo::title);				// last set value
		}
	} // end of Core component
} // end of profile

}
