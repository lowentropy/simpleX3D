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
#include "internal/Route.h"
#include "internal/Plugin.h"

#include <iostream>
using std::cout;
using std::endl;

namespace X3D {

Browser* Browser::_inst;

Browser::Browser() : profile(new Profile()) {
	if (_inst == NULL)
		_inst = this;
	else {
        delete profile;
		throw X3DError("multiple browser instances!");
    }
	Builtin::init(profile);
    started = false;
}

Plugin* Browser::addPlugin(const string& library) {
    Plugin* plugin = new Plugin(library);
    plugin->registerPlugin();
    plugins.push_back(plugin);
    return plugin;
}

void Browser::removePlugin(Plugin* plugin) {
    list<Plugin*>::iterator it;
    for (it = plugins.begin(); it != plugins.end(); it++) {
        if (*it == plugin) {
            (*it)->remove();
            plugins.erase(it);
            delete plugin;
            break;
        }
    }
}

void Browser::reset() {
	list<Node*>::iterator it = nodes.begin();
	for (; it != nodes.end(); it++) {
        Node* node = *it;
        node->dispose();
        delete node;
    }
    nodes.clear();
    persistent.clear();
    roots.clear();
    dirtyFields.clear();
    firedFields.clear();
    defs.clear();
    newSensors.clear();
    timers.clear();
    while (!events.empty())
        events.pop();
}

Browser::~Browser() {
    reset();
	delete profile;
}

bool Browser::simulate() {
    initRoots();
    initSensors();
    if (events.empty())
        return false;
    advanceTime();
    do {
        do {
            processEvents();
        } while (haveEvents());
    } while (haveTimers());
    endRoute();
    return true;
}

void Browser::initRoots() {
    if (started)
        return;
    list<Node*>::iterator r_it;
    for (r_it = roots.begin(); r_it != roots.end(); r_it++)
        (*r_it)->realize();
    started = true;
}

void Browser::initSensors() {
    vector<X3DSensorNode*>::iterator s_it;
    for (s_it = newSensors.begin(); s_it != newSensors.end(); s_it++)
        (*s_it)->initSensor();
    newSensors.clear();
}

void Browser::advanceTime() {
    simTime = events.top().time;
}

bool Browser::haveEvents() {
    if (events.empty())
        return false;
    return events.top().time <= simTime;
}

void Browser::processEvents() {
    while (haveEvents())
        processNextEvent();
    route();
}

void Browser::processNextEvent() {
    X3DSensorNode* node = events.top().node;
    if (node != NULL)
        node->evaluate();
    events.pop();
}

bool Browser::haveTimers() {
    list<X3DTimeDependentNode*>::iterator it;
    for (it = timers.begin(); it != timers.end(); it++)
        if ((*it)->tick())
            return true;
    return false;
}

double Browser::now() {
    return simTime;
}

void Browser::wake(double time) {
    schedule(time, NULL);
}

void Browser::schedule(double time, X3DSensorNode* node) {
    events.push(Event(time, node));
}

Node* Browser::createNode(const std::string& name) {
	NodeDef* def = profile->getNode(name);
	if (def == NULL)
		return NULL;
    Node* node = def->create();
    X3DSensorNode* sensor = dynamic_cast<X3DSensorNode*>(node);
    X3DTimeDependentNode* timer = dynamic_cast<X3DTimeDependentNode*>(node);
    if (sensor != NULL)
        newSensors.push_back(sensor);
    if (timer != NULL)
        timers.push_back(timer);
    return node;
}

void Browser::addNode(Node* node) {
    if (node != NULL)
        nodes.push_back(node);
}

void Browser::route() {
    // route until cascade is done; this vector will grow as
    // you are iterating it
    for (int i = 0; i < dirtyFields.size(); i++)
        routeFrom(dirtyFields[i]);
    dirtyFields.clear();
}

void Browser::endRoute() {
    for (int i = 0; i < firedFields.size(); i++)
        firedFields[i]->clearDirty();
    firedFields.clear();
}

void Browser::addDirtyField(SAIField* field) {
    dirtyFields.push_back(field);
}

void Browser::routeFrom(SAIField* field) {
    const list<Route*>& routes = field->getOutgoingRoutes();
    list<Route*>::const_iterator it;
    for (it = routes.begin(); it != routes.end(); it++)
        (*it)->activate();
    firedFields.push_back(field);
}

void Browser::persist(Node* node) {
	persistent.push_back(node);
}

void Browser::addRoot(Node* node) {
    roots.push_back(node);
}

Route* Browser::createRoute(Node* fromNode, const string& fromFieldName,
                            Node* toNode, const string& toFieldName) const {
    SAIField* fromField = fromNode->getField(fromFieldName);
    if (fromField == NULL)
        throw X3DError(
            string("couldn't find source field: ") + fromFieldName);
    SAIField* toField = toNode->getField(toFieldName);
    if (toField == NULL)
        throw X3DError(
            string("couldn't find target field: ") + toFieldName);
    return createRoute(fromField, toField);
}

Route* Browser::createRoute(SAIField* fromField, SAIField* toField) const {
    const list<Route*>& routes = fromField->getOutgoingRoutes();
    list<Route*>::const_iterator it;
    for (it = routes.begin(); it != routes.end(); it++)
        if ((*it)->toField == toField)
            return *it;
    Route* route = new Route(fromField, toField);
    try {
        route->insert();
        return route;
    } catch (X3DError e) {
        delete route;
        throw e;
    }
}

Route* Browser::createRoute(const string& fromNode, const string& fromField,
                          const string& toNode, const string& toField) {
    Node* from = getNode(fromNode);
    if (from == NULL)
        throw X3DError(string("source node not found: ") + fromNode);
    Node* to = getNode(toNode);
    if (to == NULL)
        throw X3DError(string("target node not found: ") + toNode);
    return createRoute(from, fromField, to, toField);
}

void Browser::addNamedNode(const string& name, Node* node) {
    defs[name] = node;
    node->setName(name);
}

Node* Browser::getNode(const string& name) {
    if (defs.count(name))
        return defs[name];
    return NULL;
}

}
