//
//  matrix_adapter.hpp
//  matrix
//
//  Created by Oleg Bakharev on 11/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
// Адаптер матрицы. Надстройка поверх матрицы для преобразования её с помощью срезов.

#ifndef matrix_adapter_h
#define matrix_adapter_h

#include "ForIterable.hpp"
#include "Ostreamable.hpp"
#include "Equitable.hpp"

namespace LA {
    
    // Matrix: матрица или другой адаптер.
    template<typename Matrix, typename RowSlice, typename ColSlice> class MatrixAdapter :
    public ForIterable<MatrixAdapter<Matrix, RowSlice, ColSlice>>,
    public MatrixOstreamable<MatrixAdapter<Matrix, RowSlice, ColSlice>>,
    public MatrixEquitable<MatrixAdapter<Matrix, RowSlice, ColSlice>>
    {
        ColSlice _colSlice;
        RowSlice _rowSlice;
    public:
        using instance_type = typename Matrix::instance_type;
        using value_type = typename Matrix::value_type;
        using reference = typename RowSlice::reference;
        using const_reference = typename RowSlice::const_reference;
        
        MatrixAdapter(const RowSlice& rowSlice, const ColSlice& colSlice) : _colSlice(colSlice), _rowSlice(rowSlice) {}
        
        size_t width() const { return _rowSlice.size(); }
        size_t height() const {return _colSlice.size(); }
        
        size_t size() const { return height(); }
        
        reference row(size_t i) { return _rowSlice(i); }
        const_reference row(size_t i) const { return _rowSlice(i); }
        
        reference col(size_t j) { return _colSlice(j); }
        const_reference col(size_t j) const { return _colSlice(j); }
        
        reference operator[](size_t i) { return row(i); }
        const_reference operator[](size_t i) const { return row(i); }
        
        instance_type clone() const {
            instance_type instance(width(), height());
            for (size_t i = 0; i < width(); i++) {
                for (size_t j = 0; j < height(); j++) {
                    instance[i][j] = (*this)[i][j];
                }
            }
            return instance;
        }
    };
    
} // namespace LA

#endif /* matrix_adapter_h */

