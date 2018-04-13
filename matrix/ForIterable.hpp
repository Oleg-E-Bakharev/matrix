//
//  ForIterable.h
//  matrix
//
//  Created by Oleg Bakharev on 11/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Аспект класса для Range-based for.

#ifndef ForIterable_h
#define ForIterable_h

#include "ForIter.hpp"
#include <iostream>

template <typename T> class ForIterable {
    
public:
    using ForIter = ForIter<T>;
    ForIter begin() { return {*this}; }
    ForIter end() { return {*this}; }
    
    using ConstForIter = ConstForIter<T>;
    ConstForIter begin() const { return {static_cast<const T&>(*this)}; }
    ConstForIter end() const { return {static_cast<const T&>(*this)}; }
    
};

#endif /* ForIterable_h */
