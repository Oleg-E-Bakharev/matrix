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
#include <utility>

namespace LA {
    
    ///////////////////////////////////////////////////////////////////////
    // Транспонированная строка. т.е. столбец.
    template <typename Matrix> class TranspondRow :
    public VectorEquitable<TranspondRow<Matrix>>,
    public VectorOstreamable<TranspondRow<Matrix>>
    {
    public:
        using reference = typename Matrix::reference;
        using const_reference = typename Matrix::const_reference;

        size_t size(const Matrix& m) const { return m.height(); }
        reference operator()(Matrix& m, size_t i) { return m.col(i); }
        const_reference operator()(const Matrix& m, size_t i) const { return m.col(i); }
    };

    ///////////////////////////////////////////////////////////////////////
    // Транспонированный столбец. т.е. строка.
    template <typename Matrix> class TranspondCol :
    public VectorEquitable<TranspondCol<Matrix>>,
    public VectorOstreamable<TranspondRow<Matrix>>
    {
    public:
        using reference = typename Matrix::reference;
        using const_reference = typename Matrix::const_reference;
        
        size_t size(const Matrix& m) const { return m.width(); }
        reference operator()(Matrix& m, size_t i) { return m.row(i); }
        const_reference operator()(const Matrix& m, size_t i) const { return m.row(i); }
    };
    
    template <typename Matrix, typename ClearMatrix = typename std::remove_reference<Matrix>::type>
    inline MatrixAdapter<Matrix&&, TranspondRow<ClearMatrix>, TranspondCol<ClearMatrix>> transpond(Matrix&& m) {
        return {std::forward<Matrix>(m), {}, {}};
    }
    

} // namespace LA
    
#endif /* transpond_h */
