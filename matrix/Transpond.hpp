//
//  transpond.hpp
//  matrix
//
//  Created by Oleg Bakharev on 11/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
// Транспонирование матрицы.

#ifndef transpond_h
#define transpond_h

#include "Equitable.hpp"
#include "Ostreamable.hpp"
#include "MatrixAdapter.hpp"
#include "Multiplicable.hpp"
#include "IdentityAccessor.h"
#include <utility>

namespace LA {
    
    // Возвращаем вместо строк столбцы, а вместо столбцов строки.
    template <typename Matrix, typename ClearMatrix = typename std::remove_reference<Matrix>::type>
    inline MatrixAdapter<Matrix&&, IdentifyColAccessor<ClearMatrix>, IdentifyRowAccessor<ClearMatrix>> transpond(Matrix&& m) {
        return {std::forward<Matrix>(m), {}, {}};
    }
} // namespace LA
    
#endif /* transpond_h */
