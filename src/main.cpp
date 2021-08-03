#include "parser.hpp"
#include "gui_techlist.hpp"
#include <QIcon>

#include <iostream>


int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Калькулятор материалов");
    QIcon appIcon(":icon.svg");
    app.setWindowIcon(appIcon);
    Parser *mainparser = new Parser("data");
    TechListViewer *mainlist = new TechListViewer(mainparser->getResult());
    mainlist->show();
    
    
    delete mainparser;
    return app.exec();
    
}
