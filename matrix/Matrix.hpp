//
//  matrix.hpp
//  Sorting
//
//  Created by Oleg Bakharev on 30/03/16.
//  Copyright © 2016 Oleg Bakharev. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include "Debug.hpp"
#include <vector>
#include <valarray>
#include <initializer_list>
#include "ForIterable.hpp"
#include "Ostreamable.hpp"
#include "Equitable.hpp"
#include "Multiplicable.hpp"
#include "SliceIter.hpp"

namespace LA {
    
    // Матрица
    template <typename Container> class Matrix_T :
    public ForIterable<Matrix_T<Container>>,
    public MatrixOstreamable<Matrix_T<Container>>,
    public MatrixEquitable<Matrix_T<Container>>,
    public MatrixMultiplicable<Matrix_T<Container>>
    {
        size_t _h;
        size_t _w;
        Container _m;
        
    public:
        using T = typename Container::value_type;
        using vector = SliceIter<Container>;
        using instance_type = Matrix_T;
        using value_type = vector;
        using reference = vector; // vec это и value_type и reference.
        using const_reference = ConstSliceIter<Container>;
        
        Matrix_T(size_t h, size_t w) : _h(h), _w(w), _m(w * h) {}
        Matrix_T(size_t h, size_t w, T def) : _h(h), _w(w), _m(w * h, def) {}
        ~Matrix_T() { debugOut2("~Matrix_T", 99); }
        
        explicit Matrix_T(const Matrix_T&) = default;
        Matrix_T(Matrix_T&&) = default;
        
        Matrix_T(std::initializer_list<std::initializer_list<T>> l) : _h(l.size()),
        _w(_h > 0 ? l.begin()->size() : 0),
        _m(_h * _w)
        {
            size_t pos = 0;
            for( std::initializer_list<T> const& rowList : l ) {
                assert(rowList.size() == _w);
                for( const T& value : rowList) {
                    _m[pos] = value;
                    pos++;
                }
            }
        }
        
        size_t width() const { return _w; }
        size_t height() const { return _h; }
        
        reference col(size_t x) { return { _m, std::slice(x, _h, _w) }; }
        const_reference col(size_t x) const { return { _m, std::slice(x, _h, _w) }; }
        
        reference row(size_t y) { return { _m, std::slice( y * _w, _w, 1) }; }
        const_reference row(size_t y) const { return { _m, std::slice(y * _w, _w, 1) }; }
        
        reference operator[] (size_t y) { return row(y); }
        const_reference operator[] (size_t y) const { return row(y); }
        
        size_t size() const { return _h; }        
    };
    
    template <typename T>
    using Matrix = Matrix_T<std::vector<T>>;
    
} // namespace LA

#endif /* matrix_h */

