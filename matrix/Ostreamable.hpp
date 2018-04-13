//
//  Ostreamable.hpp
//  matrix
//
//  Created by Oleg Bakharev on 13/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Адаптер контейнеров для вывода в std::ostream

#ifndef Ostreamable_h
#define Ostreamable_h

#include <iostream>
#include <iomanip>

template <typename Matrix> class MatrixOstreamable {
public:
    // Вывод в поток матрицы
    friend std::ostream& operator << (std::ostream& os, const Matrix& m) {
        for (auto row : m) {
            os << row;
        }
        return os << "\n\n";
    }
};

template <typename Vector> class VectorOstreamable {
public:
    // Вывод в поток вектора
    friend std::ostream& operator << (std::ostream& os, const Vector& v) {
        for (auto x : v) {
            os << std::setw(2) << x << ", ";
        }
        return os << "\n";
    }
};

#endif /* Ostreamable_h */
