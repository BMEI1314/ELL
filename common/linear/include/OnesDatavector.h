// OnesDatavector.h

#pragma once

#include "IDataVector.h"

namespace linear
{
    /// OnesDatavector Base class
    ///
    class OnesDatavector : public IDataVector
    {
    public:

        /// Constructor
        ///
        OnesDatavector(uint dim = 0);

        /// Converting constructor
        ///
        explicit OnesDatavector(const IDataVector& other);

        /// Move constructor
        ///
        OnesDatavector(OnesDatavector&& other) = default;

        /// Deleted copy constructor
        ///
        OnesDatavector(const OnesDatavector&) = delete;

        /// \returns The type of the vector
        ///
        virtual type GetType() const override;

        /// Sets an entry in the vector
        ///
        virtual void PushBack(uint index, double value = 1.0) override;

        /// Deletes all of the vector content and sets its Size to zero, but does not deallocate its memory
        ///
        virtual void Reset() override;

        /// Calls a callback function for each non-zero entry in the vector, in order of increasing index
        ///
        //virtual    void foreach_nonzero(function<void(uint, double)> func, uint index_offset = 0) const override;

        /// \returns The largest index of a non-zero entry plus one
        ///
        virtual uint Size() const override;

        /// \returns The number of non-zeros
        ///
        virtual uint NumNonzeros() const override;

        /// Computes the vector squared 2-norm
        ///
        virtual double Norm2() const override;

        /// Performs (*p_other) += scalar * (*this), where other is a dense vector
        ///
        virtual void AddTo(double* p_other, double scalar = 1.0) const override;
        
        /// Computes the Dot product
        ///
        virtual double Dot(const double* p_other) const override;

    private:
        uint _dim = 0;

    };
}