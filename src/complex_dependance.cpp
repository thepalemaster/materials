#include "complex_dependance.hpp"

ComplexDependance::ComplexDependance (QLabel *ptr, const Measurement::Measure& measure, CalculateElement* element1, CalculateElement* element2):
type1{element1->m_measure.m_type}, type2{element2->m_measure.m_type}, labelptr{ptr}
{
    coefficient1 = element1->expense / element1->m_measure.m_coefficient;
    coefficient2 = element2->expense / element2->m_measure.m_coefficient;
}

void ComplexDependance::operator() (double number, Measurement::Type type)
{
    if(type == type1)
    {
        input1 = number;
    }
    else if(type == type2)
    {
        input2 = number;
    }
    double result = (coefficient1 * input1) * (input2 / coefficient2);
    // k * in * mkm / exp
    labelptr->setText(QString::number(result));
}
