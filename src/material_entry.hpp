#pragma once
#include <QString>
#include "measurement.hpp"

class TechprocessViewer;

struct CalculateElement
{
    double expense;
    QString name;
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
    MaterialEntry(const QString name, double expense, const Measurement::Measure &measure1, QString measureName, const Measurement::Measure &measure2);
    MaterialEntry(const QString name, double expense, const Measurement::Measure &measure1, 
                  QString measureName1, const Measurement::Measure &measure2, QString measureName2, double additional_expense, 
                  const Measurement::Measure &measure3);
    MaterialEntry(const MaterialEntry& material) = delete;
    ~MaterialEntry();
    void addAlternative(MaterialEntry *alt);
    void calculate (double input, Measurement::Measure inputMeasure);
    std::vector<QString> getLabels();
    void transferInfo (TechprocessViewer *viewer) const;
};
