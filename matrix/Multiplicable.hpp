//
//  Multiplicable.h
//  matrix
//
//  Created by Oleg Bakharev on 17/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Аспект для перемножения

#ifndef Multiplicable_h
#define Multiplicable_h

#include <assert.h>

template <class Vector> class VectorMultiplicable {
public:
    template <class Other>
    // Не можем использовать Vector::instance_type отому что мы база Vector, но можем использовать Other::value_type.
    friend typename Other::value_type operator*(const Vector& v, const Other& o) {
        typename Vector::value_type result = 0;
        for (size_t i = 0; i < v.size(); i++) {
            result += v[i] * o[i];
        }
        return result;
    }
};

template <class Matrix> class MatrixMultiplicable {
public:
    template <class Other>
    // Не можем использовать Matrix::instance_type отому что мы база Matrix, но можем использовать Other::instance_type.
    friend typename Other::instance_type operator*(const Matrix& m, const Other& o) {
        assert(m.width() == o.height());
        typename Matrix::instance_type result(m.height(), o.width());
        for (size_t i = 0; i < m.height(); i++) {
            for (size_t j = 0; j < o.width(); j++) {
                result[i][j] = m.row(i) * o.col(j);
            }
        }
        return result;
    }
};

#endif /* Multiplicable_h */
