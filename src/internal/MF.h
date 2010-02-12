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

#ifndef _X3D_MFFIELDS_H_
#define _X3D_MFFIELDS_H_

#include "internal/SF.h"
#include "internal/NodeIterator.h"

#include <list>
#include <map>
#include <vector>
#include <set>


namespace X3D {

template <typename R, typename C>
class MFEnumerable : public X3DField {
public:
    virtual void setBegin(void* ptr) = 0;
    virtual void setBegin(void* ptr) const = 0;
    virtual void setEnd(void* ptr) = 0;
    virtual void setEnd(void* ptr) const = 0;
    virtual void advance(void* ptr) = 0;
    virtual void advance(void* ptr) const = 0;
    virtual R get(void* ptr) = 0;
    virtual C get(void* ptr) const = 0;
};

template <class S, typename T, typename R, typename C>
class MF : public MFEnumerable<R,C> {
public:
    // non-const iterator
    class iterator {
    private:
        const MFEnumerable<R,C>* mf;
        char iter[sizeof(std::list<void*>::const_iterator)];
    public:
        iterator() {}
        iterator(const MFEnumerable<R,C>* mf, bool end) : mf(mf) {
            if (end)
                mf->setEnd((void*) iter);
            else
                mf->setBegin((void*) iter);
        }
        R operator*() {
            return mf->get((void*) iter);
        }
        iterator operator++() {
            iterator it = *this;
            mf->advance((void*) iter);
            return it;
        }
        iterator operator++(int unused) {
            mf->advance((void*) iter);
            return *this;
        }
        bool operator==(const iterator& it) const {
            return !memcmp(iter, it.iter, sizeof(iter));
        }
        bool operator!=(const iterator& it) const {
            return memcmp(iter, it.iter, sizeof(iter));
        }
    };
    // const iterator
    class const_iterator {
    private:
        const MFEnumerable<R,C>* mf;
        char iter[sizeof(std::list<void*>::const_iterator)];
    public:
        const_iterator() {}
        const_iterator(const MFEnumerable<R,C>* mf, bool end) : mf(mf) {
            if (end)
                mf->setEnd((void*) iter);
            else
                mf->setBegin((void*) iter);
        }
        C operator*() {
            return mf->get((void*) iter);
        }
        const_iterator operator++() {
            const_iterator it = *this;
            mf->advance((void*) iter);
            return it;
        }
        const_iterator operator++(int unused) {
            mf->advance((void*) iter);
            return *this;
        }
        bool operator==(const const_iterator& it) const {
            return !memcmp(iter, it.iter, sizeof(iter));
        }
        bool operator!=(const const_iterator& it) const {
            return memcmp(iter, it.iter, sizeof(iter));
        }
    };
    // virtual functions
    virtual void add(C elem) = 0;
    virtual void clear() = 0;
    virtual void print(ostream& os) const = 0;
    // constructor
    MF() {}
    // iterators
    iterator begin() { return iterator(this, false); }
    iterator end() { return iterator(this, true); }
    const_iterator begin() const { return const_iterator(this, false); }
    const_iterator end() const { return const_iterator(this, true); }
    // type access
    INLINE X3DField::Type getType() const { static S s; return s.getMFType(); }
    INLINE string getTypeName() const { static S s; return s.getMFTypeName(); }
    // contracts
    INLINE MF<S,T,R,C>& operator()() { return *this; }
    INLINE const MF<S,T,R,C>& operator()() const { return *this; }
    INLINE bool operator==(const X3DField& value) const {
        throw X3DError("NOT IMPLEMENTED");
    }
    INLINE bool operator!=(const X3DField& value) const {
        throw X3DError("NOT IMPLEMENTED");
    }
    MF<S,T,R,C>& operator()(const X3DField& value) {
        throw X3DError("direct list assignment not supported");
    }
    const MF<S,T,R,C>& operator=(const MF<S,T,R,C>& mf) {
        clear();
        const_iterator it;
        for (it = mf.begin(); it != mf.end(); it++)
            add(*it);
    }
    // parse list
    bool parse(istream& ss) {
        S x;
        ss >> std::ws;
        if (ss.peek() == ',')
            return false;
        while (true) {
            ss >> std::ws;
            if (ss.eof())
                break;
            if (!x.parse(ss))
                return false;
            add(x());
            ss >> std::ws;
            if (ss.peek() == ',')
                ss.get();
        }
        return true;
    }
};

template <class S, typename T, typename R, typename C>
class MFBasic : public MF<S,T,R,C> {
public:
    typedef MF<S,T,R,C> parent;
    virtual void clear() = 0;
    static INLINE const MFBasic<S,T,R,C>& unwrap(const X3DField& value) {
        static S sf;
        if (value.getType() != sf.getMFType())
            throw X3DError(
                string("base type mismatch; expected ") +
                sf.getMFTypeName() + ", but was " +
                value.getTypeName());
        return static_cast<const MFBasic<S,T,R,C>&>(value);
    }
    void print(ostream& os) const {
        typename parent::const_iterator it;
        for (it = parent::begin(); it != parent::end(); it++)
            os << *it << ",";
    }
    const MFBasic<S,T,R,C>& operator=(const X3DField& field) {
        *this = unwrap(field);
        return *this;
    }
    const MFBasic<S,T,R,C>& operator=(const MF<S,T,R,C>& mf) {
        clear();
        typename parent::const_iterator it;
        for (it = mf.begin(); it != mf.end(); it++)
            add(*it);
    }
};

template <class N>
class MFNode : public MF<SFNode<N>, N*, N*, N*> {
public:
    typedef MF<SFNode<N>,N*,N*,N*> parent;
    virtual void clear() = 0;
    /**
     * Unwrap a generic value into a list type. This method will
     * only succeed if the generic value is an MFNode list of the
     * exact same root node type.
     * 
     * @param f generic value
     * @returns native list type
     */
	static INLINE const MFNode<N>& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::MFNODE)
			throw X3DError(
                string("base type mismatch; expected MFNode") + \
                ", but was " + f.getTypeName()); \
		const MFNode<N>* mf = dynamic_cast<const MFNode<N>*>(&f);
        if (mf == NULL)
            throw X3DError("node type mismatch");
        return *mf;
	}
    void print(ostream& os) const {
        SFNode<N> sf;
        typename parent::const_iterator it;
        for (it = parent::begin(); it != parent::end(); it++) {
            sf = *it;
            os << sf << ", ";
        }
    }
    const MFNode<N>& operator=(const X3DField& field) {
        *this = unwrap(field);
        return *this;
    }
    const MFNode<N>& operator=(const MFNode<N>& mf) {
        clear();
        typename MFNode<N>::const_iterator it;
        for (it = mf.begin(); it != mf.end(); it++)
            add(*it);
    }
};

