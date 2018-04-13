//
//  Equitable.hpp
//  matrix
//
//  Created by Oleg Bakharev on 13/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//

#ifndef Equitable_h
#define Equitable_h

template <typename Matrix> class MatrixEquitable {
public:
    // Оператор сравнения с любой другой матрицей, в т.ч. реализованной другим классом.
    template <class Other> bool operator==(const Other& m) const {
        if (width() != m.width()) return false;
        if (height() != m.height()) return false;
        for ( size_t i = 0; i < height(); i++ ) {
            for ( size_t j = 0; j < width(); j++ ) {
                if ((*this)[i][j] != m[i][j]) return false;
            }
        }
        return true;
    }
}

template <typename Vector> class VectorEquitable {
    // Оператор сравнения с любым другим вектором, в т.ч. реализованным другим классом.
    template <class Other> bool operator==(const Other& m) const {
        for ( size_t j = 0; j < width(); j++ ) {
            if ((*this)[i][j] != m[i][j]) return false;
        }
    }
}

#endif /* Equitable_h */
