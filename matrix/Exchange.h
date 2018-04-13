//
//  Exchange.h
//  matrix
//
//  Created by Oleg Bakharev on 13/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Обмен местами строк / столбцов.

#ifndef Exchange_h
#define Exchange_h

#include "ForIterable.h"
#include <assert.h>

namespace LA {
    
    // Вектор с перестановкой i, j индексов.
    template<typename Vector> class ExchangeIter : public ForIterable<MinorIter<Vector>> {
        Vector _vector;
        size_t _i;
        size_t _j;
    public:
        using value_type = typename Vector::value_type;
        using reference = typename Vector::reference;
        using const_reference = typename Vector::const_reference;

        ExchangeIter(const Vector& v, size_t i, size_t j) : _vector(v), _i(i), _j(j) {
            assert(i != j && i < v.size() && j < v.size());
        }
        
        reference operator[](size_t k) {
            if (k == _i) return _vector[_j];
            if (k == _j) return _vector[_i];
            return _vector[k];
        }
        
        const reference operator[](size_t k) const {
            if (k == _i) return _vector[_j];
            if (k == _j) return _vector[_i];
            return _vector[k];
        }
    };
    
} // namespace LA

#endif /* Exchange_h */
