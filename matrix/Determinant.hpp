//
//  determinant.hpp
//  matrix
//
//  Created by Oleg Bakharev on 12/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//

#ifndef determinant_h
#define determinant_h

#include "Minor.hpp"
#include <assert.h>

#include <random>

// Вычисление определителя матрицы по определению.
template <typename Matrix> class DeterminantDefault {
    using T = typename Matrix::element_type;
    T _det = 0;
    
    // -1^i
    T m1pow_(size_t i) {
        if (i % 2 == 0) return T(1);
        return T(-1);
    }
    
    template <typename Matrix2> typename Matrix2::element_type detDefA_(const Matrix2& m) {
        switch (m.size()) {
            case 1:
                return m[0][0];
            case 2:
                return m[0][0] * m[1][1] - m[0][1]*m[1][0];
                
            default:
                break;
        }
        T det = 0;
        for (size_t i = 0; i < m.size(); i++) {
            // Разрыв бесконечного зацикливания компилятора.
            auto min = minor(m, 0, i);
            auto *minp = reinterpret_cast<Matrix2*>(&min);
            det += m1pow_(i) * m[0][i] * detDefA_(*minp);
        }
        return det;
    }

public:
    DeterminantDefault( const Matrix& m) {
        using T = typename Matrix::element_type;
        assert(m.size() > 0 && m.width() == m.height());
        if (m.size() < 3) {
            _det = detDefA_(m);
            return;
        }
        for (size_t i = 0; i < m.size(); i++) {
            auto min = minor(m, 0, i);
            _det += m1pow_(i) * m[0][i] * detDefA_(min);
        }
    }
    
    T operator()() const { return _det; }
    operator T() const { return _det; }
};

template<typename Matrix> typename Matrix::element_type detDef(const Matrix& m) { return DeterminantDefault<Matrix>{m}(); }

#endif /* determinant_h */
