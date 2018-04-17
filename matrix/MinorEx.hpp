//
//  MinorEx.h
//  matrix
//
//  Created by Oleg Bakharev on 11/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Минор произвольного порядка.

#ifndef MinorEx_h
#define MinorEx_h

#include "ForIterable.hpp"
#include "Ostreamable.hpp"
#include "Equitable.hpp"
#include "MatrixAdapter.hpp"
#include <assert.h>

namespace LA {
    
    template<typename Vector> class MinorExIter :
    public ForIterable<MinorExIter<Vector>>,
    public VectorEquitable<MinorIter<Vector>>,
    public VectorOstreamable<MinorIter<Vector>>
    {
        Vector _vector;
        size_t _index;
        size_t _order;
        
        size_t correctIndex_(size_t i) const { return i < _index ? i : i + _order; }
        
    public:
        using value_type = typename Vector::value_type;
        using reference = typename Vector::reference;
        using const_reference = typename Vector::const_reference;
        
        MinorExIter(const Vector& v, size_t i, size_t o) : _vector(v), _index(i), _order(o) {}
        
        size_t size() const { return _vector.size() - _order; }
        const_reference operator[](size_t i) const { return _vector[correctIndex_(i)]; }
        reference operator[](size_t i) { return _vector[correctIndex_(i)]; }
        
        // Вывод в поток
        friend std::ostream& operator << (std::ostream& os, const MinorExIter<Vector>& v) {
            for ( auto x : v ) {
                os << std::setw(2) << x << ", ";
            }
            return os << std::endl;
        }
    };
    
    ///////////////////////////////////////////
    // Cтрока минора.
    template <typename Matrix> class MinorExRow {
        size_t _row;
        size_t _col;
        size_t _order;
        
        size_t correctRow_(size_t i) const { return i < _row ? i : i + _order; }
        
    public:
        using reference = MinorExIter<typename Matrix::reference>;
        using const_reference = MinorExIter<typename Matrix::const_reference>;
        
        MinorExRow(size_t row, size_t col, size_t order) : _row(row), _col(col), _order(order) {}
        
        size_t size(const Matrix& m) const { return m.width() - _order; }
        reference operator()(Matrix& m, size_t i) { return reference(m.row(correctRow_(i)), _col, _order); }
        const_reference operator()(const Matrix& m, size_t i) const { return const_reference(m.row(correctRow_(i)), _col, _order); }
    };
    
    ///////////////////////////////////////////
    // Столбец минора.
    template <typename Matrix> class MinorExCol {
        size_t _row;
        size_t _col;
        size_t _order;
        
        size_t correctCol_(size_t i) const { return i < _col ? i : i + _order; }
        
    public:
        using reference = MinorExIter<typename Matrix::reference>;
        using const_reference = MinorExIter<typename Matrix::const_reference>;
        
        MinorExCol(size_t row, size_t col, size_t order) : _row(row), _col(col), _order(order) {}
        
        size_t size(const Matrix& m) const { return m.height() - _order; }
        reference operator()(Matrix& m, size_t i) { return reference(m.col(correctCol_(i)), _row, _order); }
        const_reference operator()(const Matrix& m, size_t i) const { return const_reference(m.col(correctCol_(i)), _row, _order); }
    };
    
    template <typename Matrix, typename ClearMatrix = typename std::remove_reference<Matrix>::type>
    MatrixAdapter<Matrix&&, MinorExRow<ClearMatrix>, MinorExCol<ClearMatrix>> minorEx(Matrix&& m, size_t row, size_t col, size_t order) {
        assert(m.height() >= row + order && m.width() >= col + order);
        return {m, {row, col, order}, {row, col, order}};
    }

} // namespace LA
#endif /* MinorEx_h */
