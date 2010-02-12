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
    virtual bool compare(void* a, void *b) = 0;
    virtual bool compare(void* a, void *b) const = 0;
    virtual R get(void* ptr) = 0;
    virtual C get(void* ptr) const = 0;
};

template <class S, typename T, typename R, typename C>
class MF : public MFEnumerable<R,C> {
public:
    // non-const iterator
    class iterator {
    private:
        MFEnumerable<R,C>* mf;
        char iter[sizeof(std::list<void*>::const_iterator)];
    public:
        iterator() {}
        iterator(MFEnumerable<R,C>* mf, bool end) : mf(mf) {
            if (end)
                mf->setEnd((void*) iter);
            else
                mf->setBegin((void*) iter);
        }
        R operator*() {
            return mf->get((void*) iter);
        }
        T* operator->() {
            return &(mf->get((void*) iter));
        }
        iterator operator++(int unused) {
            iterator it = *this;
            mf->advance((void*) iter);
            return it;
        }
        iterator operator++() {
            mf->advance((void*) iter);
            return *this;
        }
        bool operator==(const iterator& it) const {
            return !memcmp(iter, it.iter, sizeof(iter));
            //return mf->compare((void*) iter, (void*) it.iter);
        }
        bool operator!=(const iterator& it) const {
            return memcmp(iter, it.iter, sizeof(iter));
            //return !mf->compare((void*) iter, (void*) it.iter);
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
        const T* operator->() {
            return &(mf->get((void*) iter));
        }
        const_iterator operator++(int unused) {
            const_iterator it = *this;
            mf->advance((void*) iter);
            return it;
        }
        const_iterator operator++() {
            mf->advance((void*) iter);
            return *this;
        }
        bool operator==(const const_iterator& it) const {
            return !memcmp(iter, it.iter, sizeof(iter));
            //return mf->compare((void*) iter, (void*) it.iter);
        }
        bool operator!=(const const_iterator& it) const {
            return memcmp(iter, it.iter, sizeof(iter));
            //return !mf->compare((void*) iter, (void*) it.iter);
        }
    };
    // virtual functions
    virtual void add(C elem) = 0;
    virtual void clear() = 0;
    virtual void print(ostream& os) const = 0;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
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
    MF<S,T,R,C>& operator()(const X3DField& value) {
        throw X3DError("direct list assignment not supported");
    }
    const MF<S,T,R,C>& operator=(const MF<S,T,R,C>& mf) {
        clear();
        const_iterator it;
        for (it = mf.begin(); it != mf.end(); it++)
            add(*it);
        return *this;
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
    void print(ostream& os) const {
        typename parent::const_iterator it;
        for (it = parent::begin(); it != parent::end(); it++)
            os << *it << ",";
    }
};

/**
 * This abstract class exists so that you can access arbitrary
 * fields which you know to be MFNode<?>.
 */
class MFAbstractNode {
public:

    virtual void cloneInto(MFAbstractNode& target, std::map<Node*,Node*>* mapping=NULL, bool shallow=false) = 0;

