//
//  TestTranspond.hpp
//  matrix
//
//  Created by Oleg Bakharev on 19/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//

#ifndef TestTranspond_hpp
#define TestTranspond_hpp

#include "Transpond.hpp"

using namespace std;
using namespace LA;

template <class M1, class M2>
void testTranspond(M1& m, const M2& check)
{
    cout << "Transpond:\n"<< transpond(m);
    auto m1 = transpond(m);
    assert(m1 == check);
    assert(m.row(0) == check.col(0));
    assert(m == transpond(m1));
    assert(m == transpond(transpond(m)));
    assert(m == transpond(transpond(m)).clone());
    
    cout << m * transpond(m);
}

#endif /* TestTranspond_hpp */
