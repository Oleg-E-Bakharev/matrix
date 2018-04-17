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

#include "Debug.hpp"
#include "CopylessHolder.hpp"
#include "ForIterable.hpp"
#include "Ostreamable.hpp"
#include "Equitable.hpp"
#include "Multiplicable.hpp"

namespace LA {
    
    // Matrix: матрица или другой адаптер.
    template<typename Matrix, typename RowSlice, typename ColSlice> class MatrixAdapter : CopylessHolder<Matrix>,
    public ForIterable<MatrixAdapter<Matrix, RowSlice, ColSlice>>,
    public MatrixOstreamable<MatrixAdapter<Matrix, RowSlice, ColSlice>>,
    public MatrixEquitable<MatrixAdapter<Matrix, RowSlice, ColSlice>>,
    public MatrixMultiplicable<MatrixAdapter<Matrix, RowSlice, ColSlice>>
    {
        using Base = CopylessHolder<Matrix>;
        using Base::data;
        using ClearMatrix = typename std::remove_reference<Matrix>::type;

        ColSlice _colSlice;
        RowSlice _rowSlice;
    public:
        using instance_type = typename ClearMatrix::instance_type;
        using value_type = typename ClearMatrix::value_type;
        using reference = typename RowSlice::reference;
        using const_reference = typename RowSlice::const_reference;
        
        MatrixAdapter(Matrix&& m, const RowSlice& rowSlice, const ColSlice& colSlice) : Base{std::forward<Matrix>(m)}, _colSlice(colSlice), _rowSlice(rowSlice) {}
        explicit MatrixAdapter(const MatrixAdapter& m) = default;
        MatrixAdapter(MatrixAdapter&& m) = default;
        ~MatrixAdapter() { debugOut2("~MatrixAdapter", 99); }
        
        size_t width() const { return _rowSlice.size(data); }
        size_t height() const {return _colSlice.size(data); }
        
        size_t size() const { return height(); }
        
        reference row(size_t i) { return _rowSlice(data, i); }
        const_reference row(size_t i) const { return _rowSlice(data, i); }
        
        reference col(size_t j) { return _colSlice(data, j); }
        const_reference col(size_t j) const { return _colSlice(data, j); }
        
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

