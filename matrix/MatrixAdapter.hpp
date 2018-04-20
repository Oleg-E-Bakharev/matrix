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
#include "ColIter.hpp"

namespace LA {
    
    // Matrix: матрица или другой адаптер.
    template<typename Matrix, typename RowsAccessor, typename ColsAccessor> class MatrixAdapter : CopylessHolder<Matrix>,
    public ForIterable<MatrixAdapter<Matrix, RowsAccessor, ColsAccessor>>,
    public MatrixOstreamable<MatrixAdapter<Matrix, RowsAccessor, ColsAccessor>>,
    public MatrixEquitable<MatrixAdapter<Matrix, RowsAccessor, ColsAccessor>>,
    public MatrixMultiplicable<MatrixAdapter<Matrix, RowsAccessor, ColsAccessor>>
    {
        using Base = CopylessHolder<Matrix>;
        using Base::data;
        using ClearMatrix = typename std::remove_reference<Matrix>::type;

        ColsAccessor _colsAccessor;
        RowsAccessor _rowsAccessor;
    public:
        using element_type = typename ClearMatrix::element_type;
        using instance_type = typename ClearMatrix::instance_type;
        using value_type = typename ClearMatrix::value_type;
        using reference = typename RowsAccessor::reference;
        using const_reference = typename RowsAccessor::const_reference;
        
        MatrixAdapter(Matrix&& m, const RowsAccessor& rowSlice, const ColsAccessor& colSlice) : Base{std::forward<Matrix>(m)}, _colsAccessor(colSlice), _rowsAccessor(rowSlice) {}
        explicit MatrixAdapter(const MatrixAdapter& m) = default;
        MatrixAdapter(MatrixAdapter&& m) = default;
        ~MatrixAdapter() { debugOut2("~MatrixAdapter", 99); }
        
        size_t width() const { return _rowsAccessor.size(data); }
        size_t height() const {return _colsAccessor.size(data); }
        
        size_t size() const { return height(); }
        
        reference row(size_t i) { return _rowsAccessor(data, i); }
        const_reference row(size_t i) const { return _rowsAccessor(data, i); }
        
        typename ColsAccessor::reference col(size_t j) { return _colsAccessor(data, j); }
        typename ColsAccessor::const_reference col(size_t j) const { return _colsAccessor(data, j); }
        
        reference operator[](size_t i) { return row(i); }
        const_reference operator[](size_t i) const { return row(i); }
      
        ColIterator<MatrixAdapter> columns() { return {*this}; }
        ConstColIterator<MatrixAdapter> columns() const { return {*this}; }

        instance_type clone() const {
            instance_type instance(width(), height());
            for (size_t i = 0; i < width(); i++) {
                for (size_t j = 0; j < height(); j++) {
                    instance[i][j] = (*this)[i][j];
                }
            }
            return instance;
        }
        
        static constexpr size_t generation() { return std::remove_reference<Matrix>::type::generation() + 1; }
    };
    
} // namespace LA

#endif /* matrix_adapter_h */

