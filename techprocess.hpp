#pragma once

#include <vector>


#include <QRegExp>

#include "measurement.hpp"




class MaterialEntry
{
private:
    QString m_name;
    //сделать указателями
    const Measurement::Measure &m_measure1;
    const Measurement::Measure &m_measure2;
    double m_expense;
    MaterialEntry* m_alt = nullptr;
public:
    MaterialEntry(const QString name, double expense, const QString &measure);
    MaterialEntry(const QString name, double expense, const Measurement::Measure &measure1, const Measurement::Measure &measure2);
    void addAlternative(MaterialEntry *alt);
    void calculate (double input, Measurement::Measure inputMeasure);
    QString* getLabels();
    void printToConsole();
};

class Operation
{
private:
    QString m_name;
    std::vector<MaterialEntry*> materials;
public:
    Operation(const QString &name);
    ~Operation();
    void addAlternative(MaterialEntry *alt);
    void addMaterial(MaterialEntry *material);
    void printToConsole();
};


class Techprocess 
{
private:
    QString m_name;
    QList<Operation*> m_operations;
    
public:
    Techprocess (QString name);
    ~Techprocess();
    void addOperation(const QString &name);
    void addMaterial(MaterialEntry *material);
    void addAlternative(MaterialEntry *alt);
    void printToConsole();
};
