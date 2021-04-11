#include "gui_techprocess.hpp"

MaterialViewer::MaterialViewer(QWidget *parent)
    :QWidget(parent)
{
        QLabel *materialName = new QLabel("Сурик свинцовый ГОСТ 1488-99");
        QVBoxLayout *vBox = new QVBoxLayout();
        vBox->addWidget(materialName);
        setLayout(vBox);
}

TechprocessViewer::TechprocessViewer(const Techprocess &tech, QWidget *parent)
    :QWidget(parent)
{
    //зависимости
    //лейаут сеткой
    //возможно один класс на отображение
    //и как быть зависимостями и конектами
}
