// PrintableShift.h

#pragma once

#include "IPrintableLayer.h"
#include "LayerLayout.h"

#include "Shift.h"
using layers::Shift;

/// A struct that adds printing capabilities to a layer
///
struct PrintableShift : public Shift, public IPrintableLayer
{
public:
    /// Prints a human-firiendly description of the underlying class to an output stream
    ///
    virtual LayerLayout Print(ostream& os, double left, double top, const CommandLineArguments& args) const override;
};