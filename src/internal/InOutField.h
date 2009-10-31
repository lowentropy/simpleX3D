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
    bool dirty;
    typedef typename TT::TYPE T;
    typedef typename TT::CONST_TYPE CT;
protected:
    inline N* node() const { return NodeField<N>::node; }
public:
    TT value;
    InOutField() {}
    InOutField(CT init) : BaseField<N,TT>(), value(init) {}
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
    inline void operator()(CT value) {
        if (!node()->realized()) {
            this->value = value;
        } else {
            if (!filter(value))
                return;
            this->value = value;
            dirty = true;
        }
    }
    void send(CT value) {
        if (!node()->realized())
            throw X3DError("can't send output until realized");
        this->value = value;
        dirty = true;
    }
    virtual bool filter(CT value) { return this->value() != value; }
    void changed(bool value=true) {
        dirty = value;
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
class DefaultInOutField : public InOutField<N,TT> {
private:
    typedef typename TT::TYPE T;
    typedef typename TT::CONST_TYPE CT;
public:
    DefaultInOutField() : InOutField<N,TT>() {}
    DefaultInOutField(T init) : InOutField<N,TT>(init) {}
    void action() {}
};

}

#endif // #ifndef _X3D_INOUTFIELD_H_
