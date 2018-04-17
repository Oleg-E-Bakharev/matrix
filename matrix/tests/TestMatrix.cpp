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
#include <vector>
#include "Debug.hpp"

using namespace std;
using namespace LA;

void testMatrix() {
    
    using M = Matrix<int>;
    using V = vector<int>;
    M m{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    
    cout << m;
    
    cout << m * m;
    
    m[1][1] = 10;
    
    cout << m;
    cout << "Transpond:\n"<< transpond(m);
    auto m1 = transpond(m);
    assert(m1 == M({
        {1, 4, 7},
        {2, 10, 8},
        {3, 6, 9}
    }));
    assert(m == transpond(m1));
    assert(m == transpond(transpond(m)));
    
    cout << m * transpond(m);

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
    
    auto m4 = minorEx(m, 0, 0, 2);
    cout << m4;
    assert(m4 == Matrix<int>({{99}}));
    assert(minorEx(m, 1, 1, 2) == Matrix<int>({{1}}));
    
    Matrix<int> m6(std::move(m));
    
    cout << m6;
//    cout << m * m;
//
//    cout << m * m1;
    
//    for (auto col : for_iter(m.cols())) {
//        cout << col;
//    }
// */
}
