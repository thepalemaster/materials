#pragma once
//#include "techprocess_viewer.hpp"
#include <QString>
#include "measurement.hpp"
#include <iostream>

class TechprocessViewer;

struct CalculateElement
{
    double expense;
    QChar sigh;
    const Measurement::Measure &m_measure;
};

class MaterialEntry
{
private:
    QString m_name;
    const Measurement::Measure &m_measure1;
    CalculateElement *m_element1;
    CalculateElement *m_element2 = nullptr;
    MaterialEntry* m_alt = nullptr;
public:
    MaterialEntry(const QString name, double expense, const Measurement::Measure &measure1, QChar sigh1, const Measurement::Measure &measure2);
    MaterialEntry(const QString name, double expense, const Measurement::Measure &measure1, 
                  QChar sigh1, const Measurement::Measure &measure2, QChar sigh2, double additional_expense, 
                  const Measurement::Measure &measure3);
    ~MaterialEntry();
    void addAlternative(MaterialEntry *alt);
    void calculate (double input, Measurement::Measure inputMeasure);
    QString* getLabels();
    void printToConsole();
    void transferInfo (TechprocessViewer *viewer);
};
