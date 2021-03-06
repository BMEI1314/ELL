////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     ProtoNNPredictor.cpp (predictors)
//  Authors:  Suresh Iyengar
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ProtoNNPredictor.h"

// math
#include "MatrixOperations.h"

// stl
#include <memory>

namespace ell
{
namespace predictors
{
    ProtoNNPredictor::ProtoNNPredictor()
        : _dimension(0), _W(0, 0), _B(0, 0), _Z(0, 0), _gamma(0)
    {
    }

    ProtoNNPredictor::ProtoNNPredictor(size_t dimension, size_t projectedDimension, size_t numPrototypes, size_t numLabels, double gamma)
        : _dimension(dimension), _W(projectedDimension, dimension), _B(projectedDimension, numPrototypes), _Z(numLabels, numPrototypes), _gamma(gamma)
    {
    }

    void ProtoNNPredictor::Reset()
    {
        _dimension = 0;
        _W.Reset();
        _B.Reset();
        _Z.Reset();
        _gamma = 0.0;
    }

    math::ColumnVector<double> ProtoNNPredictor::GetLabelScores(const DataVectorType& inputVector) const
    {
        // Projection
        math::ColumnVector<double> data(inputVector.ToArray());
        math::ColumnVector<double> projectedInput(GetProjectedDimension());
        math::Multiply(1.0, _W, data, 0.0, projectedInput);

        // Similarity to each prototype
        auto numPrototypes = GetNumPrototypes();
        math::ColumnVector<double> similarityToPrototypes(numPrototypes);
        auto prototypes = GetPrototypes();
        auto gammaVal = GetGamma();

        for (size_t i = 0; i < numPrototypes; i++)
        {
            math::ColumnVector<double> prototype(prototypes.GetColumn(i).ToArray());
            prototype -= projectedInput;
            auto prototypeDistance = prototype.Norm2();
            auto similarity = std::exp(-1 * gammaVal * gammaVal * prototypeDistance * prototypeDistance);
            similarityToPrototypes[i] = similarity;
        }

        // Get the prediction label
        math::ColumnVector<double> labels(GetNumLabels());
        math::Multiply(1.0, GetLabelEmbeddings(), similarityToPrototypes, 0.0, labels);

        return labels;
    }

    ProtoNNPrediction ProtoNNPredictor::Predict(const DataVectorType& inputVector) const
    {
        auto labels = GetLabelScores(inputVector);
        auto maxElement = std::max_element(labels.GetDataPointer(), labels.GetDataPointer() + labels.Size());
        auto maxLabelIndex = maxElement - labels.GetDataPointer();

        ProtoNNPrediction prediction{ *maxElement, (size_t)maxLabelIndex };

        return prediction;
    }

    void ProtoNNPredictor::WriteToArchive(utilities::Archiver& archiver) const
    {
        archiver["dim"] << _dimension;
        archiver["gamma"] << _gamma;
        math::MatrixArchiver::Write(_W, "w", archiver);
        math::MatrixArchiver::Write(_B, "b", archiver);
        math::MatrixArchiver::Write(_Z, "z", archiver);
    }

    void ProtoNNPredictor::ReadFromArchive(utilities::Unarchiver& archiver)
    {
        archiver["dim"] >> _dimension;
        archiver["gamma"] >> _gamma;
        math::MatrixArchiver::Read(_W, "w", archiver);
        math::MatrixArchiver::Read(_B, "b", archiver);
        math::MatrixArchiver::Read(_Z, "z", archiver);
    }
}
}
