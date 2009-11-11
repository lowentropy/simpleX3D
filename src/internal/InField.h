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

#ifndef _X3D_INFIELD_H_
#define _X3D_INFIELD_H_

#include "internal/SAIField.h"
#include "internal/InputCapableField.h"

namespace X3D {

/**
 * Base class for all node input fields. To make an input field,
 * subclass InField and provide the action() method, which takes
 * the value passed to the input field.
 * 
 * The low-level interface for input fields consists of the
 * operator()(value) method, which triggers the input event.
 * 
 * The high-level interface for input fields consists of the
 * set(value) method, which triggers the input event.
 * 
 * Both behaviors require that the node the field belongs to
 * is in state REALIZED.
 */
template <class N, class TT>
class InField : public BaseField<N,TT>, InputCapableField {
private:
    typedef typename TT::TYPE T;
    typedef typename TT::CONST_TYPE CT;

protected:
    /**
     * Return a pointer to the node which owns this field.
     * 
     * @returns node pointer
     */
    INLINE N* node() const { return NodeField<N>::node; }

public:

    /// Empty constructor.
    InField() {}

    /**
     * Get the access type of this field.
     * 
     * @returns INPUT_ONLY
     */
    SAIField::Access getAccess() const { return SAIField::INPUT_ONLY; }

    /**
     * Throws an error, since input fields have no persistent value.
     * 
     * @returns nothing, always throws an error
     */
    INLINE const TT& get() const {
        throw X3DError("can't read input field");
    }

    /**
     * Send a value to the input event. Will throw an error if
     * the value is of the wrong type or if the node is not in
     * state REALIZED.
     * 
     * @param value generic event value
     */
    INLINE void set(const X3DField& value) {
        static TT x;
        (*this)(x.unwrap(value));
    }

    /**
     * Send a value to the input event. Will throw an error if
     * the node is not in state REALIZED.
     * 
     * @param value native event value
     */
    INLINE void operator()(CT value) {
        if (!node()->realized())
            throw X3DError("wrong stage");
        action(value);
    }

    /**
     * Abstract method which subclasses use to indicate what actions
     * to take when the input event is triggered.
     * 
     * @param value native event value
     */
    virtual void action(CT value) = 0;

    /**
     * Input fields are never dirty, since they don't route out.
     * 
     * @returns false
     */
    bool isDirty() const { return false; }

    /**
     * Clear the dirty value.
     */
    virtual void clearDirty() {}

private:

    // no copy constructor
    InField(const InField<N,TT>& f) { throw X3DError("COPY CONSTRUCTOR"); }
};

}

#endif // #ifndef _X3D_INFIELD_H_
