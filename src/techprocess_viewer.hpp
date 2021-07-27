#pragma once

#include <QtWidgets/QApplication>
#include <QClipboard>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QSet>

#include "inputnumberqvalidator.hpp"
#include "techprocess.hpp"


class TechprocessViewer: public QWidget
{
    Q_OBJECT
private:
    QClipboard *copyBuffer;
    QGridLayout *m_gridBox;
    QVBoxLayout *m_dependanceBox;
    QValidator *inputValidator;
    QMultiMap<QString, std::function<void(double)>> m_changesMap;
    QSet<QString> m_usedDependance;
    std::vector<std::function<void(double, Measurement::Type)>> m_complexDependance;
    int m_currentRow = 0;
    void updateMaterials(double newValue, const QString measureType);
    void writeRow(QLabel *element1, QLabel *element2, QLabel *element3, QWidget *element4);
    void writeRow(QLabel *element);
    QLabel* writeMaterialRow(const QString &name, const Measurement::Measure &measure);
    void addLambda(CalculateElement* element, std::function<void(double)> func);
    
public:
    explicit TechprocessViewer(Techprocess* tech, QWidget *parent = nullptr);
    void generateGui(Techprocess *tech);
    void addNameTech(const QString &name);
    void addOperation(const QString &name);
    void addMaterial(const QString &name, const Measurement::Measure &measure, CalculateElement *element1, CalculateElement *element2);
    void addMaterial(const QString &name, const Measurement::Measure &measure, CalculateElement *element1, CalculateElement *element2, MaterialEntry *alt);
    void addMaterial(const QString &name, const Measurement::Measure &measure, CalculateElement *element, MaterialEntry *alt);
    void addMaterial(const QString &name, const Measurement::Measure &measure, CalculateElement *element);
};
