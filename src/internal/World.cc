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

#include "internal/World.h"

namespace X3D {

World::~World() {
    // do nothing?
}

World* World::read(Browser* browser, const char* filename) {
    World* world = new World(browser, filename, "", "", MFStringArray());
    xmlDoc* doc;
    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL)
        throw X3DError("failed to parse file");
    world->parseRoot(xmlDocGetRootElement(doc));
    xmlFreeDoc(doc);
    return world;
}

void World::parseRoot(xmlNode* xml) {
    if (xml->type != XML_ELEMENT_NODE ||
        strcmp("X3D", (char*) xml->name))
        throw X3DParserError("toplevel node should be <X3D>", filename, xml);
    for (xmlNode* child = xml->children; child != NULL; child = child->next) {
        if (child->type != XML_ELEMENT_NODE)
            continue;
        if (!strcmp("head", (char*) child->name)) {
            parseHead(child);
        } else if (!strcmp("Scene", (char*) child->name)) {
            parseScene(child, NULL);
        } else {
            throw X3DParserError(
                string("unexpected toplevel node: ")
                    + (char*) child->name, filename, child);
        }
    }
}

void World::parseHead(xmlNode* xml) {
    for (xmlNode* child = xml->children; child != NULL; child = child->next) {
        if (child->type != XML_ELEMENT_NODE)
            continue;
        if (!strcmp("component", (char*) child->name)) {
            parseComponent(child);
        } else if (!strcmp("meta", (char*) child->name)) {
            parseMeta(child);
        } else {
            throw X3DParserError(
                string("unexpected head node: ")
                    + (char*) child->name, filename, child);
        }
    }
}

void World::parseScene(xmlNode* xml, Node* node,
        vector<Node*>* nodes, vector<Connect>* connects) {
    for (xmlNode* child = xml->children; child != NULL; child = child->next) {
        if (child->type != XML_ELEMENT_NODE)
            continue;
        if ((node != NULL) && node->parseSpecial(child, filename)) {
            // do nothing
        } else if (!strcmp("ProtoDeclare", (char*) child->name)) {
            parseProtoDeclare(child);
        } else if (!strcmp("ExternProtoDeclare", (char*) child->name)) {
            parseExternProtoDeclare(child);
        } else if (!strcmp("ProtoInstance", (char*) child->name)) {
            parseProtoInstance(child, node);
        } else if (!strcmp("ROUTE", (char*) child->name)) {
            parseRoute(child);
        } else if (!strcmp("IMPORT", (char*) child->name)) {
            parseImport(child);
        } else if (!strcmp("EXPORT", (char*) child->name)) {
            parseExport(child);
        } else if (!strcmp("IS", (char*) child->name)) {
            parseConnects(child, node, connects);
        } else {
            parseNode(child, node, nodes);
        }
    }
}

void World::parseComponent(xmlNode* xml) {
    xmlChar* name = xmlGetProp(xml, (xmlChar*) "name");
    if (name == NULL)
        throw X3DParserError("component name missing", filename, xml);
    xmlChar* level = xmlGetProp(xml, (xmlChar*) "level");
    if (level == NULL)
        throw X3DParserError("component level mising", filename, xml);
    // TODO: add component
    xmlFree(name);
    xmlFree(level);
}

void World::parseMeta(xmlNode* xml) {
    xmlChar* name = xmlGetProp(xml, (xmlChar*) "name");
    if (name == NULL)
        throw X3DParserError("meta name missing", filename, xml);
    xmlChar* content = xmlGetProp(xml, (xmlChar*) "content");
    if (content == NULL)
        throw X3DParserError("meta content missing", filename, xml);
    // TODO: add meta
    xmlFree(name);
    xmlFree(content);
}

string World::getXmlAttr(xmlNode* xml, const string& attr, const string& desc) {
    xmlChar* name = xmlGetProp(xml, (xmlChar*) attr.c_str());
    if (name == NULL)
        throw X3DParserError(desc + " missing", filename, xml);
    string value = (char*) name;
    xmlFree(name);
    return value;
}

/**
 * Parse a prototype declaration.
 * The idea here is that we can't instantiate the prototype yet because
 * it's templatized to the root node of the body. So first we collect fields
 * from the interface and nodes (including IS statements) from the body,
 * then we take the first node and use it to construct the prototype, adding
 * the fields and body nodes.
 */
void World::parseProtoDeclare(xmlNode* xml) {
    // set up collectors for prototype contents
    string name = getXmlAttr(xml, "name", "prototype name");
    xmlNodePtr body=NULL, interface=NULL;

    // parse declaration contents
    for (xmlNode* child = xml->children; child != NULL; child = child->next) {
        if (child->type != XML_ELEMENT_NODE)
            continue;
        // single optional interface block
        if (!strcmp("ProtoInterface", (char*) child->name)) {
            if (interface != NULL)
                throw X3DParserError(
                        "only one ProtoInterface allowed", filename, child);
            interface = child;
        // single required interface block
        } else if (!strcmp("ProtoBody", (char*) child->name)) {
            if (body != NULL)
                throw X3DParserError(
                        "only one ProtoBody allowed", filename, child);
            body = child;
        }
    }

    // require body
    if (body == NULL)
        throw X3DParserError("ProtoBody section required", filename, xml);

    // get the body nodes
    vector<Node*> bodyNodes;
    vector<Connect> connects;
    parseProtoBody(body, bodyNodes, connects);

    // get the fields
    vector<ProtoFieldDef*> fields;
    if (interface != NULL)
        parseProtoInterface(interface, fields);

    // make the prototype and add to global scope
    // TODO: create a scope class to hold named objects
    Prototype* proto = Prototype::create(name, bodyNodes, connects, fields);
    //browser->addPrototype(proto);
}

