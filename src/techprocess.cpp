#include "techprocess.hpp"
#include "techprocess_viewer.hpp"

#include <iostream>

Techprocess::Techprocess (const QString& name): m_name{name}
{}

Techprocess::~Techprocess()
{
    std::vector<Operation*>::iterator i;
    for (i = m_operations.begin(); i != m_operations.end(); ++i)
    {
        delete *i;
    }
}

Techprocess::Techprocess(Techprocess && techprocess)
{
    m_name = std::move(techprocess.m_name);
    m_operations = std::move(techprocess.m_operations);
}


void Techprocess::addOperation(const QString& name)
{
    m_operations.push_back(new Operation(name));
}

void Techprocess::addMaterial(MaterialEntry *material)
{
    if(m_operations.empty())
        return;
    m_operations.back()->addMaterial(material);
}


void Techprocess::addAlternative(MaterialEntry *alternative)
{
    m_operations.back()->addAlternative(alternative);
}

void Techprocess::printToConsole()
{
    std::cout << "Техпроцесс " << m_name.toStdString()<<'\n';
    std::vector<Operation*>::const_iterator i;
    for (i = m_operations.begin(); i != m_operations.end(); ++i)
    {
        (*i)->printToConsole();
    }
    
}

void Techprocess::transferInfo (TechprocessViewer *viewer)
{
    viewer->addNameTech(m_name);
    std::vector<Operation*>::const_iterator i;
    for (i = m_operations.cbegin(); i != m_operations.cend(); ++i)
    {
        (*i)->transferInfo(viewer);
    }
}

QString Techprocess::getName()
{
    return m_name;
}
