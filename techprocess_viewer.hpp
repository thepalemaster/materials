#pragma once

#include <QtWidgets/QApplication>
#include <QClipboard>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QSet>

#include "techprocess.hpp"


class TechprocessViewer: public QWidget
{
    Q_OBJECT
private:
    QClipboard *copyBuffer;
    QGridLayout *m_gridBox;
    QVBoxLayout *m_dependanceBox;
    QMultiMap<QString, std::function<void(double)>> m_changesMap;
    QSet<QString> m_usedDependance;
    std::vector<std::function<void(double, Measurement::Type)>> m_complexDependance;
    int m_currentRow = 0;
    void updateMaterials(double newValue, const QString measureType);
    void writeRow(QLabel *element1, QLabel *element2, QLabel *element3, QWidget *element4);
    void writeRow(QLabel *element);
    
public:
    explicit TechprocessViewer(Techprocess* tech, QWidget *parent = nullptr);
    void generateGui(Techprocess *tech);
    void addNameTech(QString name);
    void addOperation(QString name);
    void addMaterial(QString name, const Measurement::Measure &measure, CalculateElement *element1, CalculateElement *element2);
    void addMaterial(QString name, const Measurement::Measure &measure, CalculateElement *element1, CalculateElement *element2, MaterialEntry *alt);
    void addMaterial(QString name, const Measurement::Measure &measure, CalculateElement *element, MaterialEntry *alt);
    void addMaterial(QString name, const Measurement::Measure &measure, CalculateElement *element);
};
