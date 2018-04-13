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
#include "MatrixAdapter.hpp"

namespace LA {
    
    template<typename Vector> class MinorIter : public
    ForIterable<MinorIter<Vector>>,
    VectorEquitable<MinorIter<Vector>>
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
        
        // Вывод в поток
        friend std::ostream& operator << (std::ostream& os, const MinorIter<Vector>& v) {
            for ( auto x : v ) {
                os << std::setw(2) << x << ", ";
            }
            return os << std::endl;
        }
    };
    
    ///////////////////////////////////////////
    // Cтрока минора.
    template <typename Matrix> class MinorRow {
        Matrix& _mat;
        size_t _row;
        size_t _col;
        size_t correctRow_(size_t i) const { return i < _row ? i : i + 1; }
    public:
        using reference = MinorIter<typename Matrix::reference>;
        using const_reference = MinorIter<typename Matrix::const_reference>;
        
        MinorRow(Matrix& m, size_t row, size_t col) : _mat(m), _row(row), _col(col) {
            assert(m.height() >= row + 1 && m.width() >= col + 1);
        }
        
        size_t size() const { return _mat.width() - 1; }
        reference operator()(size_t i) { return {_mat.row(correctRow_(i)), _col}; }
        const_reference operator()(size_t i) const { return {(const_cast<const Matrix&>(_mat)).row(correctRow_(i)), _col}; }
    };
    
    ///////////////////////////////////////////
    // Столбец минора.
    template <typename Matrix> class MinorCol {
        Matrix& _mat;
        size_t _row;
        size_t _col;
        size_t correctCol_(size_t i) const { return i < _col ? i : i + 1; }
    public:
        using reference = MinorIter<typename Matrix::reference>;
        using const_reference = MinorIter<typename Matrix::const_reference>;

        MinorCol(Matrix& m, size_t row, size_t col) : _mat(m), _row(row), _col(col) {
            assert(m.height() >= row + 1 && m.width() >= col + 1);
        }
        
        size_t size() const { return _mat.height() - 1; }
        reference operator()(size_t i) { return {_mat.col(correctCol_(i)), _row}; }
        const_reference operator()(size_t i) const { return {(const_cast<const Matrix&>(_mat)).col(correctCol_(i)), _row}; }
    };
    
    // L-Value matrix
    template <typename Matrix>
    MatrixAdapter<Matrix, MinorRow<Matrix>, MinorCol<Matrix>> minor(Matrix& m, size_t row, size_t col) {
        return {{m, row, col}, {m, row, col}};
    }
    
    // R-Value matrix
    template <typename Matrix>
    MatrixAdapter<Matrix, MinorRow<Matrix>, MinorCol<Matrix>> minor(Matrix&& m, size_t row, size_t col) {
        return {{m, row, col}, {m, row, col}};
    }
} // namespace LA

#endif /* Minor_h */

