#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "techprocess.hpp"

#include "techprocess.hpp"
    

class MaterialViewer: public QWidget
{
public:
    MaterialViewer(QWidget *parent = nullptr);
};

class OperationViewer: public QWidget
{
private:
    void addMaterial(const MaterialEntry &material);
public:
    OperationViewer (QWidget *parent = nullptr);
};



class TechprocessViewer: public QWidget
{
private:
    void addOperation(const Operation &oper);
    int currentRow = 0;
    int currentColumn = 0;

public:
    TechprocessViewer(const Techprocess &tech, QWidget *parent = nullptr);
    TechprocessViewer(QWidget *parent = nullptr);
    void bindTech(const Techprocess &tech);
    void addOperation(QString name);
    void addWidget();
    

};
