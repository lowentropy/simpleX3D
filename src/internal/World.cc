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

World* World::read(Browser* browser, const char* filename) {
    World* world = new World(browser, "", "", MFString());
    xmlDoc* doc;
    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL)
        throw X3DError("failed to parse file");
    world->parseRoot(xmlDocGetRootElement(doc));
    xmlFreeDoc(doc);
}

void World::parseRoot(xmlNode* xml) {
    if (xml->type != XML_ELEMENT_NODE ||
        strcmp("X3D", (char*) xml->name))
        throw X3DParserError("toplevel node should be <X3D>");
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
                    + (char*) child->name);
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
                    + (char*) child->name);
        }
    }
}

void World::parseScene(xmlNode* xml, Node* node) {
    for (xmlNode* child = xml->children; child != NULL; child = child->next) {
        if (child->type != XML_ELEMENT_NODE)
            continue;
        if (!strcmp("ProtoDeclare", (char*) child->name)) {
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
        } else {
            parseNode(child, node);
        }
    }
}

void World::parseComponent(xmlNode* xml) {
    xmlChar* name = xmlGetProp(xml, (xmlChar*) "name");
    if (name == NULL)
        throw X3DParserError("component name missing");
    xmlChar* level = xmlGetProp(xml, (xmlChar*) "level");
    if (level == NULL)
        throw X3DParserError("component level mising");
    // TODO: add component
    xmlFree(name);
    xmlFree(level);
}

void World::parseMeta(xmlNode* xml) {
    xmlChar* name = xmlGetProp(xml, (xmlChar*) "name");
    if (name == NULL)
        throw X3DParserError("meta name missing");
    xmlChar* content = xmlGetProp(xml, (xmlChar*) "content");
    if (content == NULL)
        throw X3DParserError("meta content missing");
    // TODO: add meta
    xmlFree(name);
    xmlFree(content);
}

void World::parseProtoDeclare(xmlNode* xml) {
    throw X3DParserError("prototyping not supported");
    // TODO
}

void World::parseExternProtoDeclare(xmlNode* xml) {
    throw X3DParserError("prototyping not supported");
    // TODO
}

void World::parseProtoInstance(xmlNode* xml, Node* parent) {
    throw X3DParserError("prototyping not supported");
    // TODO
}

void World::parseRoute(xmlNode* xml) {
    xmlChar* fromNode = xmlGetProp(xml, (xmlChar*) "fromNode");
    if (fromNode == NULL)
        throw X3DParserError("route missing fromNode");
    xmlChar* toNode = xmlGetProp(xml, (xmlChar*) "toNode");
    if (toNode == NULL)
        throw X3DParserError("route missing toNode");
    xmlChar* fromField = xmlGetProp(xml, (xmlChar*) "fromField");
    if (fromField == NULL)
        throw X3DParserError("route missing fromField");
    xmlChar* toField = xmlGetProp(xml, (xmlChar*) "toField");
    if (toField == NULL)
        throw X3DParserError("route missing toField");
    browser->createRoute(
        (char*) fromNode, (char*) fromField,
        (char*) toNode,   (char*) toField);
    xmlFree(fromNode);
    xmlFree(fromField);
    xmlFree(toNode);
    xmlFree(toField);
}

void World::parseNode(xmlNode* xml, Node* parent) {
    Node* node = NULL;
    xmlChar* def = NULL;
    if (xmlHasProp(xml, (xmlChar*) "USE")) {
        xmlChar* name = xmlGetProp(xml, (xmlChar*) "USE");
        node = browser->getNodeByName((char*) name);
        if (node == NULL) {
            string msg = string("can't find USE node: ") + (char*) name;
            xmlFree(name);
            throw X3DParserError(msg);
        }
        xmlFree(name);
    } else {
        node = browser->createNode((char*) xml->name);
        if (node == NULL)
            throw X3DParserError(
                string("unknown node type: ")
                    + (char*) xml->name);
        xmlChar* def = xmlGetProp(xml, (xmlChar*) "DEF");
        if (def != NULL) {
            browser->addNamedNode((char*) def, node);
            xmlFree(def);
        }
        // TODO: parse node basics
        for (xmlNode* child = xml->children; child != NULL; child = child->next)
            if (child->type == XML_ELEMENT_NODE)
                parseScene(child, node);
    }
    xmlChar* xmlField = xmlGetProp(xml, (xmlChar*) "containerField");
    string field = (xmlField != NULL)
        ? ((char*) xmlField)
        : node->defaultContainerField();
    if (parent == NULL)
        browser->addRoot(node);
    else {
        SAIField* containerField = parent->getField(field);
        MFAbstractNode* container = dynamic_cast<MFAbstractNode*>(containerField);
        container->add(node);
    }
    if (xmlField != NULL)
        xmlFree(xmlField);
}

void World::parseImport(xmlNode* xml) {
    throw X3DParserError("import/export not supported");
    // TODO
}

void World::parseExport(xmlNode* xml) {
    throw X3DParserError("import/export not supported");
    // TODO
}

}
