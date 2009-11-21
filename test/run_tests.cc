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

#include <iostream>

using std::cout;
using std::endl;

#include "internal/Browser.h"
#include <gmock/gmock.h>
#include <libxml/xmlversion.h>
#include <libxml/parser.h>

using namespace X3D;

Browser* browser() {
	return Browser::getSingleton();
}

// here's the list of tests
#include "internal/BrowserTests.h"
#include "internal/SFImageTests.h"
#include "internal/TypeTests.h"
#include "internal/FieldIteratorTests.h"
#include "internal/RouteTests.h"
#include "internal/RoutingTests.h"
#include "internal/XmlLoadTests.h"
#include "internal/ParseTests.h"
#include "Core/X3DBindableNodeTests.h"

int main(int argc, char** argv) {
#ifdef LIBXML_TREE_ENABLED
    LIBXML_TEST_VERSION
	Browser browser;
	::testing::InitGoogleMock(&argc, argv);
	int code = RUN_ALL_TESTS();
    xmlCleanupParser();
    return code;
#else
    cout << "Libxml tree support not enabled!" << endl;
    return 1;
#endif
}
