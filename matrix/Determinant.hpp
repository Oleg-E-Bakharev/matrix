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

// -1^i
template <typename T> T m1pow(size_t i) {
    if (i % 2 == 0) return T(1);
    return T(-1);
}

template <typename Matrix> typename Matrix::element_type detDef(const Matrix& m) {
    using T = typename Matrix::element_type;
    assert(m.size() > 0 && m.width() == m.height());
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
        // Зацикливание компилятора!
        det += m1pow<T>(i) * detDef(minor(m, 0, i));
        det += m1pow<T>(i);// * detDef(minor(m, 0, i));

    }
    return det;
}

#endif /* determinant_h */
