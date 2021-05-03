
#include <QtWidgets/QApplication>
#include <QTextStream>

#include "parser.hpp"
#include "gui_techprocess.hpp"

#include <iostream>


int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    Parser *mainparser = new Parser("data");
    mainparser->printToConsole();
    TechprocessViewer *tv = new TechprocessViewer();
    Techprocess *tp = mainparser->parseResult();
    tv->generateGui(tp);
    tv->show();
    
//    delete mainparser;
    return app.exec();
    
}
