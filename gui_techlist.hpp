#pragma once

#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QComboBox>
#include "gui_techprocess.hpp"

class TechListViewer: public QWidget
{
    Q_OBJECT
    
private:
    QVBoxLayout *m_mainListLayout;
    QComboBox *m_techCombo;
    QStackedWidget *m_techStack;
public:
    TechListViewer(std::vector<Techprocess*>* ptr);
};
