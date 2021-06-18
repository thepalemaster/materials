#include "techprocess.hpp"
#include "techprocess_viewer.hpp"

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


Techprocess::~Techprocess()
{
    std::vector<Operation*>::const_iterator i;
    for (i = m_operations.cbegin(); i != m_operations.cend(); ++i)
    {
        delete *i;
    }
}
