//
//  SliceIter.hpp
//  matrix
//
//  Created by Oleg Bakharev on 11/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Срез-итератор. А-ля Страуструп: http://www.stroustrup.com/matrix.c

#ifndef SliceIter_h
#define SliceIter_h

#include "ForIterable.hpp"
#include "Ostreamable.hpp"
#include "Equitable.hpp"
#include <valarray>

// Срез-итератор. А-ля Страуструп: http://www.stroustrup.com/matrix.c
template<typename Container> class SliceIter :
public ForIterable<SliceIter<Container>>,
public VectorOstreamable<SliceIter<Container>>,
public VectorEquitable<SliceIter<Container>>
{
    Container& v;
    std::slice s;
    
    typename Container::reference ref(size_t i) const { return v[s.start() + i * s.stride()]; }
    
public:
    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    SliceIter(Container& v, std::slice s) : v(v), s(s) {}
    
    size_t size() const { return s.size(); }
    const_reference operator[](size_t i) const { return ref(i); }
    reference operator[](size_t i) { return ref(i); }
};

///////////////////////////////////////////////
// То же но, константное.
template<typename Container> class ConstSliceIter :
public ForIterable<ConstSliceIter<Container>>,
public VectorOstreamable<ConstSliceIter<Container>>,
public VectorEquitable<SliceIter<Container>>
{
    const Container& v;
    std::slice s;
    
public:
    using value_type = typename Container::value_type;
    using reference = typename Container::const_reference;
    using const_reference = typename Container::const_reference;
    ConstSliceIter(const Container& v, std::slice s) : v(v), s(s) {}
    
    size_t size() const { return s.size(); }
    const_reference operator[](size_t i) const { return v[s.start() + i * s.stride()]; }
};

#endif /* SliceIter_h */
