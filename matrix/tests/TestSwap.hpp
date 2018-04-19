//
//  TestExchange.h
//  matrix
//
//  Created by Oleg Bakharev on 19/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//

#ifndef TestExchange_h
#define TestExchange_h

#include "SwapRowsCols.hpp"
#include <assert.h>

template<class M>
void testExchange (M& m) {
    using namespace std;
    using namespace LA;
    {
        auto m1 = swapRows(m, 0, 1);
        cout << "Swap row 0 & 1:\n" << m1;
        assert(m1.row(0) == m.row(1) && m1.row(1) == m.row(0) && m1.row(2) == m.row(2));
        auto m2 = swapRows(m, 1, 2);
        cout << "Swap col 1 & 2:\n" << m2;
        assert(m2.col(0) == m.col(0) && m2.col(1) == m.col(2) && m2.col(2) == m.col(1));
    }
    { // Const
        const auto m1 = swapRows(m, 0, 1);
        cout << "Const Swap row 0 & 1:\n" << m1;
        assert(m1.row(0) == m.row(1) && m1.row(1) == m.row(0) && m1.row(2) == m.row(2));
        const auto m2 = swapCols(m, 1, 2);
        cout << "Const Swap col 1 & 2:\n" << m2;
        assert(m2.col(0) == m.col(0) && m2.col(1) == m.col(2) && m2.col(2) == m.col(1));
    }
}

#endif /* TestExchange_h */
