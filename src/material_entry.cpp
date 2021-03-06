#include "material_entry.hpp"
#include "techprocess_viewer.hpp"

#include <iostream>


MaterialEntry::MaterialEntry(const QString name, double expense, const Measurement::Measure& measure1, QString measureName, const Measurement::Measure& measure2)
:m_name{name}, m_measure1{measure1}
{
    m_element1 = new CalculateElement{expense, measureName, measure2};
}

MaterialEntry::MaterialEntry(const QString name, double expense, const Measurement::Measure& measure1, 
                             QString measureName1, const Measurement::Measure& measure2, QString measureName2, 
                             double additional_expense, const Measurement::Measure& measure3):
                             MaterialEntry{name, expense, measure1, measureName1, measure2}
{
    m_element2 = new CalculateElement{additional_expense, measureName2, measure3};
}


MaterialEntry::~MaterialEntry()
{
    if(m_alt)
    {
         delete m_alt;
    }
    delete m_element1;
    if (m_element2)
    {
        delete m_element2;
    }
}

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

void MaterialEntry::transferInfo(TechprocessViewer* viewer) const
{
    if (m_alt)
    {
        if (m_element2) 
            viewer->addMaterial(m_name, m_measure1, m_element1, m_element2, m_alt);
        else
            viewer->addMaterial(m_name, m_measure1, m_element1, m_alt);
    }
    else
    {
        if (m_element2) 
            viewer->addMaterial(m_name, m_measure1, m_element1, m_element2);
        else
            viewer->addMaterial(m_name, m_measure1, m_element1);
    }
}

std::vector<QString> MaterialEntry::getLabels()
{
    std::vector<QString> listOfElements{m_name, m_measure1.m_name, m_element1->m_measure.m_name, QString::number(m_element1->expense)};
    if (!m_element1->name.isEmpty())
    {
        listOfElements.push_back(m_element1->name);
    }

    if(m_element2)
    {
        listOfElements.push_back(m_element2->m_measure.m_name);
        listOfElements.push_back(QString::number(m_element2->expense));
        if (!m_element2->name.isEmpty())
        {
            listOfElements.push_back(m_element2->name);
        }
    }
    if(m_alt)
    {
        std::vector<QString> altList = m_alt->getLabels();
        listOfElements.insert(listOfElements.end(), altList.begin(), altList.end());
    }
    return listOfElements;
}
