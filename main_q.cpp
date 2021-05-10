
#include <QtWidgets/QApplication>
#include <QTextStream>

#include "parser.hpp"
#include "gui_techlist.hpp"

#include <iostream>


int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    Parser *mainparser = new Parser("data");
    TechprocessViewer *tv = new TechprocessViewer();
    Techprocess *tp = mainparser->parseResult();
    TechListViewer mainlist(mainparser->getResult());
    tv->generateGui(tp);
    tv->show();
    
//    delete mainparser;
    return app.exec();
    
}