#define MF_ITER_IMPL(R,C) \
    void setBegin(void* ptr) { *((ITER*) ptr) = elements.begin(); } \
    void setBegin(void* ptr) const { *((CONST_ITER*) ptr) = elements.end(); } \
    void setEnd(void* ptr) { *((ITER*) ptr) = elements.begin(); } \
    void setEnd(void* ptr) const { *((CONST_ITER*) ptr) = elements.end(); } \
    void advance(void* ptr) { (*((ITER*) ptr))++; } \
    void advance(void* ptr) const { (*((CONST_ITER*) ptr))++; } \
    R get(void* ptr) { return *(*((ITER*) ptr))++; } \
    C get(void* ptr) const { return *(*((CONST_ITER*) ptr))++; }

template <class S, typename T, typename R, typename C>
class MFList : public MFBasic<S,T,R,C> {
private:
    typedef typename std::list<T>::iterator ITER;
    typedef typename std::list<T>::const_iterator CONST_ITER;
    std::list<T> elements;
public:
    typedef MFList<S,T,R,C>& TYPE;
    typedef const MFList<S,T,R,C>& CONST_TYPE;
    MF_ITER_IMPL(R,C)
    virtual void add(C elem) { elements.push_back(elem); }
    virtual void clear() { elements.clear(); }
    INLINE bool operator==(const MFList<S,T,R,C>& mf) const {
        return elements == mf.elements;
    }
    INLINE bool operator!=(const MFList<S,T,R,C>& mf) const {
        return elements != mf.elements;
    }
};

