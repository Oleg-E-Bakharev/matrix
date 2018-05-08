//
//  main.cpp
//  matrix
//
//  Created by Oleg Bakharev on 06.02.17.
//  Copyright © 2017 Oleg Bakharev. All rights reserved.
//

//clang 3.8.0

#include <iostream>
#include <iomanip>
#include "testMatrix.hpp"

using namespace std;

#include <vector>
#include "Ostreamable.hpp"
#include "Multiplicable.hpp"

class MyVector : public vector<int>,
    public VectorOstreamable<MyVector>,
    public VectorMultiplicable<MyVector>
{
public:
    using vector::vector;
};

class MyMatrix : public vector<MyVector>,
public MatrixOstreamable<MyMatrix>
{
public:
    using vector::vector;
};

int main()
{
//    MyMatrix m {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
//    cout << m;
//    cout << m[0] * m[1];
    testMatrix();
}
