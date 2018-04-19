//
//  Swap.h
//  matrix
//
//  Created by Oleg Bakharev on 13/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Обмен местами строк / столбцов.

#ifndef Swap_h
#define Swap_h

#include "ForIterable.hpp"
#include "Equitable.hpp"
#include "Ostreamable.hpp"
#include "Multiplicable.hpp"
#include <assert.h>

namespace LA {
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Вектор с перестановкой i, j индексов.
    template<typename Vector> class SwapIter :
    public ForIterable<SwapIter<Vector>>,
    public VectorEquitable<SwapIter<Vector>>,
    public VectorOstreamable<SwapIter<Vector>>,
    public VectorMultiplicable<SwapIter<Vector>>
    {
        Vector _vector;
        size_t _i;
        size_t _j;
        
        size_t correctItem_(size_t i) const { return i == _i ? _j : i == _j ? _i : i; }
    public:
        using value_type = typename Vector::value_type;
        using reference = typename Vector::reference;
        using const_reference = typename Vector::const_reference;
        
        SwapIter(const Vector& v, size_t i, size_t j) : _vector(v), _i(i), _j(j) {
            assert(i != j && i < v.size() && j < v.size());
        }
        
        size_t size() const { return _vector.size(); }
        reference operator[](size_t k) { return _vector[correctItem_(k)]; }
        const_reference operator[](size_t k) const { return _vector[correctItem_(k)]; }
    };

    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // Строковый аксессор перестановщика.
    template <typename Matrix> class SwapRows {
        size_t _i;
        size_t _j;

        size_t correctRow_(size_t i) const { return i == _i ? _j : i == _j ? _i : i; }
    public:
        using reference = typename Matrix::reference;
        using const_reference = typename Matrix::const_reference;
        
        SwapRows(size_t i, size_t j) : _i(i), _j(j) {}
        
        size_t size(const Matrix& m) const { return m.height(); }
        reference operator()(Matrix& m, size_t i) { return m.row(correctRow_(i)); }
        const_reference operator()(const Matrix& m, size_t i) const { return {m.row(correctRow_(i))}; }
    };

    // Стобцы в матрице с перестановленными строками должны возвращать хитрый итератор.
    template <typename Matrix> class SwapRowsCols {
        size_t _i;
        size_t _j;
        
    public:
        using reference = SwapIter<typename Matrix::reference>;
        using const_reference = SwapIter<typename Matrix::const_reference>;
        
        SwapRowsCols(size_t i, size_t j) : _i(i), _j(j) {}
        
        size_t size(const Matrix& m) const { return m.height(); }
        reference operator()(Matrix& m, size_t k) { return {m.col(k), _i, _j}; }
        const_reference operator()(const Matrix& m, size_t k) const { return {m.col(k), _i, _j}; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Столбцовый аксессор перестановщика.
    template <typename Matrix> class SwapCols {
        size_t _i;
        size_t _j;
        
        size_t correctCol_(size_t i) const { return i == _i ? _j : i == _j ? _i : i; }
    public:
        using reference = typename Matrix::reference;
        using const_reference = typename Matrix::const_reference;

        SwapCols(size_t i, size_t j) : _i(i), _j(j) {}
        
        size_t size(const Matrix& m) const { return m.width(); }
        reference operator()(Matrix& m, size_t i) { return m.col(correctCol_(i)); }
        const_reference operator()(const Matrix& m, size_t i) const { return {m.col(correctCol_(i))}; }
    };
    
    // Стобцы в матрице с перестановленными строками должны возвращать хитрый итератор.
    template <typename Matrix> class SwapColsRows {
        size_t _i;
        size_t _j;
        
    public:
        using reference = SwapIter<typename Matrix::reference>;
        using const_reference = SwapIter<typename Matrix::const_reference>;
        
        SwapColsRows(size_t i, size_t j) : _i(i), _j(j) {}
        
        size_t size(const Matrix& m) const { return m.height(); }
        reference operator()(Matrix& m, size_t k) { return {m.row(k), _i, _j}; }
        const_reference operator()(const Matrix& m, size_t k) const { return {m.row(k), _i, _j}; }
    };
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Swap Rows
    template <typename Matrix, typename ClearMatrix = typename std::remove_reference<Matrix>::type>
    inline MatrixAdapter<Matrix&&, SwapRows<ClearMatrix>, SwapRowsCols<ClearMatrix>>
    swapRows(Matrix&& m, size_t i, size_t j) {
        assert(i != j && i < m.size() && j < m.size());
        return {std::forward<Matrix>(m), {i, j}, {i, j}};
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Swap Cols
    template <typename Matrix, typename ClearMatrix = typename std::remove_reference<Matrix>::type>
    inline MatrixAdapter<Matrix&&, SwapColsRows<ClearMatrix>, SwapCols<ClearMatrix>>
    swapCols(Matrix&& m, size_t i, size_t j) {
        assert(i != j && i < m.size() && j < m.size());
        return {std::forward<Matrix>(m), {i, j}, {i, j}};
    }

} // namespace LA

#endif /* Swap_h */
