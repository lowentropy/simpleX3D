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

#ifndef _X3D_INOUTFIELD_H_
#define _X3D_INOUTFIELD_H_

#include "internal/SAIField.h"

namespace X3D {

/**
 * Base class for all input-output fields within nodes. In order to create
 * an input-output field, either declare an instance of DefaultInOutField,
 * or subclass InOutField and provide implementations for #filter and #action.
 * 
 * The low-level and high-level interfaces both allow read and write access
 * at both the SETUP and REALIZED phases of the node lifecycle. In the SETUP
 * phase, this will simply result in the value of the field being changed.
 * In the REALIZED phase, setting the field value will additionally result in
 * the field being marked dirty, scheduling any routes from the field to be
 * activated in the next event cascade.
 * 
 * The user-defined actions for input-output fields are broken into two parts.
 * On an input event trigger, the #filter method is called with the event value.
 * If the #filter method returns false, then no further action is taken and the
 * field value remains unchanged. If #filter returns true, the field value is
 * immediately overwritten and marked as dirty.
 * 
 * On the next event cascade, if the field has been marked as dirty, the first
 * action taken by the browser will be to call #action. This happens before any
 * outging routes, if any, are activated.
 * 
 * Attempting to write to an input-output field more than once during the same
 * period (before the next cascade) will result in an error.
 */
template <class N, class TT>
class InOutField : public BaseField<N,TT> {
private:
    typedef typename TT::REF_TYPE T;
    typedef typename TT::CONST_TYPE CT;

    /// whether field value has been modified since last event cascade
    bool dirty;

protected:

    list<Route*> incomingRoutes;

    list<Route*> outgoingRoutes;

public:

    /// generic wrapper value of this field
    TT value;

    /// Default constructor; #value will have its default value.
    InOutField() : dirty(false) {}

    /**
     * Returns a pointer to the node which owns this field.
     * 
     * @returns node pointer
     */
    INLINE N* node() const { return NodeField<N>::node; }

    /**
     * Get the access type of this field.
     * 
     * @returns INPUT_OUTPUT
     */
    SAIField::Access getAccess() const { return SAIField::INPUT_OUTPUT; }

    /**
     * Initializing constructor, which sets initial #value.
     * 
     * @param init initial value of #value
     */
    InOutField(CT init) : BaseField<N,TT>(), value(init) {}

    /**
     * Get the generic wrapper value of the field (high-level interface).
     * 
     * @returns generic field value
     */
    INLINE const TT& get() const {
        return value;
    }

    /**
     * Get the generic wrapper value of the field (high-level interface).
     * 
     * @returns generic field value
     */
    INLINE TT& get() {
        return value;
    }

    /**
     * Set the generic value of the field (high-level interface). If the
     * node is realized and #filter returns true, mark the field as dirty
     * and schedule for routing.
     * 
     * @param value generic field value to set
     */
    INLINE void set(const X3DField& value) {
        static TT x;
        try {
            (*this)(x.unwrap(value));
        } catch (EventLoopError e) {
            // this is OK, just do nothing
        }
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
     * Get the native value of the field.
     * 
     * @returns native field value
     */
    INLINE T operator()() {
        return value();
    }

    /**
     * Set the native value of the field. If the node is realized and
     * #filter returns true, mark the field as dirty and schedule for routing.
     * If the node is already dirty, this will throw an error.
     * 
     * @param value native value to set
     */
    INLINE void operator()(CT value) {
        if (!node()->realized()) {
            this->value = value;
            this->value.realize();
        } else {
            if (!filter(value))
                return;
            if (dirty) {
                throw EventLoopError(this);
            }
            this->value = value;
            this->value.realize();
            changed();
        }
    }

    /**
     * Bypass the input event stage by directly overwriting the field value
     * and marking the field as dirty. This function does not call #filter.
     * If the node is not in the REALZIED stage, or if the field has already
     * been marked as dirty, then this method will throw an error.
     * 
     * @param value native value to set
     */
    void send(CT value) {
        if (!node()->realized())
            throw X3DError("can't send output until realized");
        if (dirty)
            throw X3DError(
                string("already wrote to this field: ") +
                    this->SAIField::getName());
        this->value = value;
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

    /**
     * The default filtering action compares the event value with the value
     * already stored in the field. If they are equal, filter returns false
     * and the field is considered not to have changed.
     * 
     * @param value native event value
     * @returns whether value has changed
     */
    virtual bool filter(CT value) { return !(dirty || (this->value() == value)); }

    /**
     * Return whether field has been marked dirty since last event cascade.
     * 
     * @returns whether field is dirty
     */
    bool isDirty() const { return dirty; }

    /**
     * Clear the dirty value.
     */
    virtual void clearDirty() {
        dirty = false;
    }

    /**
     * Action to take on output event. Subclasses MUST define this function.
     */
    virtual void action() = 0;

    void addIncomingRoute(Route* route) {
        incomingRoutes.push_back(route);
    }

    void removeIncomingRoute(Route* route) {
        incomingRoutes.remove(route);
    }

    const list<Route*>& getIncomingRoutes() const {
        return incomingRoutes;
    }

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
    InOutField(const InOutField<N,TT>& f) { throw X3DError("COPY CONSTRUCTOR"); }
};

/**
 * Input-output field which has default (empty) actions.
 */
template <class N, class TT>
class DefaultInOutField : public InOutField<N,TT> {
private:
    typedef typename TT::TYPE T;
    typedef typename TT::CONST_TYPE CT;
public:
    /// Empty constructor.
    DefaultInOutField() : InOutField<N,TT>() {}

    /**
     * Initializing constructor.
     * 
     * @param init initial value for #value
     */
    DefaultInOutField(T init) : InOutField<N,TT>(init) {}

    /**
     * On output event, take no action.
     */
    void action() {}

private:

    // no copy constructor
    DefaultInOutField(const DefaultInOutField<N,TT>& f) { throw X3DError("COPY CONSTRUCTOR"); }
};

}

#endif // #ifndef _X3D_INOUTFIELD_H_
