//
//  TestDet.hpp
//  matrix
//
//  Created by Oleg Bakharev on 19/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//

#ifndef testDet_h
#define testDet_h

#include "Determinant.hpp"

using namespace std;
using namespace LA;

template <typename M> void testDet(const M& m) {
    cout << "Determinant of:\n" << m;
    auto det = detDef(m);
    cout << "is: " << det << "\n";
}

#endif /* testDet_h */
