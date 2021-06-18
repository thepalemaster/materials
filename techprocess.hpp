#pragma once

#include <vector>
#include <QRegExp>

#include "operation.hpp"

class Techprocess 
{
private:
    QString m_name;
    std::vector<Operation*> m_operations;
    
public:
    Techprocess (QString name);
    ~Techprocess();
    void addOperation(const QString &name);
    void addMaterial(MaterialEntry *material);
    void addAlternative(MaterialEntry *alt);
    void printToConsole();
    void transferInfo (TechprocessViewer *viewer);
    QString getName();
};
