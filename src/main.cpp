#include "parser.hpp"
#include "gui_techlist.hpp"

#include <iostream>


int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    Parser *mainparser = new Parser("data");
    TechListViewer mainlist(mainparser->getResult());
    mainlist.show();
    
    
    delete mainparser;
    return app.exec();
    
}
