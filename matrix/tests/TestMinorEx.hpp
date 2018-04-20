//
//  TestMinorEx.hpp
//  matrix
//
//  Created by Oleg Bakharev on 19/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//

#ifndef TestMinorEx_h
#define TestMinorEx_h

#include "MinorEx.hpp"

using namespace std;
using namespace LA;

template <class M>
void testMinorEx(M& m)
{
    auto m4 = minorEx(m, {0, 1}, {0, 1});
    cout << m4;
    assert(m4 == Matrix<int>({{1, 2}, {4, 10}}));
    assert(minorEx(m, {1, 2}, {1, 2}) == M({{10, 6}, {8, 99}}));
    assert(minorEx(m, {0, 2}, {0, 2}) == M({{1, 3}, {7, 99}}));
}

#endif /* TestMinorEx_h */
