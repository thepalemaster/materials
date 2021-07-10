#pragma once

#include <QtWidgets/QLabel>
#include "material_entry.hpp"

struct ComplexDependance
{
    double input1 = 0;
    double input2 = 0;
    Measurement::Type type1;
    Measurement::Type type2;
    QLabel *labelptr;
    double coefficient1;
    double coefficient2;
    ComplexDependance (QLabel *ptr, const Measurement::Measure& measure, CalculateElement* element1, CalculateElement* element2);
    void operator() (double number, Measurement::Type type);
};
