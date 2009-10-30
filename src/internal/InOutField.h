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

template <class N, class TT>
class InOutField : public BaseField<N,TT> {
private:
    typedef typename TT::TYPE T;
protected:
    inline N* node() const { return NodeField<N>::node; }
public:
    TT value;
    InOutField() {}
    InOutField(T init) : BaseField<N,TT>(), value(init) {}
    inline const TT& get() const {
        return value;
    }
    inline void set(const X3DField& field) {
        static TT x;
        (*this)(x.unwrap(field));
    }
    inline T operator()() {
        return value();
    }
    inline void operator()(T value) {
        if (!node()->realized()) {
            this->value = value;
        } else {
            if (!filter(value))
                return;
            this->value = value;
            // TODO: prepare for routing
            action();
        }
    }
    void send(T value) {
        if (!node()->realized())
            throw X3DError("can't send output until realized");
        this->value = value;
        // TODO: prepare for routing
        action();
    }
    virtual bool filter(T value) { return this->value() != value; }
    virtual void action() = 0;
    void route() {}
};

template <class N, class TT>
class DefaultInOutField : public InOutField<N,TT> {
private:
    typedef typename TT::TYPE T;
public:
    DefaultInOutField() : InOutField<N,TT>() {}
    DefaultInOutField(T init) : InOutField<N,TT>(init) {}
    void action() {}
};

}

#endif // #ifndef _X3D_INOUTFIELD_H_
