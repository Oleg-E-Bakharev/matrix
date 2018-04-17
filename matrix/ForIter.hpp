//
//  for_iter.hpp
//  Sorting
//
//  Created by Oleg Bakharev on 08/04/16.
//  Copyright © 2016 Oleg Bakharev. All rights reserved.
//

#ifndef for_iter_h
#define for_iter_h

// Универсальный итератор, который преобразовывает любой random-access-iterable класс в sequence-iterable-class
// Для использования в range-based for
// Для использования, Collection должен поддерживать [size_t] и size()
// А также тип reference как ссылка на хранимый тип.
// Через контекст можно специализировать итератор для специальных целей (напр в матрице смежности графа).
template <typename Collection> class ForIter {
    Collection& _col;
    size_t _pos;
public:
    // const_cast - для возможности работать и с константными и с неконстантными итераторами.
    ForIter(Collection& col) : _col(col), _pos(0) {}
    typename Collection::reference operator*() { return _col[_pos]; }
    bool operator != (const ForIter& f) const { assert(&f._col == &_col); return _pos != _col.size(); }
    void operator++() { ++_pos; }
};

// Функция для инстанциирования for_iter_t чтобы параметр шаблона вывелся компилятором.
template<class Collection> ForIter<Collection> forIter(Collection& col) { return {col}; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// То же но константный.
template <typename Collection> class ConstForIter {
    const Collection& _col;
    size_t _pos;
public:
    // const_cast - для возможности работать и с константными и с неконстантными итераторами.
    ConstForIter(const Collection& col) : _col(const_cast<Collection&>(col)), _pos(0) {}
    typename Collection::const_reference operator*() const { return _col[_pos]; }
    bool operator != (const ConstForIter& f) const { assert(&f._col == &_col); return _pos != _col.size(); }
    void operator++() { ++_pos; }
};

// Функция для инстанциирования for_iter_t чтобы параметр шаблона вывелся компилятором.
template<class Collection> ConstForIter<Collection> constForIter(Collection& col) { return {col}; }

#endif /* for_iter_h */
