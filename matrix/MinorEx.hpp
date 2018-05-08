//
//  MinorEx.h
//  matrix
//
//  Created by Oleg Bakharev on 11/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Минор произвольного порядка. Подходит для перестановки строк/столбцов.

#ifndef MinorEx_h
#define MinorEx_h

#include "ForIterable.hpp"
#include "Ostreamable.hpp"
#include "Equitable.hpp"
#include "Multiplicable.hpp"
#include "MatrixAdapter.hpp"
#include <vector>
#include <assert.h>

namespace LA {
    
    template<typename Vector> class MinorExIter :
    public ForIterable<MinorExIter<Vector>>,
    public VectorEquitable<MinorExIter<Vector>>,
    public VectorOstreamable<MinorExIter<Vector>>,
    public VectorMultiplicable<MinorExIter<Vector>>
    {
        Vector _vector; // SliceIter.
        const std::vector<size_t>& _order; // вектор индексов выборки строк/столбцов исходной матрицы.
        
    public:
        using value_type = typename Vector::value_type;
        using reference = typename Vector::reference;
        using const_reference = typename Vector::const_reference;
        
        MinorExIter(const Vector& v, const std::vector<size_t>& o) : _vector(v), _order(o) {}
        
        size_t size() const { return _order.size(); }
        const_reference operator[](size_t i) const { return _vector[_order[i]]; }
        reference operator[](size_t i) { return _vector[_order[i]]; }
    };
    
    ///////////////////////////////////////////
    // Строковый аксессор минора.
    template <typename Matrix> class MinorExRows {
        using Vector = std::vector<size_t>;
        Vector _rowOrder;
        Vector _colOrder;
        
    public:
        using reference = MinorExIter<typename Matrix::reference>;
        using const_reference = MinorExIter<typename Matrix::const_reference>;
        
        MinorExRows(const Vector& rowOrder, const Vector& colOrder) : _rowOrder(rowOrder), _colOrder(colOrder) {}
        
        size_t size(const Matrix& m) const { return _rowOrder.size(); }
        reference operator()(Matrix& m, size_t i) { return {m.row(_rowOrder[i]), _colOrder}; }
        const_reference operator()(const Matrix& m, size_t i) const { return {m.row(_rowOrder[i]), _colOrder}; }
    };
    
    ///////////////////////////////////////////
    // Столбцовый аксессор минора.
    template <typename Matrix> class MinorExCols {
        using Vector = std::vector<size_t>;
        Vector _rowOrder;
        Vector _colOrder;

    public:
        using reference = MinorExIter<typename Matrix::reference>;
        using const_reference = MinorExIter<typename Matrix::const_reference>;
        
        MinorExCols(const Vector& rowOrder, const Vector& colOrder) : _rowOrder(rowOrder), _colOrder(colOrder) {}
        
        size_t size(const Matrix& m) const { return _colOrder.size(); }
        reference operator()(Matrix& m, size_t i) { return {m.col(_colOrder[i]), _rowOrder}; }
        const_reference operator()(const Matrix& m, size_t i) const { return {m.col(_colOrder[i]), _rowOrder}; }
    };
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Создание минора.
            template <typename Matrix, typename ClearMatrix = typename std::remove_reference<Matrix>::type>
            MatrixAdapter<Matrix&&, MinorExRows<ClearMatrix>, MinorExCols<ClearMatrix>> minorEx(Matrix&& m,
                                                                                                std::vector<size_t> rowOrder,
                                                                                                std::vector<size_t> colOrder)
            {
                assert(m.height() >= rowOrder.size() && m.width() >= colOrder.size());
                return {m, {rowOrder, colOrder}, {rowOrder, colOrder}};
            }

} // namespace LA
#endif /* MinorEx_h */
