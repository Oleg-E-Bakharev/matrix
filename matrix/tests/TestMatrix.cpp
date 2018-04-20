//
//  testMatrix.cpp
//  matrix
//
//  Created by Oleg Bakharev on 11/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//

#include "TestMatrix.hpp"
#include "Matrix.hpp"
#include "Transpond.hpp"
#include "Minor.hpp"
#include "MinorEx.hpp"
#include "SwapRowsCols.hpp"
#include <vector>
#include "Debug.hpp"

#include "TestTranspond.hpp"
#include "TestSwap.hpp"
#include "TestMinor.hpp"
#include "TestMinorEx.hpp"
#include "TestDet.hpp"

using namespace std;
using namespace LA;

void testMatrix() {
    
    using M = Matrix<int>;
    M m{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    
    cout << m;
    
    cout << m * m;
    
    m[1][1] = 10;
    
    cout << m;

    testTranspond(m, M{
        {1, 4, 7},
        {2, 10, 8},
        {3, 6, 9}
    });
    
    testExchange(m);

    testMinor(m);

    testMinorEx(m);
    
    cout << m;
    
    M m2 = {
        {1, 2, 3},
        {4, -5, 6},
        {7, 8, 9}};
    
    testDet(m2);

    auto m6(std::move(m));
    cout << m6;
    
// cout << m; Fails!
//    cout << m * m;
//
//    cout << m * m1;
    
//    for (auto col : for_iter(m.cols())) {
//        cout << col;
//    }
// */
}
