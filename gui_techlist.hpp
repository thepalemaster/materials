#pragma once

#include "gui_techprocess.hpp"

class TechListViewer: public QWidget
{
    Q_OBJECT
public:
    TechListViewer(std::vector<Techprocess*>* const ptr);
};
