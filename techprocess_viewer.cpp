#include "techprocess_viewer.hpp"

#include <iostream>

TechprocessViewer::TechprocessViewer(Techprocess* tech, QWidget *parent)
    :QWidget(parent)
{
    copyBuffer = QApplication::clipboard();
    generateGui(tech);  
}

void TechprocessViewer::updateMaterials(double newValue, const QString measureType)
{
    QMultiMap<QString, std::function<void(double)>>::iterator it = m_changesMap.find(measureType);
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
    ++m_currentRow;
    m_gridBox->setRowStretch(m_currentRow, 1);
    for (auto it = m_usedDependance.begin(); it != m_usedDependance.end(); ++it)
    {
        lineEdit = new QLineEdit();
        measure = new QLabel(*it);
        connect(lineEdit, &QLineEdit::editingFinished, this, [=](){
            QString inputText = lineEdit->text();
            bool condition;
            double number = inputText.toDouble(&condition);
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
    //++m_currentRow;
    QLabel *techname = new QLabel("<strong>" + name + "</strong>");
    //std::cout<<"Гуй5"<<"\n";  
    m_dependanceBox->addWidget(techname);
}

 void TechprocessViewer::addOperation(QString name)
{
    ++m_currentRow;
    QLabel *opername = new QLabel("<strong>" + name + "</strong>");
    m_gridBox->addWidget(opername, m_currentRow, 0, 1, 2);
}

void TechprocessViewer::addMaterial(QString name, const Measurement::Measure& measure, CalculateElement* element)
{
    QLabel *matName = new QLabel(name);
    QLabel *measureName = new QLabel(measure.m_shortName);
    QLabel *factorLabel= new QLabel("0");;
    QPushButton *copyButton = new QPushButton("Скопировать");
    writeRow(matName, factorLabel, measureName, copyButton);
    connect(copyButton, &QPushButton::clicked, this, [this, factorLabel] (){
        copyBuffer->setText(factorLabel->text());
    });
    if(element->m_measure.m_type == Measurement::UNITS)
    {
        factorLabel->setText(QString::number(element->expense));
        return;
    }
    double coefficient = element->expense * (measure.m_coefficient / element->m_measure.m_coefficient);
    std::function <void(double)> func1= [coefficient, factorLabel](double newValue)
    { 
        factorLabel->setText(QString::number(coefficient * newValue));
    };
    QString dependanceKey = QString("%1 %2:").arg(Measurement::inputLabel.at(element->m_measure.m_type)).arg(element->name);
    m_changesMap.insert(dependanceKey, std::move(func1));
    m_usedDependance.insert(dependanceKey);    
}


void TechprocessViewer::addMaterial(QString name, const Measurement::Measure& measure, CalculateElement* element, MaterialEntry* alt)
{
    addMaterial(name, measure, element);
    writeRow(new QLabel("или"));
    alt->transferInfo(this);
}



void TechprocessViewer::addMaterial(QString name, const Measurement::Measure& measure, CalculateElement* element1, CalculateElement* element2)
{
    QLabel *matName = new QLabel(name);
    QLabel *measureName = new QLabel(measure.m_shortName);
    QLabel *factorLabel  = new QLabel("0");
    QPushButton *copyButton = new QPushButton("Скопировать");
    double coefficient1 = element1->expense * (measure.m_coefficient / element1->m_measure.m_coefficient);
    double coefficient2 = element2->expense * element2->m_measure.m_coefficient;
    auto mainFunc = 
        [factorLabel, input1{0.}, input2{0.}, coefficient1, coefficient2,
        type1{element1->m_measure.m_type}, type2{element1->m_measure.m_type}]
        (double number, Measurement::Type type) mutable
        {
            if(type == type1)
            {
                input1 = number;
            }
            else if(type == type2)
            {
                input2 = number;
            }
            double result = (coefficient1 * input1) * (coefficient2 / input2);
            factorLabel->setText(QString::number(result));
        };
    writeRow(matName, factorLabel, measureName, copyButton);
};



void TechprocessViewer::writeRow(QLabel* element1, QLabel* element2, QLabel* element3, QWidget* element4)
{
    ++m_currentRow;
    m_gridBox->addWidget(element1, m_currentRow, 0);
    m_gridBox->addWidget(element2, m_currentRow, 1);
    m_gridBox->addWidget(element3, m_currentRow, 2);
    m_gridBox->addWidget(element4, m_currentRow, 3);
}

void TechprocessViewer::writeRow(QLabel* element)
{
    ++m_currentRow;
    m_gridBox->addWidget(element, m_currentRow, 0);
}