template <class S, typename T, typename R, typename C>
class MFArray : public MFBasic<S,T,R,C> {
private:
    typedef typename std::vector<T>::iterator ITER;
    typedef typename std::vector<T>::const_iterator CONST_ITER;
    std::vector<T> elements;
public:
    typedef MFArray<S,T,R,C>& TYPE;
    typedef const MFArray<S,T,R,C>& CONST_TYPE;
    MF_ITER_IMPL(R,C)
    virtual void add(C elem) { elements.push_back(elem); }
    virtual void clear() { elements.clear(); }
    INLINE bool operator==(const MFArray<S,T,R,C>& mf) const {
        return elements == mf.elements;
    }
    INLINE bool operator!=(const MFArray<S,T,R,C>& mf) const {
        return elements != mf.elements;
    }
};

template <class N>
class MFNodeList : public MFNode<N> {
private:
    typedef typename std::list<N*>::iterator ITER;
    typedef typename std::list<N*>::const_iterator CONST_ITER;
    std::list<N*> elements;
public:
    typedef MFNodeList<N>& TYPE;
    typedef const MFNodeList<N>& CONST_TYPE;
    MF_ITER_IMPL(N*, N*)
    virtual void add(N* elem) { elements.push_back(elem); }
    virtual void clear() { elements.clear(); }
    INLINE bool operator==(const MFNodeList<N>& mf) const {
        return elements == mf.elements;
    }
    INLINE bool operator!=(const MFNodeList<N>& mf) const {
        return elements != mf.elements;
    }
};

template <class N>
class MFNodeSet : public MFNode<N> {
private:
    typedef typename std::set<N*>::iterator ITER;
    typedef typename std::set<N*>::const_iterator CONST_ITER;
    std::set<N*> elements;
public:
    typedef MFNodeSet<N>& TYPE;
    typedef const MFNodeSet<N>& CONST_TYPE;
    MF_ITER_IMPL(N*, N*)
    virtual void add(N* elem) { elements.insert(elem); }
    virtual void clear() { elements.clear(); }
    INLINE bool operator==(const MFNodeSet<N>& mf) const {
        return elements == mf.elements;
    }
    INLINE bool operator!=(const MFNodeSet<N>& mf) const {
        return elements != mf.elements;
    }
};

template <class N>
class MFNodeArray : public MFNode<N> {
private:
    typedef typename std::vector<N*>::iterator ITER;
    typedef typename std::vector<N*>::const_iterator CONST_ITER;
    std::vector<N*> elements;
public:
    typedef MFNodeArray<N>& TYPE;
    typedef const MFNodeArray<N>& CONST_TYPE;
    MF_ITER_IMPL(N*, N*)
    virtual void add(N* elem) { elements.push_back(elem); }
    virtual void clear() { elements.clear(); }
    INLINE bool operator==(const MFNodeArray<N>& mf) const {
        return elements == mf.elements;
    }
    INLINE bool operator!=(const MFNodeArray<N>& mf) const {
        return elements != mf.elements;
    }
};

#define DEFINE_MF_NATIVE(NAME,TYPE) \
    typedef MF<SF##NAME,TYPE,TYPE,TYPE> MF##NAME; \
    typedef MFList<SF##NAME,TYPE,TYPE,TYPE> MF##NAME##List; \
    typedef MFArray<SF##NAME,TYPE,TYPE,TYPE> MF##NAME##Array;

#define DEFINE_MF_REF(NAME,CLASS) \
    typedef MF<SF##NAME,CLASS,CLASS&,const CLASS&> MF##NAME; \
    typedef MFList<SF##NAME,CLASS,CLASS&,const CLASS&> MF##NAME##List; \
    typedef MFArray<SF##NAME,CLASS,CLASS&,const CLASS&> MF##NAME##Array;

