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

#include "ForIterable.hpp"
#include "Ostreamable.hpp"
#include "Equitable.hpp"
#include "Multiplicable.hpp"
#include <assert.h>

namespace LA {
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Вектор с перестановкой i, j индексов.
    template<typename Vector> class ExchangeIter :
    public ForIterable<ExchangeIter<Vector>>,
    public VectorEquitable<ExchangeIter<Vector>>,
    public VectorOstreamable<ExchangeIter<Vector>>,
    public VectorMultiplicable<ExchangeIter<Vector>>
    {
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
        
        const_reference operator[](size_t k) const {
            if (k == _i) return _vector[_j];
            if (k == _j) return _vector[_i];
            return _vector[k];
        }
    };
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // Строковый аксессор перестановщика.
    template <typename Matrix> class ExchangeRows {
        size_t _i;
        size_t _j;

    public:
        using reference = ExchangeIter<typename Matrix::reference>;
        using const_reference = ExchangeIter<typename Matrix::const_reference>;
        
        ExchangeRows(size_t i, size_t j) : _i(i), _j(j) {}
        
        size_t size(const Matrix& m) const { return m.height(); }
        reference operator()(Matrix& m, size_t i) { return {m.row(i), _i, _j}; }
        const_reference operator()(const Matrix& m, size_t i) const { return {m.row(i), _i, _j}; }
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Столбцовый аксессор перестановщика.
    template <typename Matrix> class ExchangeCols {
        size_t _i;
        size_t _j;
        
    public:
        using reference = ExchangeIter<typename Matrix::reference>;
        using const_reference = ExchangeIter<typename Matrix::const_reference>;

        ExchangeCols(size_t i, size_t j) : _i(i), _j(j) {}
        
        size_t size(const Matrix& m) const { return m.width(); }
        reference operator()(Matrix& m, size_t i) { return {m.col(i), _i, _j}; }
        const_reference operator()(const Matrix& m, size_t i) const { return {m.col(i), _i, _j}; }
    };
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Exchange Rows
    template <typename Matrix, typename ClearMatrix = typename std::remove_reference<Matrix>::type>
    inline MatrixAdapter<Matrix&&, ExchangeRows<ClearMatrix>, IdentifyColAccessor<ClearMatrix>>
    exchangeRows(Matrix&& m, size_t i, size_t j) {
        return {std::forward<Matrix>(m), {i, j}, {}};
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Exchange Cols
    template <typename Matrix, typename ClearMatrix = typename std::remove_reference<Matrix>::type>
    inline MatrixAdapter<Matrix&&, IdentifyRowAccessor<ClearMatrix>, ExchangeCols<ClearMatrix>>
    exchangeRows(Matrix&& m, size_t i, size_t j) {
        return {std::forward<Matrix>(m), {}, {i, j}};
    }

} // namespace LA

#endif /* Exchange_h */
