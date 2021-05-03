#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include "techprocess.hpp"
#include <QMainWindow>

#include <set>


class TechprocessViewer: public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *m_mainBox;
    QGridLayout *m_gridBox;
    QHBoxLayout *m_dependanceBox;
    //словарь хранит набор набор функций который необходимо выполнить при изменении параметра
    std::multimap<Measurement::Type, std::function<void(double)>> m_changesMap;
    std::set<Measurement::Type> m_usedDependance;
    int m_currentRow = 0;
    
public:
    explicit TechprocessViewer(QWidget *parent = nullptr);
    void generateGui(Techprocess *tech);
    void addNameTech(QString name);
    void addOperation(QString name);
    void addMaterial(QString name, double factor, const Measurement::Measure &measure1, const Measurement::Measure &measure2);
    void addMaterial(QString name, double factor, const Measurement::Measure &measure1, const Measurement::Measure &measure2, MaterialEntry *alt);
};
