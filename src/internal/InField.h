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

namespace X3D {

template <class N, class TT>
class InField : public BaseField<N,TT> {
private:
    typedef typename TT::TYPE T;
protected:
    inline N* node() const { return NodeField<N>::node; }
public:
    inline const TT& get() const {
        throw X3DError("can't read input field");
    }
    inline void set(const X3DField& field) {
        static TT x;
        (*this)(x.unwrap(field));
    }
    inline void operator()(T x) {
        if (!node()->realized())
            throw X3DError("wrong stage");
        action(x);
    }
    virtual void action(T value) = 0;
    void route() {}
};

}

#endif // #ifndef _X3D_INFIELD_H_
