//
//  testMinor.h
//  matrix
//
//  Created by Oleg Bakharev on 19/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//

#ifndef testMinor_h
#define testMinor_h

#include "Minor.hpp"

using namespace std;
using namespace LA;

template <class M>
void testMinor(M& m)
{
    using V = vector<int>;

    cout << "Minor 0, 0:\n" << minor(m, 0, 0);
    cout << "Minor 2, 2:\n" << minor(m, 2, 2);
    
    cout << "Minor 0, 0 * minor 2, 2:\n" << minor(m, 0, 0) * minor(m, 2, 2);
    
    auto m2 = minor(m, 1, 1);
    cout << "col 1:" << m2.col(1);
    assert(m2.col(1) == V({3, 9}));
    cout << "row 1:" <<  m2.row(1);
    assert(m2.row(1) == V({7, 9}));
    assert(m2 == M({{1, 3}, {7, 9}}));
    
    cout << "\nMinor transpond:\n" << minor(transpond(m), 1, 1);
    
    auto m3 = minor(transpond(m), 1, 1);
    m3[1][1] = 99;

    auto m5 = m3.clone();
    cout << m5;
    
    cout << "Minor transpond modified:\n" << m3;
    cout << "Initial matrix after transpond minor changed:\n" << m;
}

#endif /* testMinor_h */
