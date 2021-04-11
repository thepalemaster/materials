
#include <QtWidgets/QApplication>
#include <QTextStream>

#include "parser.hpp"
#include "gui_techprocess.hpp"

#include <iostream>


int main (int argc, char *argv[])
{
    std::cout <<"!";
    QApplication app(argc, argv);
    Parser *mainparser = new Parser("data");
    MaterialViewer *mv = new MaterialViewer();
    mainparser->printToConsole();
    mv->show();
    
//    delete mainparser;
    return app.exec();
    
}
    
