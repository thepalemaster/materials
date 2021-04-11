#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

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
    QList<OperationViewer> operations;
    void addOperation(const Operation &oper);
public:
    TechprocessViewer(const Techprocess &tech, QWidget *parent = nullptr);
    void bindTech(const Techprocess &tech);
};
