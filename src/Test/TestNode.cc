#include "Test/TestNode.h"
#include "Test/Expect.h"

// XXX
#include <iostream>
using std::cout;
using std::endl;

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
    int passed = 0;
    for (it = expects.begin(); it != expects.end(); it++) {
        if (it->second->test(&reason))
            passed++;
        else
            reasons().add(reason);
    }
    success(passed == expects.size());
    if (!success())
        reasons.changed();
    return success();
}

}}
