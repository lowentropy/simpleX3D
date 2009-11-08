#include "internal/Route.h"

namespace X3D {

void Route::checkTypes() {
    if (from_field->getType() != to_field->getType()) {
        throw X3DError("route field type mismatch");
    }
}

void Route::activate() {
    if (!from_field->isDirty())
        return;
    const X3DField& value = from_field->get();
    from_field->clearDirty();
    to_field->set(value);
}

}
