//
//  IdentityAccessor.h
//  matrix
//
//  Created by Oleg Bakharev on 18/04/2018.
//  Copyright © 2018 Oleg Bakharev. All rights reserved.
//
//  Аксессоры к матричному адаптеру, без изменений.

#ifndef IdentityAccessor_h
#define IdentityAccessor_h

#include "Equitable.hpp"
#include "Ostreamable.hpp"
#include "MatrixAdapter.hpp"
#include "Multiplicable.hpp"

namespace LA {
    template <typename Matrix> class IdentifyRowAccessor :
    public VectorEquitable<IdentifyRowAccessor<Matrix>>,
    public VectorOstreamable<IdentifyRowAccessor<Matrix>>,
    public VectorMultiplicable<IdentifyRowAccessor<Matrix>>
    {
    public:
        using reference = typename Matrix::reference;
        using const_reference = typename Matrix::const_reference;
        
        size_t size(const Matrix& m) const { return m.height(); }
        reference operator()(Matrix& m, size_t i) { return m.row(i); }
        const_reference operator()(const Matrix& m, size_t i) const { return m.row(i); }
    };
    
    template <typename Matrix> class IdentifyColAccessor :
    public VectorEquitable<IdentifyColAccessor<Matrix>>,
    public VectorOstreamable<IdentifyColAccessor<Matrix>>,
    public VectorMultiplicable<IdentifyColAccessor<Matrix>>
    {
    public:
        using reference = typename Matrix::reference;
        using const_reference = typename Matrix::const_reference;
        
        size_t size(const Matrix& m) const { return m.width(); }
        reference operator()(Matrix& m, size_t i) { return m.col(i); }
        const_reference operator()(const Matrix& m, size_t i) const { return m.col(i); }
    };

} // namespace LA

#endif /* IdentityAccessor_h */
