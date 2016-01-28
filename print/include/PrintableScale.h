// PrintableScale.h

#pragma once

#include "IPrintableLayer.h"
#include "LayerLayout.h"

#include "Scale.h"
using layers::Scale;

/// A struct that adds printing capabilities to a layer
///
struct PrintableScale : public Scale, public IPrintableLayer
{
public:
    /// Prints a human-firiendly description of the underlying class to an output stream
    ///
    virtual LayerLayout Print(ostream& os, double left, double top, const CommandLineArguments& args) const override;
};