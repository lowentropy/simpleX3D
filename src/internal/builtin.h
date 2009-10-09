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

#ifndef _X3D_BUILTIN_H_
#define _X3D_BUILTIN_H_

#include <string>
#include "internal/profile.h"
#include "internal/Node.h"
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

/**
 * Contains a single function which initializes all the
 * X3D types implemented by simpleX3D.
 */
class Builtin {
public:

	/**
	 * Initialize the given profile with known types.
	 * 
	 * @param profile built-in supported profile
	 */
	static void init(Profile* profile) {
		// Core component
		Component* core = profile->createComponent("Core");
		{
			using namespace X3D::Core;

			// X3DNode
			NodeDefinitionImpl<X3DNode>* node =
				core->createNode<X3DNode>("X3DNode", true);
			{
				// SFNode [in,out] metadata NULL [X3DMetadataObject]
				node->createInputOutputField(
					"metadata", SFNodeType,
					&X3DNode::metadata);			// last set value
			}

			// X3DChildNode : X3DNode
			NodeDefinition* child =
				core->createNode<X3DChildNode>("X3DChildNode", true);
			{
				child->inherits("X3DNode");
			}

			// X3DBindableNode : X3DChildNode
			NodeDefinitionImpl<X3DBindableNode>* bind =
				core->createNode<X3DBindableNode>("X3DBindableNode", true);
			{
				bind->inherits("X3DChildNode");

				// SFBool [in] set_bind
				bind->createInputField(
					"set_bind", SFBoolType,
					&X3DBindableNode::set_bind);	// input action

				// SFTime [out] bindTime
				bind->createOutputField(
					"bindTime", SFTimeType,
					&X3DBindableNode::bindTime);	// last set value

				// SFBool [out] isBound
				bind->createOutputField(
					"isBound", SFBoolType,
					&X3DBindableNode::isBound,			// last set value
					&X3DBindableNode::isBound_changed);	// output action
			}

			// X3DInfoNode : X3DChildNode
			NodeDefinition* info =
				core->createNode<X3DInfoNode>("X3DInfoNode", true);
			{
				info->inherits("X3DChildNode");
			}

			// X3DMetadataObject
			NodeDefinitionImpl<X3DMetadataObject>* meta_obj =
				core->createNode<X3DMetadataObject>("X3DMetadataObject", true);
			{
				// XXX according to the spec, X3DMetadataObject is abstract
				meta_obj->inherits("X3DNode");

				// SFString [in,out] name ""
				meta_obj->createInputOutputField(
					"name", SFStringType,
					&X3DMetadataObject::name);		// last set value

				// SFString [in,out] reference ""
				meta_obj->createInputOutputField(
					"reference", SFStringType,
					&X3DMetadataObject::reference);	// last set value
			}

			// X3DPrototypeInstance : X3DNode
			NodeDefinition* prof_inst =
				core->createNode<X3DPrototypeInstance>("X3DPrototypeInstance", true);
			{
			}

			// X3DSensorNode : X3DChildNode
			NodeDefinitionImpl<X3DSensorNode>* sensor =
				core->createNode<X3DSensorNode>("X3DSensorNode", true);
			{
				sensor->inherits("X3DChildNode");

				// SFBool [in,out] enabled TRUE
				sensor->createInputOutputField<SFBool>(
					"enabled", SFBoolType,
					&X3DSensorNode::enabled,			// last set value
					&X3DSensorNode::set_enabled,		// input action (none)
					&X3DSensorNode::enabled_changed);	// output action

				// SFBool [out] isActive
				sensor->createOutputField(
					"isActive", SFBoolType,
					&X3DSensorNode::isActive,		// last set value
					&X3DSensorNode::on_isActive);	// output action
			}

			// MetadataDouble : X3DNode, X3DMetadataObject
			NodeDefinitionImpl<MetadataDouble>* meta_double =
				core->createNode<MetadataDouble>("MetadataDouble");
			{
	//			meta_double->inherits("X3DNode");
				meta_double->inherits("X3DMetadataObject");

				// MFDouble [in,out] value []
				meta_double->createInputOutputField(
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
				meta_float->createInputOutputField(
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
				meta_int->createInputOutputField(
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
				meta_set->createInputOutputField(
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
				meta_str->createInputOutputField(
					"value", MFStringType,
					&MetadataString::value);		// last set value
			}

			// WorldInfo : X3DInfoNode
			NodeDefinitionImpl<WorldInfo>* world =
				core->createNode<WorldInfo>("WorldInfo");
			{
				world->inherits("X3DInfoNode");
				
				// MFString [] info []
				world->createInitField(
					"info", MFStringType,
					&WorldInfo::info);				// last set value

				// SFString [] title ""
				world->createInitField(
					"title", SFStringType,
					&WorldInfo::title);				// last set value
			}
		} // end of Core component
	} // end of profile
};

}

#endif // #ifndef _X3D_BUILTIN_H_
