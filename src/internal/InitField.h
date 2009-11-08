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

#ifndef _X3D_INITFIELD_H_
#define _X3D_INITFIELD_H_

#include "internal/SAIField.h"

namespace X3D {

/**
 * Base class for all init-only fields. To make an init-only field,
 * declare an instance of this class (it is never necessary to subclass
 * InitField).
 * 
 * The low-level interface allows code to get and set the value of the
 * field as long as its node is in the SETUP phase. Attempting to access
 * the field in any way at another phase will result in an error.
 * 
 * The high-level interface is the same as the low-level interface.
 */
template <class N, class TT>
class InitField : public BaseField<N,TT> {
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
    /// wrapper value contained by the field
    TT value;

    /// Default constructor; #value has default value.
    InitField() {}

    /**
     * Initializing constructor, taking the initial #value.
     * 
     * @param init initial value for #value
     */
    InitField(CT init) : BaseField<N,TT>(), value(init) {}

    /**
     * Get the generic value of this field (high-level interface).
     * Will throw an error if the field's node is not in the SETUP
     * phase.
     * 
     * @returns generic field value
     */
    INLINE const TT& get() const {
        if (node()->realized())
            throw X3DError("wrong stage");
        return value;
    }

    /**
     * Set the generic value of this field (high-level interface).
     * Will throw an error if the field's node is not in the SETUP
     * phase.
     * 
     * @param value generic field value to set
     */
    INLINE void set(const X3DField& value) {
        static TT x;
        (*this)(x.unwrap(value));
    }

    /**
     * Get the native value of the field.
     * Will throw an error if the field's node is not in the SETUP
     * phase.
     * 
     * @return native field value
     */
    INLINE T operator()() {
        if (node()->realized())
            throw X3DError("wrong stage");
        return value();
    }

    /**
     * Set the native value of the field.
     * Will throw an error if the field's node is not in the SETUP
     * phase.
     * 
     * @param value native value to set
     */
    INLINE void operator()(CT value) {
        if (node()->realized())
            throw X3DError("wrong stage");
        this->value = value;
    }

    /**
     * Since init fields don't route out, they can't be dirty.
     * 
     * @returns false
     */
    bool isDirty() const { return false; }

private:

    // no copy constructor
    InitField(const InitField<N,TT>& f) { throw X3DError("COPY CONSTRUCTOR"); }
};

}

#endif // #ifndef _X3D_INITFIELD_H_
