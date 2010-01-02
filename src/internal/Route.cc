#include "internal/Route.h"

#include <sstream>
using std::ostringstream;

namespace X3D {

void Route::checkTypes() {
    FieldDef* def = toField->definition;
    if (fromField->getType() != toField->getType()) {
        ostringstream os;
        os << "route field type mismatch (" <<
                   "source=" << fromField->getTypeName() << ", " <<
                   "target=" << toField->getTypeName() << ")";
        throw X3DError(os.str());
    }
}

void Route::activate() const {
    if (!fromField->isDirty())
        return;
    const X3DField& value = fromField->get();
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
    fromField->getNode()->realize();
    toField->getNode()->realize();
    fromField->addOutgoingRoute(this);
    toField->addIncomingRoute(this);
}

}
