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

namespace LA {
    template <typename Matrix> class IdentifyRowAccessor
    {
    public:
        using reference = typename Matrix::reference;
        using const_reference = typename Matrix::const_reference;
        
        size_t size(const Matrix& m) const { return m.height(); }
        reference operator()(Matrix& m, size_t i) { return m.row(i); }
        const_reference operator()(const Matrix& m, size_t i) const { return m.row(i); }
    };
    
    template <typename Matrix> class IdentifyColAccessor
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
