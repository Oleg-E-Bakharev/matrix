//
//  ColIter.hpp
//  matrix
//
//  Created by Oleg Bakharev on 18/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Итератор по столбцам матрицы вместо строк.

#ifndef ColIter_h
#define ColIter_h

template <typename Matrix> class ColIterator {
    Matrix& _mat;
public:
    using reference = typename Matrix::reference;
    using const_reference  = typename Matrix::const_reference;
    
    ColIterator(Matrix& m) : _mat(m) {}
    
    size_t size() const { return _mat.width(); }
    reference operator[](size_t i) { return _mat.col(i); }
    const_reference operator[](size_t i) const { return _mat.col(i); }
};

//////////////////////////////////////////////////////////////////////
// То же но константный.
template <typename Matrix> class ConstColIterator {
    const Matrix& _mat;
public:
    using reference = typename Matrix::const_reference;
    using const_reference  = typename Matrix::const_reference;
    
    ConstColIterator(const Matrix& m) : _mat(m) {}
    
    size_t size() const { return _mat.width(); }
    const_reference operator[](size_t i) const { return _mat.col(i); }
};


#endif /* ColIter_h */
