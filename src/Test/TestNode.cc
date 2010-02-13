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

#include "internal/Browser.h"
#include "Test/Expect.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

namespace X3D {
namespace Test {

TestNode::~TestNode() {
}

const string& TestNode::defaultContainerField() {
    static string field = "tests";
    return field;
}

void TestNode::setup() {
    continuous(false);
    timeout(0);
    should("pass");
}

bool TestNode::parseSpecial(xmlNode* xml, const string& filename) {
    // TODO: might call base Script parseSpecial here?
    // if it's not an expect declaration, we're not interested
    if (strcmp("expect", (char*) xml->name))
        return false;
    // get the expect field (required)
    char* field = (char*) xmlGetProp(xml, (xmlChar*) "field");
    if (field == NULL)
        throw X3DParserError("missing expect field", filename, xml);
    // get the value (required)
    char* value = (char*) xmlGetProp(xml, (xmlChar*) "value");
    if (value == NULL)
        throw X3DParserError("missing expect value", filename, xml);
    // get the time (required)
    double time = -1;
    char* timeStr = (char*) xmlGetProp(xml, (xmlChar*) "time");
    if (timeStr == NULL)
        throw X3DParserError("missing expect time", filename, xml);
    time = atof(timeStr);
    // create the expectation field
    Expect* expect = new Expect(this, field, value, time);
    // clean up some memory
    xmlFree((xmlChar*) value);
    xmlFree((xmlChar*) field);
    xmlFree((xmlChar*) timeStr);
    // add the expect
    expects.push_back(expect);
    expect->predict();
    return true;
}

bool TestNode::runTest() {
    string reason;
    list<Expect*>::iterator it;
    list<string> fails;

    // run the simulation to completion
    while (browser()->simulate())
        ; // cout << "TICK: " << browser()->now() << endl;

    int passed = 0;
    bool result;
    bool shouldPass = (should() == "pass");

    // run the expectations
    for (it = expects.begin(); it != expects.end(); it++) {
        result = (*it)->test(&reason);
        if (shouldPass) {
            if (result)
                passed++;
            else
                reasons().add(reason);
        } else if (!result) {
            fails.push_back(reason);
        }
    }

    // check expected failures
    if (!shouldPass) {
        const MFString& expected = failWith();
        // should have failed but didn't
        if (fails.empty()) {
            reasons().add("expected failure(s), but passed instead");
        // failure reasons were given
        } else if (!expected.empty()) {
            // wrong number of failures
            if (fails.size() != expected.size()) {
                std::ostringstream os;
                os << "incorrect number of failures: "
                   << "expected " << expected.size() << ", "
                   << "but was " << fails.size();
                reasons().add(os.str());
            // check failure reasons
            } else {
                list<string>::iterator r_it = fails.begin();
                MFStringList::const_iterator e_it = expected.begin();
                for (; r_it != fails.end(); r_it++, e_it++) {
                    if (*e_it != *r_it) {
                        std::ostringstream os;
                        os << "failed for wrong reason: "
                           << "expected '" << *e_it << "', "
                           << "but was '" << *r_it << "'";
                        reasons().add(os.str());
                    }
                }
            }
        }
    }

    // determine overall success
    if (reasons().empty()) {
        success(true);
    } else {
        success(false);
        reasons.changed();
    }

    return success();
}

}}
