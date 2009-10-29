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

namespace X3D {

template <class N, class TT>
class OutField : public BaseField<N,TT> {
private:
    bool dirty;
    typedef typename TT::TYPE T;
protected:
    inline N* node() const { return NodeField<N>::node; }
public:
    TT value;
    inline const TT& get() const {
        if (!node()->realized())
            throw X3DError("wrong stage");
        return value;
    }
    inline void set(const X3DField& field) {
        throw X3DError("can't write output field");
    }
    inline T operator()() {
        if (!node()->realized())
            throw X3DError("wrong stage");
        return value();
    }
    inline void operator()(T value) {
        if (!node->realized())
            throw X3DError("can't route event until realized");
        if (dirty)
            throw X3DError("already wrote to this field");
        this->value = value;
        dirty = true;
    }
    void route() {
        if (dirty) {
            action();
            // TODO: send event
            dirty = false;
        }
    }
    virtual void action() = 0;
};

template <class N, class TT>
class DefaultOutField : public OutField<N,TT> {
public:
    virtual void action() {}
};

}

#endif // #ifndef _X3D_OUTFIELD_H_
