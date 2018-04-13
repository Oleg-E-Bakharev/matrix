//
//  Equitable.hpp
//  matrix
//
//  Created by Oleg Bakharev on 13/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
// Аспект класса для сравнения.

#ifndef Equitable_h
#define Equitable_h

template <typename Matrix> class MatrixEquitable {
public:
    // Оператор сравнения с любой другой матрицей, в т.ч. реализованной другим классом.
    template <class Other>
    friend bool operator==(const Matrix& m1, const Other& m2) {
        if (m1.width() != m2.width()) return false;
        if (m1.height() != m2.height()) return false;
        for ( size_t i = 0; i < m1.height(); i++ ) {
            for ( size_t j = 0; j < m1.width(); j++ ) {
                if (m1[i][j] != m2[i][j]) return false;
            }
        }
        return true;
    }
};

template <typename Vector> class VectorEquitable {
public:
    // Оператор сравнения с любым другим вектором, в т.ч. реализованным другим классом.
    template <class Other>
    friend bool operator==(const Vector& v1, const Other& v2) {
        if (v1.size() != v2.size()) return false;
        for ( size_t j = 0; j < v1.size(); j++ ) {
            if (v1[j] != v2[j]) return false;
        }
        return true;
    }
};

#endif /* Equitable_h */
