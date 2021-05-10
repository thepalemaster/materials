#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include "techprocess.hpp"
#include <QMainWindow>

#include <set>

struct DependanceSignal
{
    Measurement::Type type;
    double value;
};


class TechprocessViewer: public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *m_mainBox;
    QGridLayout *m_gridBox;
    QHBoxLayout *m_dependanceBox;
    QMultiMap<Measurement::Type, std::function<void(double)>> m_changesMap;
    std::set<Measurement::Type> m_usedDependance;
    //задел на будущее для параметром которые зависят более чем от одного параметра
    std::vector<std::function<void(double, Measurement::Type)>> m_complexDependance;
    int m_currentRow = 0;
    void updateMaterials(double newValue, Measurement::Type measureType);
    
public:
    explicit TechprocessViewer(QWidget *parent = nullptr);
    explicit TechprocessViewer(Techprocess* tech, QWidget *parent = nullptr);
    void generateGui(Techprocess *tech);
    void addNameTech(QString name);
    void addOperation(QString name);
    void addMaterial(QString name, double factor, const Measurement::Measure &measure1, const Measurement::Measure &measure2);
    void addMaterial(QString name, double factor, const Measurement::Measure &measure1, const Measurement::Measure &measure2, MaterialEntry *alt);
};
