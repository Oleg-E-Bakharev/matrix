//
//  matrix.hpp
//  Sorting
//
//  Created by Oleg Bakharev on 30/03/16.
//  Copyright © 2016 Oleg Bakharev. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include <vector>
#include <initializer_list>
#include "ForIterable.hpp"
#include "Ostreamable.hpp"
#include "SliceIter.hpp"

namespace LA {
    
    // Матрица
    template <typename Container> class Matrix_T :
    public ForIterable<Matrix_T<Container>>,
    public MatrixOstreamable<Matrix_T<Container>>
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
        
        Matrix_T(size_t w, size_t h) : _h(h), _w(w), _m(w * h) {}
        Matrix_T(size_t w, size_t h, T def) : _h(h), _w(w), _m(w * h, def) {}
        
        explicit Matrix_T(const Matrix_T&) = default;
        
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
        
        // Оператор сравнения с любой другой матрицей, в т.ч. реализованной другим классом.
        template <class Other> bool operator==(const Other& m) const {
            if (width() != m.width()) return false;
            if (height() != m.height()) return false;
            for ( size_t i = 0; i < height(); i++ ) {
                for ( size_t j = 0; j < width(); j++ ) {
                    if ((*this)[i][j] != m[i][j]) return false;
                }
            }
            return true;
        }
    };
    
    template <typename T>
    using Matrix = Matrix_T<std::vector<T>>;
    
} // namespace LA

#endif /* matrix_h */

