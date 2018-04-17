//
//  CopylessHolder.hpp
//  matrix
//
//  Created by Oleg Bakharev on 16/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Универсальный контейнер без копирования. Служит базой для других классов. Если параметризуется
//  l-Value типом контейнера то хранит ссылку на контейнер. Если инициализируется r-Value типом контейнера,
//  То хранит сам контейнер, инициализирующийся move-конструктором.
//  Предполагается приватное наследование от данного класса.

#ifndef CopylessHolder_h
#define CopylessHolder_h

#include "Debug.hpp"

// Если производный класс инициализируется именованным объектом (l-value - долгоживущая ссылка),
// То используется база с сылкой.
template <typename Data> class CopylessHolder {
public: Data& data;
    CopylessHolder(Data& data) : data(data) { debugOut2("CopylessHolder &", 100); }
    CopylessHolder(const CopylessHolder& c) : data(c.data) { debugOut2("CopylessHolder & copy", 100); }
    CopylessHolder(CopylessHolder&& c) : data(c.data) { debugOut2("CopylessHolder & move", 100); }
};

// Eсли производный класс инициализируется временным объектом (r-value - ссылка), то берётся база с экземпляром,
// инициализирующимся move-конструктором.
template <typename Data> class CopylessHolder<Data&&> {
public: Data data;
    CopylessHolder(Data&& data) : data(data) {debugOut2("CopylessHolder &&", 100);}
    CopylessHolder(const CopylessHolder& c) = delete;
    CopylessHolder(CopylessHolder&& c) : data(c.data) { debugOut2("CopylessHolder && move", 100); }
};

#endif /* CopylessHolder_h */
