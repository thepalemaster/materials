#include "techprocess_viewer.hpp"
#include "complex_dependance.hpp"
#include "inputnumberqvalidator.hpp"


TechprocessViewer::TechprocessViewer(Techprocess* tech, QWidget *parent)
    :QWidget(parent)
{
    copyBuffer = QApplication::clipboard();
    inputValidator = new InputNumberQValidator(this);
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
        lineEdit->setValidator(inputValidator);
        measure = new QLabel(*it);
        connect(lineEdit, &QLineEdit::editingFinished, this, [=](){
            QString inputText = lineEdit->text();
            int pos = inputText.indexOf(',');
            if(pos != -1)//вероятно стоит использовать QLocale
            {
                inputText[pos] = '.';
            }
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

 void TechprocessViewer::addNameTech(const QString &name)
{
    //++m_currentRow;
    QLabel *techname = new QLabel("<strong>" + name + "</strong>");
    m_dependanceBox->addWidget(techname);
}

 void TechprocessViewer::addOperation(const QString &name)
{
    ++m_currentRow;
    QLabel *opername = new QLabel("<strong>" + name + "</strong>");
    m_gridBox->addWidget(opername, m_currentRow, 0, 1, 2);
}

void TechprocessViewer::addMaterial(const QString &name, const Measurement::Measure& measure, CalculateElement* element)
{
    QLabel *factorLabel = writeMaterialRow(name, measure);
    if (element->m_measure.m_type == Measurement::UNITS)
    {
        factorLabel->setText(QString::number(element->expense));
        return;
    }
    double coefficient = element->expense / element->m_measure.m_coefficient;
    std::function <void(double)> func1= [coefficient, factorLabel](double newValue)
    { 
        factorLabel->setText(QString::number(coefficient * newValue));
    };
    addLambda(element,
              [coefficient, factorLabel](double newValue)
              {
                  factorLabel->setText(QString::number(coefficient * newValue));
              });    
}

void TechprocessViewer::addMaterial(const QString &name, const Measurement::Measure& measure, CalculateElement* element, MaterialEntry* alt)
{
    addMaterial(name, measure, element);
    writeRow(new QLabel("или"));
    alt->transferInfo(this);
}

void TechprocessViewer::addMaterial(const QString &name, const Measurement::Measure& measure, CalculateElement* element1, CalculateElement* element2)
{
    if (element2->m_measure.m_type == Measurement::UNITS)
    {
        CalculateElement tempElement{element1->expense/element2->expense, element1->name, element1->m_measure};
        addMaterial(name, measure, &tempElement);
        return;
    }
    QLabel *factorLabel = writeMaterialRow(name, measure);
    auto index = m_complexDependance.size();
    m_complexDependance.emplace_back(
        ComplexDependance(factorLabel, measure, element1, element2)
    );
    addLambda(element1,
              [this, index, type1{element1->m_measure.m_type}] (double input)
              {
                  m_complexDependance[index](input, type1);
              });
    addLambda(element2,
              [this, index, type2{element2->m_measure.m_type}] (double input)
              {
                  m_complexDependance[index](input, type2);
              });
};

void TechprocessViewer::addMaterial(const QString& name, const Measurement::Measure& measure, CalculateElement* element1, CalculateElement* element2, MaterialEntry* alt)
{
    addMaterial(name, measure, element1, element2);
    writeRow(new QLabel("или"));
    alt->transferInfo(this);
}


QLabel* TechprocessViewer::writeMaterialRow(const QString &name, const Measurement::Measure& measure)
{
    QLabel *matName = new QLabel(name);
    QLabel *measureName = new QLabel(measure.m_shortName);
    QLabel *factorLabel  = new QLabel("0");
    QPushButton *copyButton = new QPushButton("Скопировать");
    writeRow(matName, factorLabel, measureName, copyButton);
    connect(copyButton, &QPushButton::clicked, this, [this, factorLabel] (){
        copyBuffer->setText(factorLabel->text());
    });
    return factorLabel;
}

void TechprocessViewer::addLambda(CalculateElement* element, std::function<void (double)> func)
{
    QString key = QString("%1 %2:").arg(Measurement::inputLabel.at(element->m_measure.m_type), element->name);
    m_changesMap.insert(key, std::move(func));
    m_usedDependance.insert(key);    
}

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
