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

#include "internal/Plugin.h"

namespace X3D {

void Plugin::registerPlugin() {
    void* handle;
    typedef void (*REGFUN)(Plugin*);
    typedef string (*STRFUN)();
    REGFUN regFun;
    STRFUN strFun;
    char* error;

    handle = dlopen(library.c_str(), RTLD_LAZY);
    if (handle == NULL)
        throw X3DError(string("can't load plugin: ") + dlerror());

    strFun = (STRFUN) dlsym(handle, "pluginName");
    if (NULL != (error = dlerror()))
        throw X3DError(string("can't load plugin: ") + error);
    name = strFun();

    strFun = (STRFUN) dlsym(handle, "pluginVersion");
    if (NULL != (error = dlerror()))
        throw X3DError(string("can't load plugin: ") + error);
    version = strFun();

    regFun = (REGFUN) dlsym(handle, "registerPlugin");
    if (NULL != (error = dlerror()))
        throw X3DError(string("can't load plugin: ") + error);

    regFun(this);
}

void Plugin::remove() {
    std::list<std::pair<NodeDef*, AbstractFactory*> >::iterator it;
    for (it = factories.begin(); it != factories.end(); it++)
        it->first->removeFactory(it->second);
}

}