DEFINE_MF_NATIVE(Bool,bool)
DEFINE_MF_REF(Color,SFColor)
DEFINE_MF_REF(ColorRGBA,SFColorRGBA)
DEFINE_MF_NATIVE(Double,double)
DEFINE_MF_NATIVE(Float,float)
DEFINE_MF_REF(Image,SFImage)
DEFINE_MF_NATIVE(Int32,int)
DEFINE_MF_REF(Rotation,SFRotation)
DEFINE_MF_REF(Matrix3f,SFMatrix3f)
DEFINE_MF_REF(Matrix3d,SFMatrix3d)
DEFINE_MF_REF(Matrix4f,SFMatrix4f)
DEFINE_MF_REF(Matrix4d,SFMatrix4d)
DEFINE_MF_REF(String,std::string)
DEFINE_MF_NATIVE(Time,double)
DEFINE_MF_REF(Vec2f,SFVec2f)
DEFINE_MF_REF(Vec2d,SFVec2d)
DEFINE_MF_REF(Vec3f,SFVec3f)
DEFINE_MF_REF(Vec3d,SFVec3d)
DEFINE_MF_REF(Vec4f,SFVec4f)
DEFINE_MF_REF(Vec4d,SFVec4d)

/**
 * This abstract class exists so that you can access arbitrary
 * fields which you know to be MFNode<?>.
 */
/*
class MFAbstractNode {
public:

    virtual void cloneInto(MFAbstractNode& target, std::map<Node*,Node*>* mapping=NULL, bool shallow=false) = 0;

    static const MFAbstractNode& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::MFNODE)
			throw X3DError(
                string("base type mismatch; expected MFNode") + \
                ", but was " + f.getTypeName()); \
        const MFAbstractNode* mf = dynamic_cast<const MFAbstractNode*>(&f);
        if (mf == NULL)
            throw X3DError(
                string("list type mismatch; not a node list"));
        return *mf;
    }
    static MFAbstractNode& unwrap(X3DField& f) {
		if (f.getType() != X3DField::MFNODE)
			throw X3DError(
                string("base type mismatch; expected MFNode") + \
                ", but was " + f.getTypeName()); \
        MFAbstractNode* mf = dynamic_cast<MFAbstractNode*>(&f);
        if (mf == NULL)
            throw X3DError(
                string("list type mismatch; not a node list"));
        return *mf;
    }
};
*/
/*

    void cloneInto(MFAbstractNode& abstract, std::map<Node*,Node*>* mapping=NULL, bool shallow=false) {
        MFNode<N>* mf = dynamic_cast<MFNode<N>*>(&abstract);
        if (mf == NULL)
            throw X3DError("node type mismatch");
        mf->clear();
        list<N*>& source = this->MFBase<N*>::elements;
        typename list<N*>::iterator it;
        if (shallow) {
            for (it = source.begin(); it != source.end(); it++)
                mf->add(*it);
        } else {
            for (it = source.begin(); it != source.end(); it++)
                mf->add((*it)->clone(mapping, shallow));
        }
    }

    void begin(NodeIterator& iter) {
        void* container = (void*) &(iter.iter);
        ITER* it = (ITER*) container;
        *it = this->MFBase<N*>::elements.begin();
        if (*it == this->MFBase<N*>::elements.end())
            iter.current = NULL;
        else
            iter.current = **it;
    }

    void next(NodeIterator& iter) {
        void* container = (void*) &(iter.iter);
        ITER* it = (ITER*) container;
        if (++(*it) == this->MFBase<N*>::elements.end())
            iter.current = NULL;
        else
            iter.current = **it;
    }

        SFNode<N> sf;
        typename list<N*>::const_iterator it;
        for (   it = MFBase<N*>::elements.begin();
                it != MFBase<N*>::elements.end();
                it++) {
            sf = *it;
            os << sf << ", ";
        }
    }

    bool operator==(const X3DField& f) const {
        return this->MFBase<N*>::operator==(unwrap(f));
    }

    bool operator!=(const X3DField& f) const {
        return this->MFBase<N*>::operator!=(unwrap(f));
    }

    MFNode<N>& operator()(const X3DField& f) {
        throw new X3DError("list assignment not supported");
    }
};
*/

}

#endif // #ifndef _X3D_MFFIELDS_H_
