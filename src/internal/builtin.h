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
#include "internal/Profile.h"
#include "internal/Component.h"
#include "internal/NodeDef.h"
#include "internal/FieldDef.h"
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
#include "Time/X3DTimeDependentNode.h"
#include "Time/TimeSensor.h"
#include "Test/TestSuite.h"
#include "Test/TestNode.h"

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
			NodeDefImpl<X3DNode>* node =
				core->createNode<X3DNode>("X3DNode", true);
			{
				// SFNode [in,out] metadata NULL [X3DMetadataObject]
				node->createField(
					"metadata", X3DField::SFNODE, SAIField::INPUT_OUTPUT,
					&X3DNode::metadata);
                node->finish();
			}

			// X3DChildNode : X3DNode
			NodeDef* child =
				core->createNode<X3DChildNode>("X3DChildNode", true);
			{
				child->inherits("X3DNode");
                child->finish();
			}

			// X3DBindableNode : X3DChildNode
			NodeDefImpl<X3DBindableNode>* bind =
				core->createNode<X3DBindableNode>("X3DBindableNode", true);
			{
				bind->inherits("X3DChildNode");

				// SFBool [in] set_bind
				bind->createField(
					"set_bind", X3DField::SFBOOL, SAIField::INPUT_ONLY,
					&X3DBindableNode::set_bind);

				// SFTime [out] bindTime
				bind->createField(
					"bindTime", X3DField::SFTIME, SAIField::OUTPUT_ONLY,
					&X3DBindableNode::bindTime);

				// SFBool [out] isBound
				bind->createField(
					"isBound", X3DField::SFBOOL, SAIField::OUTPUT_ONLY,
					&X3DBindableNode::isBound);

                bind->finish();
			}

			// X3DInfoNode : X3DChildNode
			NodeDef* info =
				core->createNode<X3DInfoNode>("X3DInfoNode", true);
			{
				info->inherits("X3DChildNode");
                info->finish();
			}

			// X3DMetadataObject
			NodeDefImpl<X3DMetadataObject>* meta_obj =
				core->createNode<X3DMetadataObject>("X3DMetadataObject", true);
			{
				// SFString [in,out] name ""
				meta_obj->createField(
					"name", X3DField::SFSTRING, SAIField::INPUT_OUTPUT,
					&X3DMetadataObject::name);

				// SFString [in,out] reference ""
				meta_obj->createField(
					"reference", X3DField::SFSTRING, SAIField::INPUT_OUTPUT,
					&X3DMetadataObject::reference);

                meta_obj->finish();
			}

			// X3DPrototypeInstance : X3DNode
			NodeDef* prof_inst =
				core->createNode<X3DPrototypeInstance>("X3DPrototypeInstance", true);
			{
                prof_inst->inherits("X3DNode");
                prof_inst->finish();
			}

			// X3DSensorNode : X3DChildNode
			NodeDefImpl<X3DSensorNode>* sensor =
				core->createNode<X3DSensorNode>("X3DSensorNode", true);
			{
				sensor->inherits("X3DChildNode");

				// SFBool [in,out] enabled TRUE
				sensor->createField(
					"enabled", X3DField::SFBOOL, SAIField::INPUT_OUTPUT,
					&X3DSensorNode::enabled);

				// SFBool [out] isActive
				sensor->createField(
					"isActive", X3DField::SFBOOL, SAIField::OUTPUT_ONLY,
					&X3DSensorNode::isActive);

                sensor->finish();
			}

			// MetadataDouble : X3DNode, X3DMetadataObject
			NodeDefImpl<MetadataDouble>* meta_double =
				core->createNode<MetadataDouble>("MetadataDouble");
			{
				meta_double->inherits("X3DNode");
				meta_double->inherits("X3DMetadataObject");

				// X3DField::MFDouble [in,out] value []
				meta_double->createField(
					"value", X3DField::MFDOUBLE, SAIField::INPUT_OUTPUT,
					&MetadataDouble::value);

                meta_double->finish();
			}

			// MetadataFloat : X3DNode, X3DMetadataObject
			NodeDefImpl<MetadataFloat>* meta_float =
				core->createNode<MetadataFloat>("MetadataFloat");
			{
				meta_float->inherits("X3DNode");
				meta_float->inherits("X3DMetadataObject");

				// X3DField::MFFloat [in,out] value []
				meta_float->createField(
					"value", X3DField::MFFLOAT, SAIField::INPUT_OUTPUT,
					&MetadataFloat::value);

                meta_float->finish();
			}

			// MetadataInteger : X3DNode, X3DMetadataObject
			NodeDefImpl<MetadataInteger>* meta_int =
				core->createNode<MetadataInteger>("MetadataInteger");
			{
				meta_int->inherits("X3DNode");
				meta_int->inherits("X3DMetadataObject");

				// X3DField::MFInteger [in,out] value []
				meta_int->createField(
					"value", X3DField::MFINT32, SAIField::INPUT_OUTPUT,
					&MetadataInteger::value);

                meta_int->finish();
			}

			// MetadataSet : X3DNode, X3DMetadataObject
			NodeDefImpl<MetadataSet>* meta_set =
				core->createNode<MetadataSet>("MetadataSet");
			{
				meta_set->inherits("X3DNode");
				meta_set->inherits("X3DMetadataObject");

				// X3DField::MFNode [in,out] value [] [X3DMetadataObject]
				meta_set->createField(
					"value", X3DField::MFNODE, SAIField::INPUT_OUTPUT,
					&MetadataSet::value);

                meta_set->finish();
			}

			// MetadataString : X3DNode, X3DMetadataObject
			NodeDefImpl<MetadataString>* meta_str =
				core->createNode<MetadataString>("MetadataString");
			{
				meta_str->inherits("X3DNode");
				meta_str->inherits("X3DMetadataObject");

				// X3DField::MFString [in,out] value []
				meta_str->createField(
					"value", X3DField::MFSTRING, SAIField::INPUT_OUTPUT,
					&MetadataString::value);

                meta_str->finish();
			}

			// WorldInfo : X3DInfoNode
			NodeDefImpl<WorldInfo>* world =
				core->createNode<WorldInfo>("WorldInfo");
			{
				world->inherits("X3DInfoNode");
				
				// X3DField::MFString [] info []
				world->createField(
					"info", X3DField::MFSTRING, SAIField::INIT_ONLY,
					&WorldInfo::info);

				// SFString [] title ""
				world->createField(
					"title", X3DField::SFSTRING, SAIField::INIT_ONLY,
					&WorldInfo::title);

                world->finish();
			}
		} // end of Core component

		Component* time = profile->createComponent("Time");
		{
			using namespace Time;

			NodeDefImpl<X3DTimeDependentNode>* dep =
				time->createNode<X3DTimeDependentNode>("X3DTimeDependentNode", true);
			{
                dep->inherits("X3DChildNode");

				// SFBool [in,out] loop FALSE
				dep->createField(
					"loop", X3DField::SFBOOL, SAIField::INPUT_OUTPUT,
					&X3DTimeDependentNode::loop);

				// SFTime [in,out] pauseTime 0
				dep->createField(
					"pauseTime", X3DField::SFTIME, SAIField::INPUT_OUTPUT,
					&X3DTimeDependentNode::pauseTime);

				// SFTime [in,out] resumeTime 0
				dep->createField(
					"resumeTime", X3DField::SFTIME, SAIField::INPUT_OUTPUT,
					&X3DTimeDependentNode::resumeTime);

				// SFTime [in,out] startTime 0
				dep->createField(
					"startTime", X3DField::SFTIME, SAIField::INPUT_OUTPUT,
					&X3DTimeDependentNode::startTime);

				// SFTime [in,out] stopTime 0
				dep->createField(
					"stopTime", X3DField::SFTIME, SAIField::INPUT_OUTPUT,
					&X3DTimeDependentNode::stopTime);

				// SFTime [out] elapsedTime
				dep->createField(
					"elapsedTime", X3DField::SFTIME, SAIField::OUTPUT_ONLY,
					&X3DTimeDependentNode::elapsedTime);

				// SFBool [out] isActive
                /* // NOTE: conflicts with X3DSensorNode::isActive
				dep->createField(
					"isActive", X3DField::SFBOOL, SAIField::OUTPUT_ONLY,
					&X3DTimeDependentNode::isActive);
                */

				// SFBool [out] isPaused
				dep->createField(
					"isPaused", X3DField::SFBOOL, SAIField::OUTPUT_ONLY,
					&X3DTimeDependentNode::isPaused);

                dep->finish();
			}

			NodeDefImpl<TimeSensor>* ts =
				time->createNode<TimeSensor>("TimeSensor");
			{
                ts->inherits("X3DTimeDependentNode");
                ts->inherits("X3DSensorNode");

				// SFTime [in,out] cycleInterval 1
				ts->createField(
					"cycleInterval", X3DField::SFTIME, SAIField::INPUT_OUTPUT,
					&TimeSensor::cycleInterval);

				// SFTime [out] cycleTime
				ts->createField(
					"cycleTime", X3DField::SFTIME, SAIField::OUTPUT_ONLY,
					&TimeSensor::cycleTime);

				// SFFloat [out] fraction_changed
				ts->createField(
					"fraction_changed", X3DField::SFFLOAT, SAIField::OUTPUT_ONLY,
					&TimeSensor::fraction_changed);

				// SFTime [out] time
				ts->createField(
					"time", X3DField::SFTIME, SAIField::OUTPUT_ONLY,
					&TimeSensor::time);

                ts->finish();
			}
		}
		// Test component
		Component* test = profile->createComponent("Test");
		{
			using namespace X3D::Test;

			// TestSuite
			NodeDefImpl<TestSuite>* ts =
				test->createNode<TestSuite>("TestSuite");
            {
                ts->inherits("X3DNode");

                // SFString [] name
                ts->createField(
                    "name", X3DField::SFSTRING, SAIField::INIT_ONLY,
                    &TestSuite::name);
    
                // MFNode [] tests
                ts->createField(
                    "tests", X3DField::MFNODE, SAIField::INIT_ONLY,
                    &TestSuite::tests);

                // MFNode [out] passed
                ts->createField(
                    "passed", X3DField::MFNODE, SAIField::OUTPUT_ONLY,
                    &TestSuite::passed);

                // MFNode [out] failed
                ts->createField(
                    "failed", X3DField::MFNODE, SAIField::OUTPUT_ONLY,
                    &TestSuite::failed);

                // SFInt32 [out] numPassed
                ts->createField(
                    "numPassed", X3DField::MFNODE, SAIField::OUTPUT_ONLY,
                    &TestSuite::numPassed);

                // SFInt32 [out] numFailed
                ts->createField(
                    "numFailed", X3DField::MFNODE, SAIField::OUTPUT_ONLY,
                    &TestSuite::numFailed);

                ts->finish();
            }

            // TestNode
            NodeDefImpl<TestNode>* tn =
                test->createNode<TestNode>("Test");
            {
                tn->inherits("X3DChildNode");

                // SFString [] name
                tn->createField(
                    "name", X3DField::SFSTRING, SAIField::INIT_ONLY,
                    &TestNode::name);

                // SFBool [] continuous (false)
                tn->createField(
                    "continuous", X3DField::SFBOOL, SAIField::INIT_ONLY,
                    &TestNode::continuous);

                // SFTime [] timeout (0)
                tn->createField(
                    "timeout", X3DField::SFTIME, SAIField::INIT_ONLY,
                    &TestNode::timeout);

                // SFBool [out] success
                tn->createField(
                    "success", X3DField::SFBOOL, SAIField::OUTPUT_ONLY,
                    &TestNode::success);

                // MFString [out] reasons
                tn->createField(
                    "reasons", X3DField::MFSTRING, SAIField::OUTPUT_ONLY,
                    &TestNode::reasons);

                tn->finish();
            }
        }
	} // end of profile
};

}

#endif // #ifndef _X3D_BUILTIN_H_
