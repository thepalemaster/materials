#include "techprocess.hpp"


#include <iostream>

//материал
MaterialEntry::MaterialEntry(const QString name, double expense, const QString& measure)
:m_name(name), m_measure1{Measurement::measureMap.at(measure)},m_measure2{Measurement::measureMap.at("шт")}, m_expense(expense)
{}

MaterialEntry::MaterialEntry (const QString name, double expense, const Measurement::Measure &measure1, const Measurement::Measure &measure2)
:m_name(name),m_measure1(measure1), m_measure2(measure2), m_expense(expense)
{}

void MaterialEntry::addAlternative(MaterialEntry *alternative)
{
    if (m_alt)
    {
        m_alt->addAlternative(alternative);
    }
    else
    {
       m_alt = alternative;
    }
}

void MaterialEntry::printToConsole()
{
    std::cout << m_name.toStdString() << '\t'<< '\t'<< m_expense << '\t' <<m_measure1.m_shortName << '/' << m_measure2.m_shortName<< '\n';
    if (m_alt)
    {
        std::cout << "или" << '\n';
        m_alt->printToConsole();
    }
}


//операция
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

    
void Operation::addMaterial(MaterialEntry *material)
{
    materials.push_back(material);
}

void Operation::addAlternative(MaterialEntry *alternative)
{
    materials.back()->addAlternative(alternative);
}
 
 
 
//техпроцесс
Techprocess::Techprocess (QString name)
    {
        m_name = name;
    }

void Techprocess::addOperation(const QString& name)
{
    Operation *oper = new Operation(name);   
    m_operations.push_back(oper);
}

        
void Techprocess::addMaterial(MaterialEntry *material)
{
    if(m_operations.empty())
        return;
    m_operations.back()->addMaterial(material);
}


void Techprocess::addAlternative(MaterialEntry *alternative)
{
    m_operations.back()->addAlternative(alternative); //сделать чтобы напрямую
}

void Techprocess::printToConsole()
{
    std::cout << "Техпроцесс " << m_name.toStdString()<<'\n';
    QList<Operation*>::const_iterator i;
    for (i = m_operations.constBegin(); i != m_operations.constEnd(); ++i)
    {
        (*i)->printToConsole();
    }
    
}

Techprocess::~Techprocess()
{
    QList<Operation*>::const_iterator i;
    for (i = m_operations.constBegin(); i != m_operations.constEnd(); ++i)
    {
        delete *i;
    }
}
