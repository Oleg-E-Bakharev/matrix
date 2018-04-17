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

template <typename Vector> class VectorEquitable {
public:
    // Оператор сравнения с любым другим вектором, в т.ч. реализованным другим классом.
    template <class Other>
    friend bool operator==(const Vector& v, const Other& o) {
        if (v.size() != o.size()) return false;
        for ( size_t j = 0; j < v.size(); j++ ) {
            if (v[j] != o[j]) return false;
        }
        return true;
    }
};

template <typename Matrix> class MatrixEquitable {
public:
    // Оператор сравнения с любой другой матрицей, в т.ч. реализованной другим классом.
    template <class Other>
    friend bool operator==(const Matrix& m, const Other& o) {
        if (m.width() != o.width()) return false;
        if (m.height() != o.height()) return false;
        for ( size_t i = 0; i < m.height(); i++ ) {
            for ( size_t j = 0; j < m.width(); j++ ) {
                if (m[i][j] != o[i][j]) return false;
            }
        }
        return true;
    }
};

#endif /* Equitable_h */
