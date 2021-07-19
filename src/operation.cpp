#include "techprocess.hpp"
#include "techprocess_viewer.hpp"

#include <iostream>



Operation::Operation(const QString& name):m_name(name) {}

Operation::~Operation()
{
    std::vector<MaterialEntry*>::iterator i;
    for (i = materials.begin(); i != materials.end(); ++i)
    {
        delete *i;
    }
}

void Operation::printToConsole()
{
    std::cout<< m_name.toStdString() << '\n';
    std::vector<MaterialEntry*>::const_iterator i;
    for (i = materials.begin(); i != materials.end(); ++i)
    {
        (*i)->printToConsole();
    }
}

void Operation::transferInfo(TechprocessViewer *viewer) const
{
    viewer->addOperation(m_name);
    std::vector<MaterialEntry*>::const_iterator i;
    for (i = materials.begin(); i != materials.end(); ++i)
    {
        (*i)->transferInfo(viewer);
    } 
}
    
void Operation::addMaterial(MaterialEntry *material)
{
    materials.push_back(material);
}

void Operation::addAlternative(MaterialEntry *alternative)
{
    materials.back()->addAlternative(alternative);
}

QString Operation::getName()
{
    return m_name;
}

std::vector<QString> Operation::getMaterial(int index)
{
    if (index>= materials.size() || index < 0)
    {
        return {};
    }
    return materials[index]->getLabels();
}
 