void World::parseProtoInterface(xmlNode* xml, vector<ProtoFieldDef*>& fields) {
    for (xmlNode* child = xml->children; child != NULL; child = child->next) {
        if (child->type != XML_ELEMENT_NODE)
            continue;
        if (strcmp("field", (char*) child->name))
            throw X3DParserError("only fields allowed here", filename, child);
        string name = getXmlAttr(xml, "name", "proto-field name");
        string typeName = getXmlAttr(xml, "type", "proto-field type");
        string accessName = getXmlAttr(xml, "accessType", "proto-field access type");
        X3DField::Type type = X3DField::getType(typeName);
        SAIField::Access access = SAIField::getAccess(accessName);
        // TODO
        //X3DField* value = parseFieldValue(child, "value");
        //fields.push_back(new ProtoFieldDef(type, access, value));
    }
}

void World::parseProtoBody(
        xmlNode* xml, vector<Node*>& body, vector<Connect>& connects) {
    parseScene(xml, NULL, &body, &connects);
}

void World::parseExternProtoDeclare(xmlNode* xml) {
    throw X3DParserError("prototyping not supported", filename, xml);
    // TODO
}

void World::parseProtoInstance(xmlNode* xml, Node* parent) {
    throw X3DParserError("prototyping not supported", filename, xml);
    // TODO
}

void World::parseRoute(xmlNode* xml) {
    xmlChar* fromNode = xmlGetProp(xml, (xmlChar*) "fromNode");
    if (fromNode == NULL)
        throw X3DParserError("route missing fromNode", filename, xml);
    xmlChar* toNode = xmlGetProp(xml, (xmlChar*) "toNode");
    if (toNode == NULL)
        throw X3DParserError("route missing toNode", filename, xml);
    xmlChar* fromField = xmlGetProp(xml, (xmlChar*) "fromField");
    if (fromField == NULL)
        throw X3DParserError("route missing fromField", filename, xml);
    xmlChar* toField = xmlGetProp(xml, (xmlChar*) "toField");
    if (toField == NULL)
        throw X3DParserError("route missing toField", filename, xml);
    browser->createRoute(
        (char*) fromNode, (char*) fromField,
        (char*) toNode,   (char*) toField);
    xmlFree(fromNode);
    xmlFree(fromField);
    xmlFree(toNode);
    xmlFree(toField);
}

void World::parseConnects(xmlNode* xml, Node* node, vector<Connect>* connects) {
    if (connects == NULL)
        throw X3DParserError("<IS> not allowed here", filename, xml);
    for (xmlNode* child = xml->children; child != NULL; child = child->next) {
        if (child->type != XML_ELEMENT_NODE)
            continue;
        if (strcmp("connect", (char*) child->name))
            throw X3DParserError("expected <connect>", filename, child);
        string nodeField = getXmlAttr(child, "nodeField", "node field");
        string protoField = getXmlAttr(child, "protoField", "interface field");
        connects->push_back(Connect(node, nodeField, protoField));
    }
}

void World::parseNode(xmlNode* xml, Node* parent,
        vector<Node*>* nodes, vector<Connect>* connects) {
    Node* node = NULL;
    string field;
    // if it's a USE, then look up the node and use that
    if (xmlHasProp(xml, (xmlChar*) "USE")) {
        xmlChar* name = xmlGetProp(xml, (xmlChar*) "USE");
        node = browser->getNode((char*) name);
        if (node == NULL) {
            string msg = string("can't find USE node: ") + (char*) name;
            xmlFree(name);
            throw X3DParserError(msg, filename, xml);
        }
        xmlFree(name);
    // otherwise, parse the node
    } else {
        node = browser->createNode((char*) xml->name);
        if (node == NULL)
            throw X3DParserError(
                string("unknown node type: ")
                    + (char*) xml->name, filename, xml);
        for (xmlAttrPtr attr = xml->properties; attr != NULL; attr = attr->next) {
            char* name = (char*) attr->name;
            xmlChar* value = xmlGetProp(xml, attr->name);
            if (!strcmp("DEF", name)) {
                browser->addNamedNode((char*) value, node);
            } else if (!strcmp("field", name)) {
                field = (char*) value;
            } else {
                SAIField* field = node->getField(name);
                if (field == NULL) {
                    xmlFree(value);
                    throw X3DParserError(
                        string("unknown field for ") +
                        string(node->definition->name) +
                        string(": ") + name, filename, xml);
                }
                std::stringstream ss((char*) value);
                if (!field->get().parse(ss)) {
                    std::stringstream msg;
                    msg << "failed to parse value for field "
                        << name << ": " << value;
                    xmlFree(value);
                    throw X3DParserError(msg.str(), filename, xml);
                }
            }
            xmlFree(value);
        }
        parseScene(xml, node, NULL, connects);
    }
    if (nodes != NULL) {
        nodes->push_back(node);
    } else if (parent == NULL) {
        browser->addRoot(node);
    } else {
        if (field.empty()) {
            field = node->defaultContainerField();
            if (field.empty())
                throw X3DParserError(
                    string("no container field defined for ") + (char*) xml->name,
                        filename, xml);
        }
        SAIField* sai = parent->getField(field);
        if (sai == NULL)
            throw X3DParserError(
                string("invalid container field: ") + field, filename, xml);
        MFAbstractNode::unwrap(sai->get()).addNode(node);
        // XXX
        if (!node->realized())
            throw X3DParserError("should've realized...", filename, xml);
    }
}

void World::parseImport(xmlNode* xml) {
    throw X3DParserError("import/export not supported", filename, xml);
    // TODO
}

void World::parseExport(xmlNode* xml) {
    throw X3DParserError("import/export not supported", filename, xml);
    // TODO
}

}
