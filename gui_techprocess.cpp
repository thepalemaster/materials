#include "gui_techprocess.hpp"

//#include <QtWidgets/QGridLayout>

MaterialViewer::MaterialViewer(QWidget *parent)
    :QWidget(parent)
{
        QLabel *materialName = new QLabel("Сурик свинцовый ГОСТ 1488-99");
        QVBoxLayout *vBox = new QVBoxLayout();
        vBox->addWidget(materialName);
        setLayout(vBox);
}

//TechprocessViewer::TechprocessViewer(const Techprocess &tech, QWidget *parent)
TechprocessViewer::TechprocessViewer(QWidget *parent)
    :QWidget(parent)
{
    QGridLayout *gridBox = new QGridLayout();
    QLabel *oper = new QLabel("005 Обезжиривание");
    QLabel *mat1 = new QLabel("Ацетон ГОСТ 1144-88");
    QLabel *mat2 = new QLabel("Уайт-спирит ГОСТ 45687-88");
    QLabel *dig1 = new QLabel("45,5");
    QLabel *dig2 = new QLabel("14");
    QLabel *mea1 = new QLabel("г");
    QLabel *mea2 = new QLabel("мл");
    gridBox->addWidget(oper, 0, 0, 1, 2);
    gridBox->addWidget(mat1, 1, 0);
    gridBox->addWidget(mat2, 2, 0);
    gridBox->addWidget(dig1, 1, 1);
    gridBox->addWidget(dig2, 2, 1);
    gridBox->addWidget(mea1, 1, 2);
    gridBox->addWidget(mea2, 2, 2);
    setLayout(gridBox);
    //зависимости
    //лейаут сеткой
    //возможно один класс на отображение
    //и как быть зависимостями и конектами
}
 

void TechprocessViewer::addWidget()
{
    
}
