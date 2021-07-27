#pragma once
#include "material_entry.hpp"

class Operation
{
private:
    QString m_name;
    std::vector<MaterialEntry*> materials;
public:
    Operation(const QString &name);
    Operation(const Operation& operation) = delete;
    ~Operation();
    void addAlternative(MaterialEntry *alt);
    void addMaterial(MaterialEntry *material);
    void transferInfo (TechprocessViewer *viewer) const;
    QString getName();
    std::vector<QString> getMaterial(int index);
};
