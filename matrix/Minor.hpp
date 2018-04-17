//
//  Minor.hpp
//  matrix
//
//  Created by Oleg Bakharev on 11/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Вычисление минора матрицы.

#ifndef Minor_h
#define Minor_h

#include "ForIterable.hpp"
#include "Ostreamable.hpp"
#include "Equitable.hpp"
#include "Multiplicable.hpp"
#include "MatrixAdapter.hpp"
#include <utility>

namespace LA {
    
    // Итератор строки или столбца минора.
    template<typename Vector> class MinorIter :
    public ForIterable<MinorIter<Vector>>,
    public VectorEquitable<MinorIter<Vector>>,
    public VectorOstreamable<MinorIter<Vector>>,
    public VectorMultiplicable<MinorIter<Vector>>
    {
        Vector _vector;
        size_t _index;
        
        size_t correctIndex_(size_t i) const { return i < _index ? i : i + 1; }
        
    public:
        using value_type = typename Vector::value_type;
        using reference = typename Vector::reference;
        using const_reference = typename Vector::const_reference;
        
        MinorIter(const Vector& v, size_t i) : _vector(v), _index(i) {}
        
        size_t size() const { return _vector.size() - 1; }
        const_reference operator[](size_t i) const { return _vector[correctIndex_(i)]; }
        reference operator[](size_t i) { return _vector[correctIndex_(i)]; }
    };
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // Cтрока минора.
    template <typename Matrix> class MinorRow {
        size_t _row;
        size_t _col;
        
        size_t correctRow_(size_t i) const { return i < _row ? i : i + 1; }
        
    public:
        using reference = MinorIter<typename Matrix::reference>;
        using const_reference = MinorIter<typename Matrix::const_reference>;
  
        // std::forward необходимо применять для правильной инициализации базы l-value или r-value ссылкой.
        MinorRow(size_t row, size_t col) : _row(row), _col(col) {}

        size_t size(const Matrix& m) const { return m.width() - 1; }
        reference operator()(Matrix& m, size_t i) { return {m.row(correctRow_(i)), _col}; }
        const_reference operator()(const Matrix& m, size_t i) const { return {m.row(correctRow_(i)), _col}; }
    };
    
    ////////////////////////////////////////////////////////////////
    // Столбец минора.
    template <typename Matrix> class MinorCol {
        size_t _row;
        size_t _col;
        
        size_t correctCol_(size_t i) const { return i < _col ? i : i + 1; }
        
    public:
        using reference = MinorIter<typename Matrix::reference>;
        using const_reference = MinorIter<typename Matrix::const_reference>;
        
        // std::forward необходимо применять для правильной инициализации базы l-value или r-value ссылкой.
        MinorCol(size_t row, size_t col) : _row(row), _col(col) {}

        size_t size(const Matrix& m) const { return m.height() - 1; }
        reference operator()(Matrix& m, size_t i) { return {m.col(correctCol_(i)), _row}; }
        const_reference operator()(const Matrix& m, size_t i) const { return {m.col(correctCol_(i)), _row}; }
    };
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Создание минора.
    // std::forward необходимо применять для правильной инициализации базы l-value или r-value ссылкой.
    template <typename Matrix, typename ClearMatrix = typename std::remove_reference<Matrix>::type>
    MatrixAdapter<Matrix&&, MinorRow<ClearMatrix>, MinorCol<ClearMatrix>> minor(Matrix&& m, size_t row, size_t col) {
        assert(m.height() >= row + 1 && m.width() >= col + 1);
        return {{std::forward<Matrix>(m)}, {row, col}, {row, col}};
    }
    
} // namespace LA

#endif /* Minor_h */