    virtual void addNode(Node* node) = 0;

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

template <class N>
class MFNode : public MF<SFNode<N>, N*, N*, N*>, public MFAbstractNode {
public:
    typedef MF<SFNode<N>,N*,N*,N*> parent;
    void addNode(Node* node) {
        N* n = dynamic_cast<N*>(node);
        if (n == NULL)
            throw X3DError("node type mismatch");
        this->add(n); // XXX problem spot...
    }
    void print(ostream& os) const {
        SFNode<N> sf;
        typename parent::const_iterator it;
        for (it = parent::begin(); it != parent::end(); it++) {
            sf = *it;
            os << sf << ", ";
        }
    }
    void cloneInto(MFAbstractNode& abstract, std::map<Node*,Node*>* mapping=NULL, bool shallow=false) {
        MFNode<N>* mf = dynamic_cast<MFNode<N>*>(&abstract);
        if (mf == NULL)
            throw X3DError("node type mismatch");
        mf->clear();
        typename parent::iterator it;
        if (shallow) {
            for (it = parent::begin(); it != parent::end(); it++)
                mf->add(*it);
        } else {
            for (it = parent::begin(); it != parent::end(); it++)
                mf->add(SFNode<N>::clone(*it, mapping, shallow));
        }
    }
};

#define MF_ITER_IMPL(R,C) \
    void setBegin(void* ptr) { *((ITER*) ptr) = elements.begin(); } \
    void setBegin(void* ptr) const { *((CONST_ITER*) ptr) = elements.begin(); } \
    void setEnd(void* ptr) { *((ITER*) ptr) = elements.end(); } \
    void setEnd(void* ptr) const { *((CONST_ITER*) ptr) = elements.end(); } \
    void advance(void* ptr) { (*((ITER*) ptr))++; } \
    void advance(void* ptr) const { (*((CONST_ITER*) ptr))++; } \
    bool compare(void* a, void* b) { return *((ITER*) a) == *((ITER*) b); } \
    bool compare(void* a, void* b) const { return *((CONST_ITER*) a) == *((CONST_ITER*) b); } \
    R get(void* ptr) { return **((ITER*) ptr); } \
    C get(void* ptr) const { return **((CONST_ITER*) ptr); }

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
    virtual bool empty() const { return elements.empty(); }
    virtual int size() const { return elements.size(); }
    INLINE bool operator==(const MFList<S,T,R,C>& mf) const {
        return elements == mf.elements;
    }
    INLINE bool operator!=(const MFList<S,T,R,C>& mf) const {
        return elements != mf.elements;
    }
    INLINE bool operator==(const X3DField& field) const {
        return *this == unwrap(field);
    }
    INLINE bool operator!=(const X3DField& field) const {
        return *this != unwrap(field);
    }
    INLINE MFList<S,T,R,C>& operator()() { return *this; }
    INLINE const MFList<S,T,R,C>& operator()() const { return *this; }
    const MFList<S,T,R,C>& operator()(const MFBasic<S,T,R,C>& mf) {
        return *this = mf;
    }
    const MFList<S,T,R,C>& operator=(const MFBasic<S,T,R,C>& mf) {
        clear();
        typename MF<S,T,R,C>::const_iterator it;
        for (it = mf.begin(); it != mf.end(); it++)
            add(*it);
        return *this;
    }
    static INLINE const MFList<S,T,R,C>& unwrap(const X3DField& value) {
        static S sf;
        if (value.getType() != sf.getMFType())
            throw X3DError(
                string("base type mismatch; expected ") +
                sf.getMFTypeName() + ", but was " +
                value.getTypeName());
        const MFList<S,T,R,C>* mf = dynamic_cast<const MFList<S,T,R,C>*>(&value);
        if (mf == NULL)
            throw X3DError(
                "list type mismatch; expected list, but was array");
        return *mf;
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
    virtual bool empty() const { return elements.empty(); }
    virtual int size() const { return elements.size(); }
    INLINE bool operator==(const MFArray<S,T,R,C>& mf) const {
        return elements == mf.elements;
    }
    INLINE bool operator!=(const MFArray<S,T,R,C>& mf) const {
        return elements != mf.elements;
    }
    INLINE bool operator==(const X3DField& field) const {
        return *this == unwrap(field);
    }
    INLINE bool operator!=(const X3DField& field) const {
        return *this != unwrap(field);
    }
    INLINE MFArray<S,T,R,C>& operator()() { return *this; }
    INLINE const MFArray<S,T,R,C>& operator()() const { return *this; }
    const MFArray<S,T,R,C>& operator()(const MFBasic<S,T,R,C>& mf) {
        return *this = mf;
    }
    const MFArray<S,T,R,C>& operator=(const MFBasic<S,T,R,C>& mf) {
        clear();
        typename MF<S,T,R,C>::const_iterator it;
        for (it = mf.begin(); it != mf.end(); it++)
            add(*it);
        return *this;
    }
    static INLINE const MFArray<S,T,R,C>& unwrap(const X3DField& value) {
        static S sf;
        if (value.getType() != sf.getMFType())
            throw X3DError(
                string("base type mismatch; expected ") +
                sf.getMFTypeName() + ", but was " +
                value.getTypeName());
        const MFArray<S,T,R,C>* mf = dynamic_cast<const MFArray<S,T,R,C>*>(&value);
        if (mf == NULL)
            throw X3DError(
                "list type mismatch; expected array, but was list");
        return *mf;
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
    virtual void add(N* elem) {
        if (elem != NULL)
            elem->realize();
        elements.push_back(elem);
    }
    virtual void clear() { elements.clear(); }
    virtual bool empty() const { return elements.empty(); }
    virtual int size() const { return elements.size(); }
    INLINE bool operator==(const MFNodeList<N>& mf) const {
        return elements == mf.elements;
    }
    INLINE bool operator!=(const MFNodeList<N>& mf) const {
        return elements != mf.elements;
    }
    INLINE bool operator==(const X3DField& field) const {
        return *this == unwrap(field);
    }
    INLINE bool operator!=(const X3DField& field) const {
        return *this != unwrap(field);
    }
    INLINE MFNodeList<N>& operator()() { return *this; }
    INLINE const MFNodeList<N>& operator()() const { return *this; }
    const MFNodeList<N>& operator()(const MFNode<N>& mf) {
        return *this = mf;
    }
    const MFNodeList<N>& operator=(const X3DField& field) {
        return *this = unwrap(field);
    }
    const MFNodeList<N>& operator=(const MFNode<N>& mf) {
        clear();
        typename MFNode<N>::const_iterator it;
        for (it = mf.begin(); it != mf.end(); it++)
            add(*it);
        return *this;
    }
	static INLINE const MFNodeList<N>& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::MFNODE)
			throw X3DError(
                string("base type mismatch; expected MFNode") + \
                ", but was " + f.getTypeName()); \
		const MFNode<N>* mf = dynamic_cast<const MFNode<N>*>(&f);
        if (mf == NULL)
            throw X3DError("node type mismatch");
        const MFNodeList<N>* mflist = dynamic_cast<const MFNodeList<N>*>(mf);
        if (mflist == NULL)
            throw X3DError("list type mismatch");
        return *mflist;
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
    virtual void add(N* elem) {
        if (elem != NULL)
            elem->realize();
        elements.insert(elem);
    }
    virtual void clear() { elements.clear(); }
    virtual bool empty() const { return elements.empty(); }
    virtual int size() const { return elements.size(); }
    INLINE bool operator==(const MFNodeSet<N>& mf) const {
        return elements == mf.elements;
    }
    INLINE bool operator!=(const MFNodeSet<N>& mf) const {
        return elements != mf.elements;
    }
    INLINE bool operator==(const X3DField& field) const {
        return *this == unwrap(field);
    }
    INLINE bool operator!=(const X3DField& field) const {
        return *this != unwrap(field);
    }
    INLINE MFNodeSet<N>& operator()() { return *this; }
    INLINE const MFNodeSet<N>& operator()() const { return *this; }
    const MFNodeSet<N>& operator()(const MFNode<N>& mf) {
        return *this = mf;
    }
    const MFNodeSet<N>& operator=(const X3DField& field) {
        return *this = unwrap(field);
    }
    const MFNodeSet<N>& operator=(const MFNode<N>& mf) {
        clear();
        typename MFNode<N>::const_iterator it;
        for (it = mf.begin(); it != mf.end(); it++)
            add(*it);
        return *this;
    }
	static INLINE const MFNodeSet<N>& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::MFNODE)
			throw X3DError(
                string("base type mismatch; expected MFNode") + \
                ", but was " + f.getTypeName()); \
		const MFNode<N>* mf = dynamic_cast<const MFNode<N>*>(&f);
        if (mf == NULL)
            throw X3DError("node type mismatch");
        const MFNodeSet<N>* mfset = dynamic_cast<const MFNodeSet<N>*>(mf);
        if (mfset == NULL)
            throw X3DError("list type mismatch");
        return *mfset;
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
    virtual void add(N* elem) {
        if (elem != NULL)
            elem->realize();
        elements.push_back(elem);
    }
    virtual void clear() { elements.clear(); }
    virtual bool empty() const { return elements.empty(); }
    virtual int size() const { return elements.size(); }
    INLINE bool operator==(const MFNodeArray<N>& mf) const {
        return elements == mf.elements;
    }
    INLINE bool operator!=(const MFNodeArray<N>& mf) const {
        return elements != mf.elements;
    }
    INLINE bool operator==(const X3DField& field) const {
        return *this == unwrap(field);
    }
    INLINE bool operator!=(const X3DField& field) const {
        return *this != unwrap(field);
    }
    INLINE MFNodeArray<N>& operator()() { return *this; }
    INLINE const MFNodeArray<N>& operator()() const { return *this; }
    const MFNodeArray<N>& operator()(const MFNode<N>& mf) {
        return *this = mf;
    }
    const MFNodeArray<N>& operator=(const X3DField& field) {
        return *this = unwrap(field);
    }
    const MFNodeArray<N>& operator=(const MFNode<N>& mf) {
        clear();
        typename MFNode<N>::const_iterator it;
        for (it = mf.begin(); it != mf.end(); it++)
            add(*it);
        return *this;
    }
	static INLINE const MFNodeArray<N>& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::MFNODE)
			throw X3DError(
                string("base type mismatch; expected MFNode") + \
                ", but was " + f.getTypeName()); \
		const MFNode<N>* mf = dynamic_cast<const MFNode<N>*>(&f);
        if (mf == NULL)
            throw X3DError("node type mismatch");
        const MFNodeArray<N>* mfarr = dynamic_cast<const MFNodeArray<N>*>(mf);
        if (mfarr == NULL)
            throw X3DError("list type mismatch");
        return *mfarr;
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


}

#endif // #ifndef _X3D_MFFIELDS_H_
