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

#include "internal/types.h"
#include <gmock/gmock.h>

using namespace X3D;

// here's the list of tests
#include "internal/BrowserTests.h"
#include "internal/SFImageTests.h"
#include "Core/X3DBindableNodeTests.h"

int main(int argc, char** argv) {
	Browser browser;
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
