//
//  Debug.hpp
//  matrix
//
//  Created by Oleg Bakharev on 17/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//

#ifndef Debug_h
#define Debug_h

#include <assert.h>
#include <iostream>

static constexpr size_t DebugLevel = 0;

#ifdef NDEBUG
#define debugOut2(m, l) ((void)0)
#else
#define debugOut2(m, l) {if (l <= DebugLevel) {std::cout << m << "\n";}}
#endif

#ifdef NDEBUG
#define debugOut(m) ((void)0)
#else
#define debugOut(m) (std::cout << m << "\n")
#endif

#endif /* Debug_h */
