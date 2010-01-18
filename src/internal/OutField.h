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

#ifndef _X3D_OUTFIELD_H_
#define _X3D_OUTFIELD_H_

#include "internal/SAIField.h"
// XXX
#include <sstream>

namespace X3D {

/**
 * Base class for all output-only fields contained in nodes.
 * 
 * To create an output field, either create an instance of DefaultOutField
 * or subclass OutField and provide the #action method.
 * 
 * The high-level interface for this field type only defines the
 * get() method, which returns the last value triggered by this field.
 * 
 * The low-level interface additionally defines the operator()(value)
 * method, which triggers an output event. It does this by immediately
 * setting the value of the field, and marking the field as dirty.
 * 
 * Attempting to trigger an output event when the node is not in the
 * REALIZED state will result in an error. Only one output event per
 * event cycle is allowed; attempting to trigger the field repeatedly
 * will also result in an error.
 * 
 * When the output event actually triggers, the first action performed
 * by the browser is to call the #action method. This occurs before any
 * outgoing routes are activated.
 */
template <class N, class TT>
class OutField : public BaseField<N,TT> {
private:
    typedef typename TT::TYPE T;
    typedef typename TT::CONST_TYPE CT;

    /// whether field has been modified
    bool dirty;

protected:

    list<Route*> outgoingRoutes;

public:

    /// Stored value of the field; last thing sent in output event.
    TT value;

    /// Empty constructor.
    OutField() : dirty(false) {}

    /**
     * Get a reference to the node which owns this field.
     * 
     * @returns node pointer
     */
    INLINE N* node() const { return NodeField<N>::node; }


    /**
     * Get the access type of this field.
     * 
     * @returns OUTPUT_ONLY
     */
    SAIField::Access getAccess() const { return SAIField::OUTPUT_ONLY; }

    /**
     * High-level accessor to get generic field value. Will throw an
     * error if the field's node is not in state REALIZED.
     * 
     * @returns generic field value
     */
    INLINE const TT& get() const {
        if (!node()->realized())
            throw X3DError("can't read output field until node is realized", node());
        return value;
    }

    /**
     * High-level accessor to get generic field value. Will throw an
     * error if the field's node is not in state REALIZED.
     * 
     * @returns generic field value
     */
    INLINE TT& get() {
        if (!node()->realized())
            throw X3DError("can't read output field until node is realized", node());
        return value;
    }

    /**
     * High-level accessor to set generic field value. This will
     * always throw an error, as output fields can't be written to.
     * 
     * @param field generic field value to set
     */
    INLINE void set(const X3DField& field) {
        throw X3DError("can't write to output field", node());
    }

    /**
     * Unsafe get() operation. Will never throw an error.
     *
     * @returns generic field value
     */
    INLINE TT& getSilently() {
        return value;
    }

    /**
     * Unsafe set() operation. Will never throw an error. The value
     * of the field is set without triggering any events. Additionally,
     * if the value is a node, the node will not be automatically
     * realized.
     *
     * @param value generic field value to set
     */
    INLINE void setSilently(const X3DField& value) {
        static TT x;
        this->value = x.unwrap(value);
    }

    /**
     * Low-level accessor to get native field value. Will throw an
     * error if the field's node is not in state REALIZED.
     * 
     * @returns native field value
     */
    INLINE T operator()() {
        if (!node()->realized())
            throw X3DError("can't read output field until node is realized", node());
        return value();
    }

    /**
     * Low-level access to set the native field value. This has the effect
     * of overwriting the field's value and queueing an output event. If the
     * field's node is not in state REALIZED, this will throw an error.
     * 
     * @param value native value to set
     */
    INLINE void operator()(CT value) {
        send(value);
    }

    INLINE void send(CT value) {
        if (!node()->realized())
            throw X3DError("can't route event until realized", node());
        if (dirty)
            throw X3DError(
                string("already wrote to this field: ") +
                    this->SAIField::getName(), node());
        this->value = value;
        this->value.realize();
        changed();
    }

    /**
     * Manually set whether the field should be considered dirty.
     * 
     * @param value whether field is changed
     */
    void changed(bool value=true) {
        if (value && !dirty) {
            node()->queue(this);
            action();
        }
        dirty = value;
    }

    /// @returns whether field has been marked dirty
    bool isDirty() const { return dirty; }

    /**
     * Clear the dirty value.
     */
    virtual void clearDirty() {
        dirty = false;
    }

    /**
     * When the output field triggers an event, the browser will call
     * #action before activating any outgoing routes. This will be called
     * even if no routes are present. Subclasses MUST provide this method,
     * unless they subclass DefaultOutField.
     */
    virtual void action() = 0;

    void addOutgoingRoute(Route* route) {
        outgoingRoutes.push_back(route);
    }

    void removeOutgoingRoute(Route* route) {
        outgoingRoutes.remove(route);
    }

    const list<Route*>& getOutgoingRoutes() const {
        return outgoingRoutes;
    }

private:

    // no copy constructor
    OutField(const OutField<N,TT>& f) { throw X3DError("COPY CONSTRUCTOR"); }
};

/**
 * Provides a default action for OutField. Derive from this class if you
 * either do not want any action to be performed for this output field,
 * or if the default action is to do nothing.
 */
template <class N, class TT>
class DefaultOutField : public OutField<N,TT> {
public:
    /// Default action is to do nothing.
    virtual void action() {}

    /// Empty constructor.
    DefaultOutField() {}
    
private:

    // no copy constructor
    DefaultOutField(const DefaultOutField<N,TT>& f) { throw X3DError("COPY CONSTRUCTOR"); }
};

}

#endif // #ifndef _X3D_OUTFIELD_H_
