#include "Test/Expect.h"

#include <iostream>
#include <sstream>

namespace X3D {
namespace Test {

TestNode::~TestNode() {
    map<string,Expect*>::const_iterator it;
    for (it = expects.begin(); it != expects.end(); it++)
        delete it->second;
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

SAIField* TestNode::getField(const string& name) {
    if (expects.count(name)) {
        return expects[name];
    } else {
        return this->Node::getField(name);
    }
}

bool TestNode::parseSpecial(xmlNode* xml, const string& filename) {
    // TODO: might call base Script parseSpecial here?
    // if it's not an expect declaration, we're not interested
    if (strcmp("expect", (char*) xml->name))
        return false;
    // get the expect type (required)
    char* type = (char*) xmlGetProp(xml, (xmlChar*) "type");
    if (type == NULL)
        throw X3DParserError("missing expect type", filename, xml);
    // get the expect name (required)
    char* name = (char*) xmlGetProp(xml, (xmlChar*) "name");
    if (name == NULL)
        throw X3DParserError("missing expect type", filename, xml);
    // get the value (optional)
    char* value = (char*) xmlGetProp(xml, (xmlChar*) "value");
    // create the expectation field
    Expect* expect = new Expect(this, type, name, value ? value : "");
    // clean up some memory
    if (value != NULL)
        xmlFree((xmlChar*) value);
    xmlFree((xmlChar*) type);
    xmlFree((xmlChar*) name);
    // add the expect
    expects[expect->name] = expect;
    return true;
}

bool TestNode::runTest() {
    string reason;
    map<string,Expect*>::iterator it;
    list<string> fails;

    int passed = 0;
    bool result;
    bool shouldPass = (should() == "pass");

    // run the expectations
    for (it = expects.begin(); it != expects.end(); it++) {
        result = it->second->test(&reason);
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
        const list<string>& expected = failWith().getElements();
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
                list<string>::const_iterator e_it = expected.begin();
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
    if (reasons().getElements().empty()) {
        success(true);
    } else {
        success(false);
        reasons.changed();
    }

    return success();
}

}}
