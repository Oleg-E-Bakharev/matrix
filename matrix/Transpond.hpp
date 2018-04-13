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

#include "MatrixAdapter.hpp"

namespace LA {
    
    // Транспонированная строка. т.е. столбец.
    template <typename Matrix> class TranspondRow {
        Matrix& _mat;
    public:
        using reference = typename Matrix::reference;
        using const_reference = typename Matrix::const_reference;
        
        TranspondRow(Matrix& m) : _mat(m) {}
        
        size_t size() const { return _mat.height(); }
        reference operator()(size_t i) { return _mat.col(i); }
        const_reference operator()(size_t i) const { return (const_cast<const Matrix&>(_mat)).col(i); }
    };
    
    //////////////////////////////////////////////////////////////////////
    // Транспонированный столбец. т.е. строка.
    template <typename Matrix> class TranspondCol {
        Matrix& _mat;
    public:
        using reference = typename Matrix::reference;
        using const_reference = typename Matrix::const_reference;
        
        TranspondCol(Matrix& m) : _mat(m) {}
        
        size_t size() const { return _mat.width(); }
        reference operator()(size_t i) { return _mat.row(i); }
        const_reference operator()(size_t i) const { return (const_cast<const Matrix&>(_mat)).row(i); }
    };
    
    template <typename Matrix>
    MatrixAdapter<Matrix, TranspondRow<Matrix>, TranspondCol<Matrix>>  transpond(Matrix& m) {
        return {{m}, {m}};
    }    

} // namespace LA
    
#endif /* transpond_h */
