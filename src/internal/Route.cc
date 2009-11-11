#include "internal/Route.h"

namespace X3D {

void Route::checkTypes() {
    if (fromField->getType() != toField->getType()) {
        throw X3DError("route field type mismatch");
    }
}

void Route::activate() const {
    if (!fromField->isDirty())
        return;
    const X3DField& value = fromField->get();
    fromField->clearDirty();
    toField->set(value);
}

void Route::remove() {
    fromField->removeOutgoingRoute(this);
    toField->removeIncomingRoute(this);
}

void Route::insert() {
    const list<Route*>& outs = fromField->getOutgoingRoutes();
    list<Route*>::const_iterator it;
    for (it = outs.begin(); it != outs.end(); it++) {
        if ((*it)->toField == toField)
            throw X3DError("another identical route exists");
    }
    fromField->addOutgoingRoute(this);
    toField->addIncomingRoute(this);
}

}
