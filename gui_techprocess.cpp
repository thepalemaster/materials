#include "gui_techprocess.hpp"

#include <iostream>


TechprocessViewer::TechprocessViewer(QWidget *parent)
    :QWidget(parent)
{
    std::cout<<"Гуй9\n";    
}

TechprocessViewer::TechprocessViewer(Techprocess* tech, QWidget *parent)
    :QWidget(parent)
{
    generateGui(tech);  
}

void TechprocessViewer::updateMaterials(double newValue, Measurement::Type measureType)
{
    QMultiMap<Measurement::Type, std::function<void(double)>>::iterator it = m_changesMap.find(measureType);
    for (; it != m_changesMap.end() && it.key() == measureType; ++it)
    {
         (*it)(newValue);
     }
}


void TechprocessViewer::generateGui(Techprocess* tech)
{
    m_gridBox = new QGridLayout(this);
    m_dependanceBox = new QVBoxLayout();
    m_gridBox->addLayout(m_dependanceBox, 0, 0, 1, -1);
    tech->transferInfo(this);
    QLabel *measure;
    QLineEdit *lineEdit;
    for (auto it = m_usedDependance.begin(); it != m_usedDependance.end(); ++it)
    {
        lineEdit = new QLineEdit();
        measure = new QLabel(Measurement::inputLabel.at(*it));
        connect(lineEdit, &QLineEdit::editingFinished, this, [=](){
            QString inputText = lineEdit->text();
            bool condition;
            double number = inputText.toDouble(&condition);
            std::cout << inputText.toStdString()<<'\n';
            if (condition)
            {
                updateMaterials(number, *it);
            }
        });
        m_dependanceBox->addWidget(measure);
        m_dependanceBox->addWidget(lineEdit);
    }
    
}

 void TechprocessViewer::addNameTech(QString name)
{
    ++m_currentRow;
    QLabel *techname = new QLabel(name);
    std::cout<<"Гуй5"<<"\n";  
    m_gridBox->addWidget(techname, m_currentRow, 0);
}

 void TechprocessViewer::addOperation(QString name)
{

    ++m_currentRow;
    QLabel *opername = new QLabel(name);
    m_gridBox->addWidget(opername, m_currentRow, 0, 1, 2);
}

void TechprocessViewer::addMaterial(QString name, double factor, const Measurement::Measure& measure1, const Measurement::Measure& measure2)
{
    ++m_currentRow;
    QLabel *matName = new QLabel(name);
    QLabel *measureName1 = new QLabel(measure1.m_shortName);
    QLabel *factorLabel = new QLabel("0");
    m_gridBox->addWidget(matName, m_currentRow, 0);
    m_gridBox->addWidget(factorLabel, m_currentRow, 1);
    m_gridBox->addWidget(measureName1, m_currentRow, 2);
    if (measure2.m_type == Measurement::UNITS)
    {
        factorLabel->setText(QString::number(factor));
        return;
    }
    double coefficient = factor * measure1.m_coefficient / measure2.m_coefficient; 
    std::function <void(double)> func1= [coefficient, factorLabel](double newValue)
    { 
        double x = coefficient * newValue;
        std::cout << "+";
        factorLabel->setText(QString::number(x));
        std::cout<<factorLabel->text().toStdString();
    };
    m_changesMap.insert(measure2.m_type, func1);
    m_usedDependance.insert(measure2.m_type);
    
}

void TechprocessViewer::addMaterial(QString name, double factor, const Measurement::Measure& measure1, const Measurement::Measure& measure2, MaterialEntry* alt)
{

    addMaterial(name, factor, measure1, measure2);
    QLabel *orLabel = new QLabel(QString("или"));
    ++m_currentRow;
    m_gridBox->addWidget(orLabel, m_currentRow, 0);
    alt->transferInfo(this);
}
