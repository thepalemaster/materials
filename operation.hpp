#pragma once
#include "material_entry.hpp"

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
    void transferInfo (TechprocessViewer *viewer);
};